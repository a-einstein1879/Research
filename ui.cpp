#include "ui.h"
#include "cell.h"

#include <stdlib.h>
#include <stdio.h>


/*****************
      CLUI TODO: Change class to namespace
*****************/

void CLUI::printNeuronalNetwork(Neuron *neurons) {
   clearScreen();
   int numberOfNeurons = neurons->NumberOfNeurons - 1;
   printf("NumberOfNeurons = %d\n", numberOfNeurons);

   char Field[XMAXSIZE][YMAXSIZE];
   for(int i = 0; i < XMAXSIZE; i++)
      for(int j = 0; j < YMAXSIZE; j++)
         Field[i][j] = ' ';

   for(int i = 0; i < numberOfNeurons; i++) {
      struct Coordinates coord = neurons[i].getCoord();
      Field[coord.CoordX][coord.CoordY] = 'N';
   }

   for(int j = 0; j < YMAXSIZE; j++) {
      for(int i = 0; i < XMAXSIZE; i++)
         printf("%c\t", Field[i][j]);
      printf("\n");
   }
}

void CLUI::printNeuron() {};

void CLUI::clearScreen() {
   system("clear");
}

