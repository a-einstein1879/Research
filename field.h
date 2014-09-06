#ifndef FIELD_H
#define FIELD_H

#include "cmn_struct.h"
#include "cell.h"

#define NEURONSYMBOL     'N'
#define AXONSYMBOL       'A'
#define EMPTYFIELDSYMBOL ' '

class Field {
protected:
   int numberOfCells;
public:
   int getNumberOfCells();
};

class NeuronField : public Field {
private:
   int maxNumberOfConnections;
   char neuronField[XMAXSIZE][YMAXSIZE][FIELDNAMELENGTH];
   Neuron *neurons;
public:
   NeuronField();
   void createNeuron(int x, int y);
   int addNeuron(int x = -1, int y = -1); //returns neuron Id
   void growAxon(int NeuronId, int delta, double azimuth = 0);
   void growDendr(int NeuronId, int delta);
   Neuron* getNeuronById(int neuronId);
   Neuron getNeuronByField(int x, int y);
   char getFieldStat(int x, int y);
};

#endif
