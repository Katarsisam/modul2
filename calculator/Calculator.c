#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef double (*CalcFunc)(double, ...);   

typedef struct {
    char name[20];
    char description[50];
    double (*func)(double, ...);     // один указатель с ellipsis
    void *handle;                    // дескриптор dlopen
    int args_required;
} Command;

int add_dynamic_command(Command **commands, int *count,
                        const char *name, const char *desc, int args)
{
    *commands = realloc(*commands, (*count + 1) * sizeof(Command));
    if (*commands == NULL) {
        printf("Ошибка выделения памяти\n");
        return -1;
    }

    Command *cmd = &(*commands)[*count];

    strncpy(cmd->name, name, 19);
    cmd->name[19] = '\0';

    strncpy(cmd->description, desc, 49);
    cmd->description[49] = '\0';

    cmd->func = NULL;
    cmd->handle = NULL;
    cmd->args_required = args;

    // Загружаем динамическую библиотеку сразу при добавлении команды
    if (args > 0) {
        char libname[64];
        snprintf(libname, sizeof(libname), "./libs/lib%s.so", name);

        cmd->handle = dlopen(libname, RTLD_LAZY | RTLD_LOCAL);
        if (cmd->handle) {
            // Загружаем функцию (приводим к типу CalcFunc)
            cmd->func = (CalcFunc)dlsym(cmd->handle, name);
            if (!cmd->func) {
                fprintf(stderr, "Ошибка dlsym для функции '%s' в %s: %s\n", 
                        name, libname, dlerror());
                dlclose(cmd->handle);
                cmd->handle = NULL;
            }
        } else {
            fprintf(stderr, "Предупреждение: не удалось загрузить библиотеку %s: %s\n", 
                    libname, dlerror());
        }
    }

    (*count)++;
    return 0;
}


int main() {
    Command *commands = NULL;
    int command_count = 0;

    // Регистрация всех команд с автоматической загрузкой .so
    add_dynamic_command(&commands, &command_count, "add",  "Сложение двух чисел", 2);
    add_dynamic_command(&commands, &command_count, "subtract",  "Вычитание двух чисел", 2);
    add_dynamic_command(&commands, &command_count, "multiply",  "Умножение двух чисел", 2);
    add_dynamic_command(&commands, &command_count, "divide",  "Деление двух чисел", 2);
    add_dynamic_command(&commands, &command_count, "power",  "Возведение в степень", 2);
    add_dynamic_command(&commands, &command_count, "square_root", "Квадратный корень", 1);
    add_dynamic_command(&commands, &command_count, "exit", "Выход из программы", 0);

    printf("Добро пожаловать в калькулятор с динамическими библиотеками!\n");

    while (1) {
        printf("\nДоступные команды:\n");
        for (int i = 0; i < command_count; i++) {
            printf("%s - %s\n", commands[i].name, commands[i].description);
        }

        printf("\nВведите команду: ");
        char input[20];
        if (scanf("%19s", input) != 1) {
            break;
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Поиск команды
        Command *current = NULL;
        for (int i = 0; i < command_count; i++) {
            if (strcmp(commands[i].name, input) == 0) {
                current = &commands[i];
                break;
            }
        }

        if (current == NULL) {
            printf("Неизвестная команда. Попробуйте снова.\n");
            continue;
        }

        // Повторная попытка загрузки, если не удалось при регистрации
        if (current->func == NULL && current->args_required > 0) {
            char libname[64];
            snprintf(libname, sizeof(libname), "./libs/%s.so", current->name);

            current->handle = dlopen(libname, RTLD_LAZY | RTLD_LOCAL);
            if (current->handle) {
                current->func = (CalcFunc)dlsym(current->handle, current->name);
            }
        }

        // Ввод аргументов
        double a = 0.0, b = 0.0;
        if (current->args_required >= 1) {
            printf("Введите первый аргумент: ");
            scanf("%lf", &a);
        }
        if (current->args_required >= 2) {
            printf("Введите второй аргумент: ");
            scanf("%lf", &b);
        }

        // Выполнение функции
        if (current->func != NULL) {
            double result = 0.0;
            if (current->args_required == 2) {
                result = current->func(a, b);
            } else if (current->args_required == 1) {
                result = current->func(a);
            }
            printf("Результат: %.2lf\n", result);
        } else {
            printf("Ошибка: функция '%s' не загружена.\n", current->name);
        }
    }

    // Очистка всех библиотек
    for (int i = 0; i < command_count; i++) {
        if (commands[i].handle != NULL) {
            dlclose(commands[i].handle);
        }
    }
    free(commands);

    printf("Программа завершена.\n");
    return 0;
}