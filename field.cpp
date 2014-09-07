#include "field.h"
#include "cell.h"
#include "cmn_functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*****************
      Field
*****************/

int Field::getNumberOfCells() {
   return numberOfCells;
};

/*****************
      NeuronField
*****************/

NeuronField::NeuronField() {
   numberOfCells = 0;
   maxNumberOfConnections = 0;

   for(int i = 0; i < XMAXSIZE; i++)
      for(int j = 0; j < YMAXSIZE; j++)
         for(int k = 0; k < FIELDNAMELENGTH; k++)
            neuronField[i][j][k] = EMPTYFIELDSYMBOL;

   neurons = new Neuron[numberOfCells];
};

void NeuronField::createNeuron() { //TODO: for more reliable solution add MAXNUMBEROFNEURONS checking
   Neuron *tmpNeurons;
   neurons->resetIdCounter();
   tmpNeurons = new Neuron[numberOfCells];
   for(int i = 0; i < numberOfCells; i++)
      *(tmpNeurons+i) = neurons[i];

   neurons->resetIdCounter();
   neurons = new Neuron[++numberOfCells];

   for(int i = 0; i < numberOfCells - 1; i++)
      neurons[i] = *(tmpNeurons+i);

   delete [] tmpNeurons;
};

int NeuronField::addNeuron(int x, int y) { //TODO: fix recursive bug. Add counter to prevent loop
   bool availability = false, randomity = false;
   if ((x == -1) and (y == -1)) {x = rand()%XMAXSIZE; y = rand()%YMAXSIZE; randomity = true;}
   if (getFieldType(x, y) == EMPTYFIELDSYMBOL) {availability = true;}

   if (availability == true) {
         createNeuron();
         neurons[numberOfCells - 1].setCoordinates(x, y);
         fillField(x, y, NEURONSYMBOL, numberOfCells - 1);
   }
   else {
      if (randomity == true)
         addNeuron();
      else {
         printf("Can`t create neuron here (%d, %d)\n", x, y);
      }
   }
   return 0;
};

void NeuronField::fillField(int x, int y, char type, int neuronId) {
   char id[FIELDNAMELENGTH];
   snprintf(id, FIELDNAMELENGTH, "%d", neuronId);
   neuronField[x][y][0] = type;
   for(int i = 1; i < FIELDNAMELENGTH; i++)
      neuronField[x][y][i] = id[i-1];
};

void NeuronField::growAxon(int NeuronId, int delta, double azimuth) {
   Neuron *neuron;
   neuron = getNeuronById(NeuronId);
   struct Coordinates coord;
   coord = neuron->getCoord(); //axon end??
   int axonLength = neuron->getAxonLength();

   for(int i = axonLength + 1; i < delta; i++) {
      int newx, newy;
      newx = coord.CoordX + i * sin(azimuth);
      newy = coord.CoordY + i * cos(azimuth);

      if (newx > XMAXSIZE or newx < 0 or newy > YMAXSIZE or newy < 0/* or newx == coord.CoordX or newy == coord.CoordY*/) {continue;}
      char stat = getFieldType(newx, newy);
      if (stat == NEURONSYMBOL or stat == DENDRSYMBOL) {

#ifdef TRACE
         printf("Added connection. newx = %d\tnewy = %d\tNeuronId = %d\n", newx, newy, NeuronId);
#endif

         neuron->addConnection(getNeuronByField(newx, newx));
         int NumberOfConnections = neuron->getNumberOfConnections();
#ifdef TRACE
         if (maxNumberOfConnections < NumberOfConnections) {printf("maxNumberOfConnections increased to %d\n", NumberOfConnections);}
#endif
         maxNumberOfConnections = (maxNumberOfConnections < NumberOfConnections) ? NumberOfConnections : maxNumberOfConnections;
      }
      else {
         fillField(newx, newy, AXONSYMBOL, NeuronId);

#ifdef TRACE
         printf("newx = %d\tnewy = %d\tNeuronId = %d\n", newx, newy, NeuronId);
#endif

      }
   }
};

void NeuronField::growDendr(int NeuronId, int delta) {
};

Neuron* NeuronField::getNeuronById(int neuronId) {
   return neurons + neuronId;
};

char NeuronField::getFieldType(int x, int y) {
   return neuronField[x][y][0];
};

Neuron* NeuronField::getNeuronByField(int x, int y) {
   Neuron* ret = NULL;


   int neuronId = CharToInt(neuronField[x][y] + 1, FIELDNAMELENGTH - 1);

   ret = neurons + neuronId;
   return ret;
};

void NeuronField::printFieldStat() {
   printf("numberOfCells = %d\n", numberOfCells);
   for(int i = 0; i < numberOfCells; i++) {
      struct Coordinates coord = neurons[i].getCoord();
      printf("Coord[%d] = (%d,%d)\n", i, coord.CoordX, coord.CoordY);
   }
};
