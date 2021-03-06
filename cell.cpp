#include "cell.h"
#include "cmn_struct.h"
#include "cmn_defines.h"

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
      if(x != -1 and y != -1) {PRINTTRACE("Cell", "Added neuron number %d with coordinates x = %d, y = %d\n", NeuronId, x, y);}
      else                    {PRINTTRACE("Cell", "Added neuron number %d without place\n", NeuronId);}
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
   else {
      PRINTTRACE("Cell", "Can`t create a new neuron with counter %d. Maximum number of cells exceeded\n", NeuronCounter);
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
      PRINTTRACE("Cell", "Coordinates of neuron number %d were changed. New coordinates are x = %d, y = %d\n", NeuronId, x, y);
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
   axonEnd.CoordX = coord.CoordX + (int) double(length) * sin(azimuth);
   axonEnd.CoordY = coord.CoordY + (int) double(length) * cos(azimuth);

   if(axonEnd.CoordX <= 0 or axonEnd.CoordX >= XMAXSIZE or axonEnd.CoordY <= YMAXSIZE or axonEnd.CoordY >= YMAXSIZE) {return -1;}
   axon.Length  = length;
   axon.Azimuth = azimuth;

#ifdef TRACE
   PRINTTRACE("Cell", "Axon end of neuron %d is (%d, %d) now\n", NeuronId, axonEnd.CoordX, axonEnd.CoordY);
#endif
   return axon.Length;
}

int Neuron::growDendr(int delta) {
#ifdef TRACE
   PRINTTRACE("Cell", "Trying to grow dendrite of neuron %d. Dendrite radius was %d", NeuronId, dendrRad);
#endif
   dendrRad += delta;

#ifdef TRACE
   PRINTTRACE("Cell", "and is %d now\n", getDendrRad());
#endif
   return dendrRad;
}

int Neuron::addConnection(Neuron *tmpConnection) {
   if (numberOfConnections > MAXNUMBEROFCONNECTIONSPERNEURON) {return 0;}

#ifdef TRACE
   PRINTTRACE("Cell", "Added connection number %d\n", numberOfConnections + 1);
#endif

   bool isAlreadyConnected = false;
   for(int i = 0; i < numberOfConnections; i++) {
      if (connection[i]->getNeuronId() == tmpConnection->getNeuronId()) {
         isAlreadyConnected = true;
      }
   }

   if (    numberOfConnections < MAXNUMBEROFCONNECTIONSPERNEURON
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

void Neuron::chargeBattery(int delta) {
   if (!(isFired)) {batteryCharge += delta;}
}

void Neuron::unchargeBattery() {
   if (isFired == true and batteryCharge > 0) {batteryCharge--;}
   if (batteryCharge == 0) {isFired = false;}
}


void Neuron::printConnections() {
#ifdef TRACE
   if (numberOfConnections > 0) {
         PRINTTRACE("Cell", "Neuron %d is connected with %d neurons\n", NeuronId, numberOfConnections);
         for(int i = 0; i < numberOfConnections; i++)
            PRINTTRACE("Cell", "Connection number %d is with neuron %d\n", i + 1, connection[i]->getNeuronId());
   }
#endif
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
