#ifndef CALC_H
#define CALC_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double power(double a, double b);
double square_root(double a);


typedef struct {
  char name[20];
  char description[50];
  double (*func)(double, ...);
  int args_required;
} Command;

void add_command(Command **commands, int *count, const char *name,
                 const char *desc, double (*func)(double, ...), int args);
#endif