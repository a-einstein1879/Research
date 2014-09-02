#ifndef UI_H
#define UI_H

#include "cell.h"

class UI {
private:
   virtual void printNeuron()=0;
   virtual void clearScreen()=0;
public:   
   virtual void printNeuronalNetwork(Neuron *neurons)=0;
};

class CLUI : public UI {
private:
   void printNeuron();
   void clearScreen();
public:
   void printNeuronalNetwork(Neuron *neurons);
};

#endif
