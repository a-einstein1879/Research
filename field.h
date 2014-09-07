#ifndef FIELD_H
#define FIELD_H

#include "cmn_struct.h"
#include "cell.h"

#define NEURONSYMBOL     'N'
#define AXONSYMBOL       'A'
#define DENDRSYMBOL      'D'
#define EMPTYFIELDSYMBOL ' '

class Field {
protected:
   int numberOfCells;
public:
   int getNumberOfCells();
};

class NeuronField : public Field {
private:
/**********************
      Private data
**********************/
   int maxNumberOfConnections;
   char neuronField[XMAXSIZE][YMAXSIZE][FIELDNAMELENGTH];
   Neuron *neurons;

/**********************
      Private functions
**********************/
   void createNeuron();
   void fillField(int x, int y, char type, int neuronId);
public:
/**********************
      Public functions
**********************/
   NeuronField();
   int addNeuron(int x = -1, int y = -1);
   void growAxon(int NeuronId, int delta, double azimuth = 0); /* azimuth is an angle that is counted from positive part of y axis counterclockwise */
   void growDendr(int NeuronId, int delta);
   Neuron* getNeuronById(int neuronId);
   char getFieldType(int x, int y);
   Neuron* getNeuronByField(int x, int y);
   void printFieldStat();
};

#endif
