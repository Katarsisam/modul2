#include "../Calculator.h"

// Функция для добавления команды в список
void add_command(Command **commands, int *count, const char *name,
                 const char *desc, double (*func)(double, ...), int args) {
  *commands = realloc(*commands, (*count + 1) * sizeof(Command));
  if (*commands == NULL) {
    printf("Ошибка выделения памяти\n");
    exit(1);
  }

  strncpy((*commands)[*count].name, name, 19);
  strncpy((*commands)[*count].description, desc, 49);
  (*commands)[*count].func = func;
  (*commands)[*count].args_required = args;
  (*count)++;
}