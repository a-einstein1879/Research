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
   int dendrRad;
   Neuron **connection;
   int numberOfConnections;
public:
   static int NeuronCounter;
   void resetIdCounter();
   Neuron(int x = -1, int y = -1);
   void setCoordinates(int x, int y);
//   struct *Axon getAxon();
   int getDendrRad();
   void createAxon(int length = 0, double azimuth = 0);
   int growAxon(int delta);
   int growDendr(int delta);
   int addConnection(Neuron *tmpConnection);
};

#endif
