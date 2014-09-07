#include "cell.h"
#include "cmn_struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

      coord.CoordX = x;
      coord.CoordY = y;

#ifdef TRACE
      if(x != -1 and y != -1) {printf("Added neuron number %d with coordinates x = %d, y = %d\n", NeuronId + 1, x, y);}
      else                    {printf("Added neuron number %d without place\n", NeuronId + 1);}
#endif

      axonEnd.CoordX = x;
      axonEnd.CoordY = y;
      dendrRad = 0;

      numberOfConnections = 0;
      connection = new Neuron*[numberOfConnections];
      for(int i = 0; i < numberOfConnections; i++)
         connection[i] = NULL;
   }
   else { //TODO:Add destructor calling for not creating new object
      printf("Can`t create a new neuron with counter %d. Maximum number of cells exceeded\n", NeuronCounter);
   }
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
      coord.CoordX = x;
      coord.CoordY = y;

#ifdef TRACE
      printf("Coordinates of neuron number %d were changed. New coordinates are x = %d, y = %d\n", NeuronId, x, y);
#endif
};


void Neuron::resetIdCounter() {
   NeuronCounter = FIRSTNEURONNUMBER;
};

int Neuron::getAxonLength() {
   return axon.Length;
};

int Neuron::getDendrRad() {
   return dendrRad;
};

int Neuron::growAxon(int delta, double azimuth) {
   if (azimuth == -1) {azimuth = axon.Azimuth;}
   axon.Length += delta;
   axon.Azimuth = azimuth;
/*   axonEnd.CoordX += (int) (double(delta) * sin(azimuth));
   axonEnd.CoordY += (int) (double(delta) * cos(azimuth));*/ //TODO: Needs thinking
};

int Neuron::growDendr(int delta) {
   dendrRad += delta;
};

int Neuron::addConnection(Neuron *tmpConnection) {

#ifdef TRACE
   printf("Added connection number %d\n", numberOfConnections + 1);
#endif

   Neuron **TmpConnection;
   TmpConnection = new Neuron*[numberOfConnections];
   for(int i = 0; i < numberOfConnections; i++)
      TmpConnection[i] = connection[i];

   connection = new Neuron*[++numberOfConnections];

   for(int i = 0; i < numberOfConnections - 1; i++)
      connection[i] = TmpConnection[i];

   delete [] TmpConnection;

   connection[numberOfConnections - 1] = tmpConnection;
};

int Neuron::getNumberOfConnections() {
   return numberOfConnections;
};
