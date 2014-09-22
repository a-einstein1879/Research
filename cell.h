#ifndef CELL_H
#define CELL_H

#include "cmn_struct.h"

#define STARTBATTERYCHARGE 3

class Cell {
protected:
   struct Coordinates coord;
public:
   struct Coordinates getCoord();
};

class Neuron : public Cell {
private:
   int NeuronId;
   struct Axon axon;
   struct Coordinates axonEnd;
   int dendrRad;
   Neuron **connection;
   int numberOfConnections;
   bool isFired;
   int batteryCharge;
public:
   static int NeuronCounter;
   void resetIdCounter();
   Neuron(int x = -1, int y = -1);
   void setCoordinates(int x, int y);
   struct Coordinates getAxonEnd();
   int getDendrRad();
   int getAxonLength();
   double getAxonAzimuth();
   int growAxon(int length, double azimuth = -1);
   int growDendr(int delta);
   int addConnection(Neuron *tmpConnection);
   bool checkIfFired();
   void fire();
   void chargeBattery();
   void unchargeBattery();
   int getNumberOfConnections();
   int getBatteryCharge();
};

#endif
