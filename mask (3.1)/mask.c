#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void print_permissions(mode_t mode) {
    // Буквенное представление
    printf("Буквенное представление: ");
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c\n", (mode & S_IXOTH) ? 'x' : '-');

    // Цифровое представление
    printf("Цифровое представление: %o\n", mode & 0777);

    // Битовое представление
    printf("Битовое представление: ");
    for (int i = 8; i >= 0; i--) {
        printf("%d", (mode & (1 << i)) ? 1 : 0);
        if (i % 3 == 0) printf(" ");
    }
    printf("(9 бит: rwxrwxrwx)\n");
}

mode_t parse_numeric_permissions(const char* input) {
    return (mode_t)strtol(input, NULL, 8) & 0777;
}

mode_t parse_symbolic_permissions(const char* input) {
    mode_t mode = 0;
    char* token;
    char* rest = strdup(input);

    while ((token = strtok_r(rest, ",", &rest))) {
        char who[10] = {0};
        char op;
        char perms[10] = {0};
        
        if (sscanf(token, "%[^=]=%s", who, perms) == 2) {
            op = '=';
        } else if (sscanf(token, "%[^+-]%c%s", who, &op, perms) < 2) {
            continue;
        }

        mode_t perm_bits = 0;
        if (strchr(perms, 'r')) perm_bits |= 4;
        if (strchr(perms, 'w')) perm_bits |= 2;
        if (strchr(perms, 'x')) perm_bits |= 1;

        mode_t user_mask = 0, group_mask = 0, other_mask = 0;
        
        if (strchr(who, 'u') || !*who) user_mask = 07;
        if (strchr(who, 'g') || !*who) group_mask = 07;
        if (strchr(who, 'o') || !*who) other_mask = 07;

        if (op == '+') {
            mode |= (perm_bits << 6) & user_mask;
            mode |= (perm_bits << 3) & group_mask;
            mode |= perm_bits & other_mask;
        } else if (op == '-') {
            mode &= ~((perm_bits << 6) & user_mask);
            mode &= ~((perm_bits << 3) & group_mask);
            mode &= ~(perm_bits & other_mask);
        } else if (op == '=') {
            mode &= ~(user_mask << 6 | group_mask << 3 | other_mask);
            mode |= (perm_bits << 6) & user_mask;
            mode |= (perm_bits << 3) & group_mask;
            mode |= perm_bits & other_mask;
        }
    }

    return mode;
}

mode_t get_file_permissions(const char* filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("Ошибка при получении информации о файле");
        return 0;
    }
    return file_stat.st_mode & 0777;
}

mode_t modify_permissions(mode_t current_mode, const char* modification) {
    if (strspn(modification, "01234567") == strlen(modification)) {
        return parse_numeric_permissions(modification);
    } else {
        return parse_symbolic_permissions(modification);
    }
}

int main() {
    mode_t current_mode = 0;
    char input[100];
    int choice;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Ввести права доступа (буквенное или цифровое обозначение)\n");
        printf("2. Ввести имя файла для получения информации о правах доступа\n");
        printf("3. Изменить текущие права доступа\n");
        printf("4. Выход\n");
        printf("Выберите пункт меню: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Некорректный ввод. Попробуйте снова.\n");
            continue;
        }
        getchar(); // Очистка буфера

        switch (choice) {
            case 1:
                printf("Введите права доступа (например, 755 или u=rwx,g=rx,o=): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                
                if (strspn(input, "01234567") == strlen(input)) {
                    current_mode = parse_numeric_permissions(input);
                } else {
                    current_mode = parse_symbolic_permissions(input);
                }
                
                printf("\nТекущие права доступа:\n");
                print_permissions(current_mode);
                break;
                
            case 2:
                printf("Введите имя файла: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                
                current_mode = get_file_permissions(input);
                if (current_mode != 0) {
                    printf("\nПрава доступа для файла '%s':\n", input);
                    print_permissions(current_mode);
                    printf("\nДля сравнения выполните в терминале команду: ls -l %s\n", input);
                }
                break;
                
            case 3:
                if (current_mode == 0) {
                    printf("Сначала задайте права доступа (пункт 1 или 2)\n");
                    break;
                }
                
                printf("Введите команду модификации прав (например, 755 или u+rwx,go-w): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                
                mode_t new_mode = modify_permissions(current_mode, input);
                if (new_mode != current_mode) {
                    current_mode = new_mode;
                    printf("\nНовые права доступа:\n");
                    print_permissions(current_mode);
                } else {
                    printf("Права доступа не изменились\n");
                }
                break;
                
            case 4:
                printf("Выход из программы\n");
                return 0;
                
            default:
                printf("Некорректный выбор. Попробуйте снова.\n");
        }
    }

    return 0;
}