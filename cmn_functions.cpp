#include "cmn_functions.h"

#include <stdio.h>

int RaiseByThePower(int number, int degree) {
   int a = 1;
   for(int i = 0; i < degree; i++)
      a *= number;
   return a;
}
