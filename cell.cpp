#include "cell.h"
#include "cmn_struct.h"
#include "field.h"

#include <stdio.h>
#include <stdlib.h>

/*****************
      Cell
*****************/

struct Coordinates Cell::getCoord() {
   return coord;
}

/*****************
      Neuron
*****************/

int Neuron::NumberOfNeurons = FIRSTNEURONNUMBER;

Neuron::Neuron(int x, int y) {
   if (NumberOfNeurons<MAXNUMBEROFNEURONS + FIRSTNEURONNUMBER) {
      NeuronId = NumberOfNeurons++;
      printf("NeuronId = %d\n", NeuronId);

      if ((x == -1) and (y == -1)) {x = rand()%XMAXSIZE; y = rand()%YMAXSIZE;}
      coord.CoordX = x;
      coord.CoordY = y;
/*      axon.Exist = 0;
      dendrRad = 0;
      dendrArea.Preciseness = PRECISENESS;*/
      printf("Coord = (%d,%d)\n", coord.CoordX, coord.CoordY);
   }
   else { //TODO:Add destructor calling for not creating new object
      printf("Can`t create a new neuron. Maximum number of cells exceeded\n");
   }
}


void Neuron::SetNeuronField(NeuronField *tmpfield) {
   field = tmpfield;
};

void Neuron::createAxon(int length, double azimuth) {
/*   if ((length == 0) and (azimuth == 0)) {
      axon.Exist = 1;
      axon.Azimuth = 0;
   }
   else {
      axon.Exist = 1;
      axon.Length = length;
      axon.Azimuth = azimuth;
   }*/
};

void Neuron::growAxon(int delta) {
/*   if(axon.Exist == 0) {createAxon(delta);}
   axon.Length += delta;*/
};

void Neuron::growDendr() {};

int Neuron::getNeuronId() {
   return NeuronId;
};
void Neuron::CheckForNewNeuroConnection(struct DendrArea dendrArea) {};
