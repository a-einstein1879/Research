#include "field.h"
#include "cell.h"
#include "cmn_functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*****************
      Field
*****************/

int Field::getNumberOfCells() {
   return numberOfCells;
};

/*****************
      NeuronField
*****************/

NeuronField::NeuronField() {
   numberOfCells = 0;
   maxNumberOfConnections = 0;

   for(int i = 0; i < XMAXSIZE; i++)
      for(int j = 0; j < YMAXSIZE; j++)
         for(int k = 0; k < FIELDNAMELENGTH; k++)
            neuronField[i][j][k] = EMPTYFIELDSYMBOL;

   neurons = new Neuron[numberOfCells];
};

void NeuronField::createNeuron() {
   if (numberOfCells < MAXNUMBEROFNEURONS) {
      Neuron *tmpNeurons;
      neurons->resetIdCounter();
      tmpNeurons = new Neuron[numberOfCells];
      for(int i = 0; i < numberOfCells; i++)
         *(tmpNeurons+i) = neurons[i];

      neurons->resetIdCounter();
      neurons = new Neuron[++numberOfCells];

      for(int i = 0; i < numberOfCells - 1; i++)
         neurons[i] = *(tmpNeurons+i);

      delete [] tmpNeurons;
   }
};

/**********************
      Growing
**********************/

int NeuronField::addNeuron(int x, int y) { //TODO: fix recursive bug. Add counter to prevent loop
   if (numberOfCells < MAXNUMBEROFNEURONS) {
      bool availability = false, randomity = false;
      if ((x == -1) and (y == -1)) {x = rand()%XMAXSIZE; y = rand()%YMAXSIZE; randomity = true;}
      if (getFieldType(x, y) == EMPTYFIELDSYMBOL) {availability = true;}

      if (availability == true) {
            createNeuron();
            neurons[numberOfCells - 1].setCoordinates(x, y);
            fillField(x, y, NEURONSYMBOL, numberOfCells - 1);
      }
      else {
         if (randomity == true)
            addNeuron();
         else {
            printf("Can`t create neuron here (%d, %d)\n", x, y);
         }
      }
   }
   return 0;
};

void NeuronField::fillField(int x, int y, char type, int neuronId) {
   char id[FIELDNAMELENGTH];
   snprintf(id, FIELDNAMELENGTH, "%d", neuronId);
   neuronField[x][y][0] = type;
   for(int i = 1; i < FIELDNAMELENGTH; i++)
      neuronField[x][y][i] = id[i-1];
};

void NeuronField::growAxon(int NeuronId, int delta, double azimuth) {
   Neuron *neuron;
   neuron = getNeuronById(NeuronId);
   struct Coordinates coord;
   coord = neuron->getCoord();
   if (azimuth == -1) {azimuth = neuron->getAxonAzimuth();}
   else               {coord = neuron->getAxonEnd();}
   if (azimuth == -1) {azimuth = 2 * M_PI * double (rand()%AXONANGLEPRECISENESS + 1) / AXONANGLEPRECISENESS;} 
                      /* If it`s still -1 it means there was no azimuth. We choose random direction */
   int axonLength = neuron->getAxonLength();

#ifdef TRACE
   printf("Axon end coordinates = (%d, %d).\tAxonLength is %d.\tAxon azimuth is %.3e\n", coord.CoordX, coord.CoordY, axonLength, azimuth);
#endif

   for(int i = axonLength + 1; i < axonLength + delta + 1; i++) {
      int newx, newy;
      newx = coord.CoordX + i * sin(azimuth);
      newy = coord.CoordY + i * cos(azimuth);

      if (newx > (XMAXSIZE - 1) or newx < 0 or newy > (YMAXSIZE - 1) or newy < 0 or ( newx == coord.CoordX and newy == coord.CoordY ) ) {continue;}
      neuron->growAxon(i, azimuth);
      char stat = getFieldType(newx, newy);
      if (stat == NEURONSYMBOL or stat == DENDRSYMBOL) {

#ifdef TRACE
         printf("Added connection. newx = %d\tnewy = %d\tNeuronId = %d\n", newx, newy, NeuronId);
#endif

         neuron->addConnection(getNeuronByField(newx, newx));
         int NumberOfConnections = neuron->getNumberOfConnections();
#ifdef TRACE
         if (maxNumberOfConnections < NumberOfConnections) {printf("maxNumberOfConnections increased to %d\n", NumberOfConnections);}
#endif
         maxNumberOfConnections = (maxNumberOfConnections < NumberOfConnections) ? NumberOfConnections : maxNumberOfConnections;
      }
      else {
         fillField(newx, newy, AXONSYMBOL, NeuronId);

#ifdef TRACE
         printf("newx = %d\tnewy = %d\tNeuronId = %d\n", newx, newy, NeuronId);
#endif

      }
   }
};

void NeuronField::growAxons(int maxLength) {
};

void NeuronField::growDendr(int NeuronId, int delta) {
};

/**********************
      Firing
**********************/

void NeuronField::fireNeuron(int NeuronId) {
   if (NeuronId == -1) {NeuronId = rand()%numberOfCells;}
   Neuron* neuron;
   neuron = getNeuronById(NeuronId);
   if ( !(neuron->checkIfFired()) ) {neuron->fire();}
};

void NeuronField::chargeBatteries() {
   for(int i = 0; i < numberOfCells; i++)
      neurons[i].chargeBattery();
};

void NeuronField::unchargeBatteries() {
   for(int i = 0; i < numberOfCells; i++)
      neurons[i].unchargeBattery();
};

/**********************
      Interface
**********************/

bool NeuronField::getSpotStat(int x, int y) {
   Neuron* neuron;
   neuron = getNeuronByField(x, y);
   return neuron->checkIfFired();
};

Neuron* NeuronField::getNeuronById(int neuronId) {
   return neurons + neuronId;
};

char NeuronField::getFieldType(int x, int y) {
   return neuronField[x][y][0];
};

Neuron* NeuronField::getNeuronByField(int x, int y) {
   Neuron* ret = NULL;


   int neuronId = CharToInt(neuronField[x][y] + 1, FIELDNAMELENGTH - 1);

   ret = neurons + neuronId;
   return ret;
};

/**********************
      Print
**********************/

void NeuronField::printFieldStat(int time) {
   system("clear");
   if (time != -1) {printf("time = %d\n", time);}
   printf("numberOfCells = %d\n", numberOfCells);
   for(int i = 0; i < numberOfCells; i++) {
      struct Coordinates coord = neurons[i].getCoord();
      int axonLength           = neurons[i].getAxonLength();
      double axonAzimuth       = neurons[i].getAxonAzimuth();
      int batteryCharge        = neurons[i].getBatteryCharge();
      printf("Coord[%d] = (%d,%d). AxonLength = %d. AxonAzimuth = %.3e. BatteryCharge = %d\n", i, coord.CoordX, coord.CoordY, axonLength, axonAzimuth, batteryCharge);
   }
};
