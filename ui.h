#ifndef UI_H
#define UI_H

#include "field.h"

#define NEURONCOLOR     GREEN
#define AXONCOLOR       WHITE
#define DENDRITECOLOR   YELLOW
#define FIRINGCOLOR     RED
#define EMPTYFIELDCOLOR BLACK

class UI {
private:
   virtual void clearScreen()=0;
public:   
   virtual void printNeuronalNetwork(NeuronField Field, int time)=0;
};

class CLUI : public UI {
private:
   void clearScreen();
public:
   void printNeuronalNetwork(NeuronField Field, int time);
};

class GUI : public UI {
private:
   void clearScreen();
public:
   GUI();
   ~GUI();
   void printNeuronalNetwork(NeuronField Field, int time);
};

#endif
