#ifndef CELL_H
#define CELL_H

#include "cmn_struct.h"

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
public:
   static int NeuronCounter;
   void resetIdCounter();
   Neuron(int x = -1, int y = -1);
   void setCoordinates(int x, int y);
   int getDendrRad();
   int getAxonLength();
   int growAxon(int delta, double azimuth = -1);
   int growDendr(int delta);
   int addConnection(Neuron *tmpConnection);
   int getNumberOfConnections();
};

#endif
