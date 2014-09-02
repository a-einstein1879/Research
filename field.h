#ifndef FIELD_H
#define FIELD_H

#include "cmn_struct.h"
#include "cell.h"

class Field {
protected:
   int numberOfCells;
   char field[XMAXSIZE][YMAXSIZE][FIELDNAMELENGTH];
public:
   int getNumberOfCells();
};

class NeuronField : public Field {
private:
   Neuron *neuron[MAXNUMBEROFNEURONS];
public:
   NeuronField();
   int addNeuron(struct Coordinates coordinates, Neuron newNeuron); //returns 1 if succeded 0 if failed
   Neuron getNeuronById(int cellId);
};

#endif
