#include "field.h"
#include "cell.h"

#include <stdlib.h>
#include <stdio.h>

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

void NeuronField::createNeuron(int x, int y) {
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

   neurons[numberOfCells - 1].setCoordinates(x, y);
   neuronField[x][y][0] = NEURONSYMBOL;
   printf("numberOfCells = %d\n", numberOfCells);
   for(int i = 0; i < numberOfCells; i++) {
      struct Coordinates coord = neurons[i].getCoord();
      printf("Coord[%d] = (%d,%d)\n", i, coord.CoordX, coord.CoordY);
   }
};

int NeuronField::addNeuron(int x, int y) { //TODO: fix recursive bug. Add counter to prevent loop
   bool availability = false, randomity = false;
   if ((x == -1) and (y == -1)) {x = rand()%XMAXSIZE; y = rand()%YMAXSIZE; randomity = true;}
   if (getFieldStat(x, y) == EMPTYFIELDSYMBOL) {availability = true;}

   if (availability == true) {
         createNeuron(x, y);
   }
   else {
      if (randomity == true)
         addNeuron();
      else {
         printf("Can`t create neuron here (%d, %d)\n", x, y);
      }
   }
};

void NeuronField::growAxon(int NeuronId, int delta, double azimuth) {
};

void NeuronField::growDendr(int NeuronId, int delta) {
};

Neuron* NeuronField::getNeuronById(int neuronId) {
   return neurons + neuronId;
};

Neuron NeuronField::getNeuronByField(int x, int y) {
};

char NeuronField::getFieldStat(int x, int y) {
   return neuronField[x][y][0];
};
