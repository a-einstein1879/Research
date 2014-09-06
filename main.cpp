#include "main.h"
#include "cmn_struct.h"
#include "ui.h"
#include "cell.h"
#include "field.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*****************
      Main
*****************/

int main() {
   srand (time(NULL));
   NeuronField field1;
   field1.addNeuron(1, 1);
   field1.addNeuron(1, 3);
   field1.addNeuron();
   field1.growAxon(0, 1, 0);
   CLUI ui;
   ui.printNeuronalNetwork(field1);
   return 0;
}
