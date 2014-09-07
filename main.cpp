#include "main.h"
#include "cmn_struct.h"
#include "ui.h"
#include "cell.h"
#include "field.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/*****************
      Main
*****************/

int main() {
   srand (time(NULL));
   NeuronField field1;
   field1.addNeuron(1, 3);
   field1.addNeuron(1, 6);
   field1.addNeuron(1, 10);
   field1.growAxon(2, 10, M_PI);
   field1.growAxon(0, 7, M_PI/4);

#ifdef TRACE
   field1.printFieldStat();
#endif

   CLUI ui;
   ui.printNeuronalNetwork(field1);
   return 0;
}
