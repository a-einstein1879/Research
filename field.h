#ifndef FIELD_H
#define FIELD_H

#include "cmn_struct.h"
#include "cell.h"

#define NEURONSYMBOL          'N'
#define AXONSYMBOL            'A'
#define DENDRSYMBOL           'D'
#define EMPTYFIELDSYMBOL      ' '
#define FIREDSYMBOL           'F'
#define NEURONIDINITIALVALUE  (-1)

#define AXONANGLEPRECISENESS 2

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
   char neuronType[XMAXSIZE][YMAXSIZE];
   int neuronIds[XMAXSIZE][YMAXSIZE];
   Neuron *neurons;

/**********************
      Private functions
**********************/
   void createNeuron();
   void fillField(int x, int y, char type, int neuronId);

/**********************
      Internal interface
**********************/

   Neuron* getNeuronByField(int x, int y);
   Neuron* getNeuronById(int neuronId);

public:
   NeuronField();

/**********************
      Growing
**********************/

   int addNeuron(int x = -1, int y = -1);
   void growAxons(int maxLength = 0);
   void growAxon(int NeuronId, int delta, double azimuth = -1); /* azimuth is an angle that is counted from positive part of y axis counterclockwise */
   void growDendr(int NeuronId, int delta);                     /* no functionality... yet */

/**********************
      Firing
**********************/

   void fireNeuron(int NeuronId = -1);
   void spreadImpulse();
   void chargeBatteries();
   void unchargeBatteries();

/**********************
      External interface
**********************/

   char getFieldType(int x, int y); /* Should make it a friend of UI class */
   bool getSpotStat(int x, int y); /* For UI to get stat fired or not fired */
   void printFieldStat(int time = -1);
   bool isAnyPlaceLeft();
};

#endif
