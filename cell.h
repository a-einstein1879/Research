#ifndef CELL_H
#define CELL_H

#include "cmn_struct.h"
#include "field.h"

class Cell {
protected:
   struct Coordinates coord;
public:
   struct Coordinates getCoord();
};

class Neuron : public Cell {
private:
   NeuronField *field;
   int NeuronId;
   struct DendrArea dendrArea;
   int dendrRad;
   struct Axon axon;
public:
   static int NumberOfNeurons;
   Neuron(int x = -1, int y = -1);
   void SetNeuronField(NeuronField *tmpfield);
   int getNeuronId();
   void createAxon(int length = 0, double azimuth = 0);
   void growAxon(int delta);
   void growDendr();
   void CheckForNewNeuroConnection(struct DendrArea dendrArea);
};

#endif
