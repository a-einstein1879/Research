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
      axon.Length  =  0;
      axon.Azimuth = -1; 
      dendrRad = 0;

      numberOfConnections = 0;
      connection = new Neuron*[numberOfConnections];
      for(int i = 0; i < numberOfConnections; i++)
         connection[i] = NULL;

      isFired = false;
      batteryCharge = STARTBATTERYCHARGE;
   }
   else { //TODO:Add destructor calling for not creating new object
      printf("Can`t create a new neuron with counter %d. Maximum number of cells exceeded\n", NeuronCounter);
   }
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
      coord.CoordX = x;
      coord.CoordY = y;

      axonEnd.CoordX = x;
      axonEnd.CoordY = y;

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

double Neuron::getAxonAzimuth() {
   return axon.Azimuth;
};

struct Coordinates Neuron::getAxonEnd() {
   return axonEnd;
};

int Neuron::getDendrRad() {
   return dendrRad;
};

int Neuron::growAxon(int length, double azimuth) {
   if (azimuth == -1) {azimuth = axon.Azimuth;}
   axon.Length  = length;
   axon.Azimuth = azimuth;
   axonEnd.CoordX = coord.CoordX + (int) double(length) * sin(azimuth);
   axonEnd.CoordY = coord.CoordY + (int) double(length) * cos(azimuth);

#ifdef TRACE
   printf("Axon end is (%d, %d) now\n", axonEnd.CoordX, axonEnd.CoordY);
#endif
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

bool Neuron::checkIfFired() {
   return isFired;
};

void Neuron::fire() {
   isFired = true;
};

void Neuron::chargeBattery() {
   if (!(isFired)) {batteryCharge++;}
};

void Neuron::unchargeBattery() {
   if (isFired == true and batteryCharge > 0) {batteryCharge--;}
   if (batteryCharge == 0) {isFired = false;}
};

int Neuron::getNumberOfConnections() {
   return numberOfConnections;
};

int Neuron::getBatteryCharge() {
   return batteryCharge;
};
