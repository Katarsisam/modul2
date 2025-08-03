#include "../Calculator.h"

double square_root(double a) {

  if (a < 0) {
    printf("Ошибка: корень из отрицательного числа!\n");
    return 0;
  }
  return sqrt(a);
}
