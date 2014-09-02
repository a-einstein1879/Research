#include "prog.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
using namespace std;

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
   if (NumberOfNeurons<MAXNUMBEROFNEURONS) {
      NeuronId = NumberOfNeurons++;
      printf("NeuronId = %d\n", NeuronId);

      if ((x==-1) and (y==-1)) {x = rand()%XMAXSIZE; y = rand()%YMAXSIZE;}
      coord.CoordX = x;
      coord.CoordY = y;
      printf("Coord = (%d,%d)\n", coord.CoordX, coord.CoordY);
   }
   else { //TODO:Add destructor calling for not creating new object
      printf("Can`t create a new neuron. Maximum number of cells exceeded\n");
   }
}

void Neuron::growAxon() {};
void Neuron::growDendr() {};

int Neuron::getNeuronId() {
   return NeuronId;
};
void Neuron::CheckForNewNeuroConnection(struct DendrArea dendrArea) {};

/*****************
      Connection
*****************/

int Connection::getSourceID() {
   return SourceID;
}

int Connection::getDestinationID() {
   return DestinationID;
}

/*****************
      NeuroConnection
*****************/

int NeuroConnection::getDelay() {
   return delay;
}

double NeuroConnection::getProbability() {
   return probability;
}

/*****************
      CLUI TODO: Change class to namespace
*****************/

void CLUI::printNeuronalNetwork(Neuron *neurons) {
   clearScreen();
   int numberOfNeurons = neurons->NumberOfNeurons - 1;
   printf("NumberOfNeurons = %d\n", numberOfNeurons);

   int Field[XMAXSIZE][YMAXSIZE];
   for(int i = 0; i < XMAXSIZE; i++)
      for(int j = 0; j < YMAXSIZE; j++)
         Field[i][j] = 0;

   for(int i = 0; i < numberOfNeurons; i++) {
      struct Coordinates coord = neurons[i].getCoord();
      Field[coord.CoordX][coord.CoordY] = 1;
   }

   for(int j = 0; j < YMAXSIZE; j++) {
      for(int i = 0; i < XMAXSIZE; i++)
         printf("%d\t", Field[i][j]);
      printf("\n");
   }
}

void CLUI::printNeuron() {};

void CLUI::clearScreen() {
   system("clear");
}

/*****************
      Main
*****************/

int main() {
   srand (time(NULL));
   int a=rand();
   Neuron neurons[MAXNUMBEROFNEURONS];
   CLUI ui;
   ui.printNeuronalNetwork(neurons);
   return 0;
}
