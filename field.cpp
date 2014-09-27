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
}

/*****************
      NeuronField
*****************/

NeuronField::NeuronField() {
   numberOfCells = 0;
   maxNumberOfConnections = 0;

   for(int i = 0; i < XMAXSIZE; i++)
      for(int j = 0; j < YMAXSIZE; j++)
         neuronType[i][j] = EMPTYFIELDSYMBOL;

   for(int i = 0; i < XMAXSIZE; i++)
      for(int j = 0; j < YMAXSIZE; j++)
         neuronIds[i][j] = NEURONIDINITIALVALUE;

   neurons = new Neuron[numberOfCells];
}

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
}

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
}

void NeuronField::fillField(int x, int y, char type, int neuronId) {

#ifdef TRACE
   printf("Field: Field (%d, %d) was `%c` type", x, y, getFieldType(x, y));
#endif

   neuronType[x][y] = type;
   neuronIds[x][y]  = neuronId;

#ifdef TRACE
   printf(" and now it`s `%c` type with id %d\n", getFieldType(x, y), neuronIds[x][y]);
#endif

}

void NeuronField::growAxon(int NeuronId, int delta, double azimuth) {
   Neuron *neuron;
   neuron = getNeuronById(NeuronId);
   if (neuron == NULL) {

#ifdef TRACE
   printf("Field: growAxon: getNeuronById returned NULL pointer\n");
#endif
      return;
   }

   struct Coordinates coord;
   coord = neuron->getCoord();
   if (azimuth == -1) {azimuth = neuron->getAxonAzimuth();}
   else               {coord = neuron->getAxonEnd();}
   if (azimuth == -1) {azimuth = 2 * M_PI * double (rand()%AXONANGLEPRECISENESS + 1) / AXONANGLEPRECISENESS;} 
                      /* If it`s still -1 it means there was no azimuth. We choose random direction */
   int axonLength = neuron->getAxonLength();

#ifdef TRACE
   printf("Field: Axon starts growing. Axon end coordinates = (%d, %d).\tAxonLength is %d.\tAxon azimuth is %.3e\n", coord.CoordX, coord.CoordY, axonLength, azimuth);
#endif

   for(int i = axonLength + 1; i < axonLength + delta + 1; i++) {
      int newx, newy;
      newx = coord.CoordX + i * sin(azimuth);
      newy = coord.CoordY + i * cos(azimuth);

      if (newx > (XMAXSIZE - 1) or newx < 0 or newy > (YMAXSIZE - 1) or newy < 0 or ( newx == coord.CoordX and newy == coord.CoordY ) ) {continue;}
      neuron->growAxon(i, azimuth);
      char stat = getFieldType(newx, newy);
      if (stat == NEURONSYMBOL or stat == DENDRSYMBOL) {
         Neuron* neu = getNeuronByField(newx, newy);
         if (neu == NULL) {

#ifdef TRACE
            printf("Field: Going to next iteration due to NULL return value\n");
#endif

            continue;
}
         neuron->addConnection(neu);

#ifdef TRACE
         printf("Field: Added connection. From neuron %d to neuron %d in (%d, %d)\n", NeuronId, neu->getNeuronId(), newx, newy);
#endif

         int NumberOfConnections = neuron->getNumberOfConnections();

#ifdef TRACE
         if (maxNumberOfConnections < NumberOfConnections) {printf("Field: maxNumberOfConnections increased to %d\n", NumberOfConnections);}
#endif

         maxNumberOfConnections = (maxNumberOfConnections < NumberOfConnections) ? NumberOfConnections : maxNumberOfConnections;
      }
      else {
         fillField(newx, newy, AXONSYMBOL, NeuronId);
      }
   }
}

void NeuronField::growDendr(int NeuronId, int delta) {
   Neuron* neuron = getNeuronById(NeuronId);
   struct Coordinates coord;
   coord = neuron->getCoord();
   int dendrRad = neuron->getDendrRad();

#ifdef TRACE
         printf("Field: Starting growing neuron %d dendrite.\n", NeuronId);
#endif

   neuron->growDendr(delta);
   for(int i = dendrRad; i < dendrRad + delta; i++) {
      for(int j = 0; j < DENDRITEANGLEPRECISENESS; j++) {         
         double angle = 2 * M_PI * double(j) / DENDRITEANGLEPRECISENESS;
         int newx = 0, newy = 0;
         newx = coord.CoordX + i * sin(angle);
         newy = coord.CoordY + i * cos(angle);

         if (newx > (XMAXSIZE - 1) or newx < 0 or newy > (YMAXSIZE - 1) or newy < 0
             or ( newx == coord.CoordX and newy == coord.CoordY )) {
             continue;
         }

         char stat = getFieldType(newx, newy);
         if (stat == NEURONSYMBOL or stat == DENDRSYMBOL) {
            Neuron* neuro;
            neuro = getNeuronByField(newx, newy);
            neuro->addConnection( getNeuronById(NeuronId) );

#ifdef TRACE
         printf("Field: Adding connection from neuron %d to neuron %d\n", neuro->getNeuronId(), NeuronId);
#endif

         int NumberOfConnections = neuro->getNumberOfConnections();

#ifdef TRACE
         if (maxNumberOfConnections < NumberOfConnections) {printf("maxNumberOfConnections increased to %d\n", NumberOfConnections);}
#endif
         maxNumberOfConnections = (maxNumberOfConnections < NumberOfConnections) ? NumberOfConnections : maxNumberOfConnections;

         }
         else {
            fillField(newx, newy, DENDRSYMBOL, neuron->getNeuronId());
         }
      }
   }
}

/**********************
      Firing
**********************/

void NeuronField::fireNeuron(int NeuronId) {
   if (NeuronId == -1) {NeuronId = rand()%numberOfCells;}
   Neuron* neuron;
   neuron = getNeuronById(NeuronId);

   if (neuron == NULL) {
#ifdef TRACE
   printf("Field: fireNeuron: getNeuronById returned NULL pointer\n");
#endif
      return;
   }

   if ( !(neuron->checkIfFired()) ) {neuron->fire();}
}

void NeuronField::spreadImpulse(int NeuronId) {
   if (NeuronId == -1) {
      for(int i = 0; i < numberOfCells; i++)
         neurons[i].spreadImpulse();
   }
   else {
      Neuron* neu = getNeuronById(NeuronId);
      if (neu != NULL) {
         if ( !(neu->checkIfFired()) ) {neu->fire();}
         neu->spreadImpulse();
      }
   }
}

void NeuronField::chargeBatteries() {
   for(int i = 0; i < numberOfCells; i++)
      neurons[i].chargeBattery();
}

void NeuronField::unchargeBatteries() {
   for(int i = 0; i < numberOfCells; i++)
      neurons[i].unchargeBattery();
}

/**********************
      Interface
**********************/

bool NeuronField::getSpotStat(int x, int y) {
   Neuron* neuron;
   neuron = getNeuronByField(x, y);
   if (neuron == NULL) {return 0;}
   return neuron->checkIfFired();
}

Neuron* NeuronField::getNeuronById(int neuronId) {
   if ( neuronId < 0 or neuronId > numberOfCells ) {return NULL;}
   Neuron* neuro = NULL;

   int realId = neurons[neuronId].getNeuronId();
   if ( realId == neuronId) {neuro = neurons + neuronId;}
   else {
      for(int i = 0; i < numberOfCells; i++) {
         int realId = neurons[i].getNeuronId();
         if ( realId == neuronId ) {neuro = neurons + i;}
      }
   }

#ifdef TRACE
         if ( neuro == NULL ) {printf("Field: Can`t find a neuron with neuronId %d\n", neuronId);}
#endif

   return neuro;
}

char NeuronField::getFieldType(int x, int y) {
   return neuronType[x][y];
}

Neuron* NeuronField::getNeuronByField(int x, int y) {

#ifdef TRACE
   printf("Field: Getting neuron by field (%d, %d)\n", x, y);
#endif
   Neuron* ret = NULL;

   if ( getFieldType(x, y) != EMPTYFIELDSYMBOL ) {
      int neuronId = neuronIds[x][y];
      ret = getNeuronById(neuronId);
   }

#ifdef TRACE
         if (ret == NULL) {printf("Field: Can`t get neuron in (%d, %d)\n",     x, y);}
         else             {printf("Field: Trying to get neuron in (%d, %d)\n", x, y);}
#endif

   return ret;
}

bool NeuronField::isAnyPlaceLeft() {
   bool isAnyPlace = false;
   if ( numberOfCells < (MAXNUMBEROFNEURONS) ) {isAnyPlace = true;}
   return isAnyPlace;
}

/**********************
      Print. TODO:Can be really good to move it to UI
**********************/

void NeuronField::printFieldStat(int time) {
   if (time != -1) {printf("time = %d\n", time);}
   printf("numberOfCells = %d\nmaxNumberOfConnections = %d\n", numberOfCells, maxNumberOfConnections);
#ifdef TEST
   for(int i = 0; i < numberOfCells; i++) {
      struct Coordinates coord = neurons[i].getCoord();
      int axonLength           = neurons[i].getAxonLength();
      double axonAzimuth       = neurons[i].getAxonAzimuth();
      int dendrRad             = neurons[i].getDendrRad();
      int batteryCharge        = neurons[i].getBatteryCharge();
      int numberOfConnections  = neurons[i].getNumberOfConnections();
      printf("Field: Coord[%d] = (%d,%d). AxonLength = %d. AxonAzimuth = %.3e. DendriteRad = %d. BatteryCharge = %d. NumberOfConnections = %d\n", 
                     i, coord.CoordX, coord.CoordY, axonLength, axonAzimuth, dendrRad, batteryCharge, numberOfConnections);
      if (numberOfConnections > 0) { neurons[i].printConnections(); }
   }
#endif
}
