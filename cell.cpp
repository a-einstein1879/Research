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

/**********************
      Creation and deletition
**********************/

int Neuron::NeuronCounter = FIRSTNEURONNUMBER;

Neuron::Neuron(int x, int y) {
   if (NeuronCounter < MAXNUMBEROFNEURONS + FIRSTNEURONNUMBER) {
      NeuronId = NeuronCounter++;

      coord.CoordX = x;
      coord.CoordY = y;

#ifdef TRACE
      if(x != -1 and y != -1) {printf("Cell: Added neuron number %d with coordinates x = %d, y = %d\n", NeuronId, x, y);}
      else                    {printf("Cell: Added neuron number %d without place\n", NeuronId);}
#endif

      axonEnd.CoordX = x;
      axonEnd.CoordY = y;
      axon.Length  =  0;
      axon.Azimuth = -1; 
      dendrRad = 0;

      numberOfConnections = 0;
      for(int i = 0; i < MAXNUMBEROFCONNECTIONSPERNEURON; i++)
         connection[i] = NULL;

      isFired = false;
      batteryCharge = STARTBATTERYCHARGE;
   }
   else { //TODO:Add destructor calling for not creating new object
      printf("Cell: Can`t create a new neuron with counter %d. Maximum number of cells exceeded\n", NeuronCounter);
   }
}


Neuron::~Neuron() {
   NeuronCounter--;
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
      coord.CoordX = x;
      coord.CoordY = y;

      axonEnd.CoordX = x;
      axonEnd.CoordY = y;

#ifdef TRACE
      printf("Cell: Coordinates of neuron number %d were changed. New coordinates are x = %d, y = %d\n", NeuronId, x, y);
#endif
}

void Neuron::resetIdCounter() {
   NeuronCounter = FIRSTNEURONNUMBER;
}

/**********************
      Growth
**********************/

int Neuron::growAxon(int length, double azimuth) {
   if (azimuth == -1) {azimuth = axon.Azimuth;}
   axon.Length  = length;
   axon.Azimuth = azimuth;
   axonEnd.CoordX = coord.CoordX + (int) double(length) * sin(azimuth);
   axonEnd.CoordY = coord.CoordY + (int) double(length) * cos(azimuth);

#ifdef TRACE
   printf("Cell: Axon end of neuron %d is (%d, %d) now\n", NeuronId, axonEnd.CoordX, axonEnd.CoordY);
#endif
   return axon.Length;
}

int Neuron::growDendr(int delta) {
#ifdef TRACE
   printf("Cell: Trying to grow dendrite of neuron %d. Dendrity radius was %d", NeuronId, dendrRad);
#endif
   dendrRad += delta;

#ifdef TRACE
   printf("and is %d now\n", getDendrRad());
#endif
   return dendrRad;
}

int Neuron::addConnection(Neuron *tmpConnection) {
   if (numberOfConnections >= MAXNUMBEROFCONNECTIONS) {return 0;}

#ifdef TRACE
   printf("Cell: Added connection number %d\n", numberOfConnections + 1);
#endif
   bool isAlreadyConnected = false;
   for(int i = 0; i < numberOfConnections; i++)
      if (connection[i]->getNeuronId() == tmpConnection->getNeuronId()) {isAlreadyConnected = true;}
   if (numberOfConnections < MAXNUMBEROFCONNECTIONSPERNEURON
   and isAlreadyConnected == false) {
      connection[numberOfConnections++] = tmpConnection;
   }
   return 0;
}

/**********************
      Firing
**********************/

bool Neuron::checkIfFired() {
   return isFired;
}

void Neuron::fire() {
   isFired = true;
}

void Neuron::spreadImpulse() {
   if (isFired and numberOfConnections > 0) {
      for(int i = 0; i < numberOfConnections; i++)
         connection[i]->fire();
   }
}

void Neuron::chargeBattery() {
   if (!(isFired)) {batteryCharge++;}
}

void Neuron::unchargeBattery() {
   if (isFired == true and batteryCharge > 0) {batteryCharge--;}
   if (batteryCharge == 0) {isFired = false;}
}


void Neuron::printConnections() {
   if (numberOfConnections > 0) {
         printf("Cell: Neuron %d is connected with %d neurons\n", NeuronId, numberOfConnections);
         for(int i = 0; i < numberOfConnections; i++)
            printf("Cell: Connection number %d is with neuron %d\n", i + 1, connection[i]->getNeuronId());
   }
}

/**********************
      Interface
**********************/

int Neuron::getNeuronId() {
   return NeuronId;
}

int Neuron::getAxonLength() {
   return axon.Length;
}

double Neuron::getAxonAzimuth() {
   return axon.Azimuth;
}

struct Coordinates Neuron::getAxonEnd() {
   return axonEnd;
}

int Neuron::getDendrRad() {
   return dendrRad;
}

int Neuron::getNumberOfConnections() {
   return numberOfConnections;
}

int Neuron::getBatteryCharge() {
   return batteryCharge;
}
