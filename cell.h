#ifndef CELL_H
#define CELL_H

#include "cmn_struct.h"
#include "cmn_defines.h"

/**********************
      Cell
**********************/

class Cell {
protected:
   struct Coordinates coord;
public:
   struct Coordinates getCoord();
};

/**********************
      Neuron
**********************/

class Neuron : public Cell {
private:
   int NeuronId;

/**********************
      Connections
**********************/

   struct Axon axon;
   struct Coordinates axonEnd;
   int dendrRad;
   Neuron *connection[MAXNUMBEROFCONNECTIONSPERNEURON];
   int numberOfConnections;

/**********************
      Firing
**********************/

   bool isFired;
   int batteryCharge;

public:

/**********************
      Creation and deletition
**********************/

   static int NeuronCounter;
   void resetIdCounter();
   Neuron(int x = -1, int y = -1);
   ~Neuron();
   void setCoordinates(int x, int y);

/**********************
      Connections
**********************/

   int growAxon(int length, double azimuth = -1);  /* returns new axon length     */
   int growDendr(int delta);                       /* returns new dendrite radius */
   int addConnection(Neuron *tmpConnection);

/**********************
      Firing
**********************/

   bool checkIfFired();
   void fire();
   void spreadImpulse();
   void chargeBattery(int delta = 1);
   void unchargeBattery();
   void printConnections();

/**********************
      Interface
**********************/

   int getNeuronId();
   struct Coordinates getAxonEnd();
   int getDendrRad();
   int getAxonLength();
   double getAxonAzimuth();
   int getNumberOfConnections();
   int getBatteryCharge();
};

#endif
