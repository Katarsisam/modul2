#include "Calculator.h"

int main() {
  Command *commands = NULL;
  int command_count = 0;

  add_command(&commands, &command_count, "add", "Сложение двух чисел", add, 2);
  add_command(&commands, &command_count, "sub", "Вычитание двух чисел",
              subtract, 2);
  add_command(&commands, &command_count, "mul", "Умножение двух чисел",
              multiply, 2);
  add_command(&commands, &command_count, "div", "Деление двух чисел", divide,
              2);
  add_command(&commands, &command_count, "pow", "Возведение в степень", power,
              2);
  add_command(&commands, &command_count, "sqrt", "Квадратный корень",
              square_root, 1);
  add_command(&commands, &command_count, "exit", "Выход из программы", NULL, 0);

  printf("Добро пожаловать в калькулятор!\n");

  while (1) {
    printf("\nДоступные команды:\n");
    for (int i = 0; i < command_count; i++) {
      printf("%s - %s\n", commands[i].name, commands[i].description);
    }

    printf("\nВведите команду: ");
    char input[20];
    scanf("%19s", input);

    // Проверка на выход
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

    // Ввод аргументов
    double a = 0, b = 0;
    if (current->args_required >= 1) {
      printf("Введите первый аргумент: ");
      scanf("%lf", &a);
    }
    if (current->args_required >= 2) {
      printf("Введите второй аргумент: ");
      scanf("%lf", &b);
    }

    // Выполнение операции и вывод результата
    if (current->func != NULL) {
      double result = current->func(a, b);
      printf("Результат: %.2lf\n", result);
    } else {
      printf("Невозможно выполнить команду.\n");
    }
  }

  free(commands);
  printf("Программа завершена.\n");
  return 0;
}