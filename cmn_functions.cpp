#include "cmn_functions.h"

int RaiseByThePower(int number, int degree) {
   int a = 1;
   for(int i = 0; i < degree; i++)
      a *= a;
   return a;
};


int CharToInt(char *number, int numberOfDigits) {
   int ret = 0;
   for(int i = 0; i < numberOfDigits; i++)
      ret += (number[i] - '0') * RaiseByThePower(10, i - 1);
   return ret;
};
