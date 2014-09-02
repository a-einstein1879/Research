#include "main.h"
#include "cmn_struct.h"
#include "ui.h"
#include "cell.h"
#include "field.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*****************
      Connection
*****************/

int Connection::getSourceID() {
   return SourceID;
}

int Connection::getDestinationID() {
   return DestinationID;
}

/*****************
      NeuroConnection
*****************/

int NeuroConnection::getDelay() {
   return delay;
}

double NeuroConnection::getProbability() {
   return probability;
}

/*****************
      Main
*****************/

int main() {
   srand (time(NULL));
   NeuronField field;
   Neuron neurons[MAXNUMBEROFNEURONS];
   for(int i = 0; i < MAXNUMBEROFNEURONS; i++)
      neurons[i].SetNeuronField(field);
//   neurons[0].growAxon(2);
   CLUI ui;
   ui.printNeuronalNetwork(neurons);
   return 0;
}
