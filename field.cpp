#include "field.h"
#include "cell.h"

#include <stdlib.h>

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

   for(int i = 0; i < XMAXSIZE; i++)
      for(int j = 0; j < YMAXSIZE; j++)
         for(int k = 0; k < FIELDNAMELENGTH; k++)
            field[i][j][k] = ' ';

   for(int i = 0; i < MAXNUMBEROFNEURONS; i++)
      neuron[i] = NULL;
};

int NeuronField::addNeuron(struct Coordinates coordinates, Neuron newNeuron) {
};

Neuron NeuronField::getNeuronById(int cellId) {
};
