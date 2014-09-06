#include "cell.h"
#include "cmn_struct.h"

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

int Neuron::NeuronCounter = FIRSTNEURONNUMBER;

Neuron::Neuron(int x, int y) {
   if (NeuronCounter < MAXNUMBEROFNEURONS + FIRSTNEURONNUMBER) {
      NeuronId = NeuronCounter++;
//      printf("Creating neuron with NeuronId = %d\n", NeuronId);

      coord.CoordX = x;
      coord.CoordY = y;
      axon.Exist = 0;
      dendrRad = 0;
      numberOfConnections = 0;
      connection = new Neuron*[numberOfConnections];
      for(int i = 0; i < numberOfConnections; i++)
         connection[i] = NULL;
//      printf("Coord = (%d,%d)\n", coord.CoordX, coord.CoordY);
   }
   else { //TODO:Add destructor calling for not creating new object
      printf("Can`t create a new neuron with counter %d. Maximum number of cells exceeded\n", NeuronCounter);
   }
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
      coord.CoordX = x;
      coord.CoordY = y;
//      printf("Coordinates of neuron %d were changed.\nNew coordinates = (%d,%d)\n", NeuronId, coord.CoordX, coord.CoordY);
};


void Neuron::resetIdCounter() {
   NeuronCounter = FIRSTNEURONNUMBER;
};
/**Axon Neuron::getAxon() {
   return *axon;
};*/

int Neuron::getDendrRad() {
   return dendrRad;
};

void Neuron::createAxon(int length, double azimuth) {
   if ((length == 0) and (azimuth == 0)) {
      axon.Exist = 1;
      axon.Azimuth = 0;
   }
   else {
      axon.Exist = 1;
      axon.Length = length;
      axon.Azimuth = azimuth;
   }
};

int Neuron::growAxon(int delta) {
   if(axon.Exist == 0) {createAxon(delta);}
   axon.Length += delta;
};

int Neuron::growDendr(int delta) {
   dendrRad += delta;
};

int Neuron::addConnection(Neuron *tmpConnection) {};
