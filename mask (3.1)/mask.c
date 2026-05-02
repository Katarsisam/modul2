#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

// Проверка на цифровые права (только 0-7)
int is_numeric(const char *s) {
    if (!s || !*s) return 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] < '0' || s[i] > '7') return 0;
    }
    int len = strlen(s);
    if (len < 3 || len > 4) return 0;
    long val = strtol(s, NULL, 8);
    if (val < 0 || val > 0777) return 0;
    return 1;
}

// Проверка на символьные права
int is_symbolic(const char *s) {
    if (!s || !*s) return 0;
    if (strchr(s, ',') == NULL && strchr(s, '=') == NULL && 
        strchr(s, '+') == NULL && strchr(s, '-') == NULL) return 0;
    return 1;
}

// Парсинг символьных прав
int parse_symbolic(const char *input, mode_t *result) {
    char buf[256];
    strncpy(buf, input, 255);
    buf[255] = '\0';
    
    *result = 0;
    char *token = strtok(buf, ",");
    
    while (token) {
        // Пропускаем пробелы
        while (*token == ' ') token++;
        if (!*token) {
            token = strtok(NULL, ",");
            continue;
        }
        
        // Находим оператор
        char *op_pos = NULL;
        char op = 0;
        
        char *eq = strchr(token, '=');
        char *plus = strchr(token, '+');
        char *minus = strchr(token, '-');
        
        if (eq) { op_pos = eq; op = '='; }
        else if (plus) { op_pos = plus; op = '+'; }
        else if (minus) { op_pos = minus; op = '-'; }
        else {
            token = strtok(NULL, ",");
            continue;
        }
        
        // Разделяем на who и perms
        *op_pos = '\0';
        char *who = token;
        char *perms = op_pos + 1;
        
        // Убираем пробелы из perms
        while (*perms == ' ') perms++;
        
        // Проверяем валидность who
        for (char *p = who; *p; p++) {
            if (*p != 'u' && *p != 'g' && *p != 'o' && *p != 'a') {
                return -1;
            }
        }
        
        // Проверяем валидность perms
        for (char *p = perms; *p; p++) {
            if (*p != 'r' && *p != 'w' && *p != 'x') {
                return -1;
            }
        }
        
        // Для + и - perms не могут быть пустыми
        if ((op == '+' || op == '-') && !*perms) {
            return -1;
        }
        
        // Вычисляем биты прав
        mode_t bits = 0;
        if (strchr(perms, 'r')) bits |= 4;
        if (strchr(perms, 'w')) bits |= 2;
        if (strchr(perms, 'x')) bits |= 1;
        
        // Применяем к соответствующим категориям
        int apply_user = (!*who || strchr(who, 'u') || strchr(who, 'a'));
        int apply_group = (!*who || strchr(who, 'g') || strchr(who, 'a'));
        int apply_other = (!*who || strchr(who, 'o') || strchr(who, 'a'));
        
        if (op == '=') {
            if (apply_user) {
                *result &= ~(7 << 6);
                *result |= (bits << 6);
            }
            if (apply_group) {
                *result &= ~(7 << 3);
                *result |= (bits << 3);
            }
            if (apply_other) {
                *result &= ~7;
                *result |= bits;
            }
        } else if (op == '+') {
            if (apply_user) *result |= (bits << 6);
            if (apply_group) *result |= (bits << 3);
            if (apply_other) *result |= bits;
        } else if (op == '-') {
            if (apply_user) *result &= ~(bits << 6);
            if (apply_group) *result &= ~(bits << 3);
            if (apply_other) *result &= ~bits;
        }
        
        token = strtok(NULL, ",");
    }
    
    return 0;
}

void print_mode(mode_t mode) {
    printf("  Буквенное: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n  Цифровое: %03o\n", mode & 0777);
}

int main() {
    mode_t current = 0;
    char input[256];
    int choice;
    
    printf("Программа управления правами доступа\n");
    printf("====================================\n");
    
    while (1) {
        if (current != (mode_t)-1) {
            printf("\nТекущие права: %03o\n", current);
        }
        
        printf("\nМеню:\n");
        printf("1 - Ввести права\n");
        printf("2 - Получить права из файла\n");
        printf("3 - Изменить права\n");
        printf("4 - Выход\n");
        printf("Выбор: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Ошибка: введите число\n");
            continue;
        }
        while (getchar() != '\n');
        
        if (choice == 4) {
            printf("Выход\n");
            break;
        }
        
        if (choice == 1) {
            printf("Введите права (например: 755 или u=rwx,g=rx,o=): ");
            if (!fgets(input, sizeof(input), stdin)) continue;
            input[strcspn(input, "\n")] = '\0';
            
            if (!*input) {
                printf("Ошибка: пустой ввод\n");
                continue;
            }
            
            if (is_numeric(input)) {
                current = strtol(input, NULL, 8) & 0777;
                printf("Установлены права:\n");
                print_mode(current);
            } else if (is_symbolic(input)) {
                mode_t new_mode = 0;
                if (parse_symbolic(input, &new_mode) == 0) {
                    current = new_mode;
                    printf("Установлены права:\n");
                    print_mode(current);
                } else {
                    printf("Ошибка: неверный формат символьных прав\n");
                    printf("Примеры: u=rwx,g=rx,o= | u+x | go-w | a=r\n");
                }
            } else {
                printf("Ошибка: неверный формат\n");
                printf("Используйте цифровой (755) или символьный (u=rwx) формат\n");
            }
        } else if (choice == 2) {
            printf("Имя файла: ");
            if (!fgets(input, sizeof(input), stdin)) continue;
            input[strcspn(input, "\n")] = '\0';
            
            if (!*input) {
                printf("Ошибка: пустое имя\n");
                continue;
            }
            
            struct stat st;
            if (stat(input, &st) == 0) {
                current = st.st_mode & 0777;
                printf("Права файла %s:\n", input);
                print_mode(current);
            } else {
                printf("Ошибка: %s\n", strerror(errno));
            }
        } else if (choice == 3) {
            if (current == (mode_t)-1) {
                printf("Сначала установите права\n");
                continue;
            }
            
            printf("Введите модификацию: ");
            if (!fgets(input, sizeof(input), stdin)) continue;
            input[strcspn(input, "\n")] = '\0';
            
            if (!*input) {
                printf("Ошибка: пустой ввод\n");
                continue;
            }
            
            if (is_numeric(input)) {
                current = strtol(input, NULL, 8) & 0777;
                printf("Новые права:\n");
                print_mode(current);
            } else if (is_symbolic(input)) {
                mode_t backup = current;
                if (parse_symbolic(input, &current) == 0) {
                    printf("Измененные права:\n");
                    print_mode(current);
                } else {
                    current = backup;
                    printf("Ошибка: неверный формат модификации\n");
                    printf("Примеры: u+x | go-w | o=r | u=rwx,g=rx\n");
                }
            } else {
                printf("Ошибка: неверный формат\n");
            }
        } else {
            printf("Неверный выбор (1-4)\n");
        }
    }
    
    return 0;
}