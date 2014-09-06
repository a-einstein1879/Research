#include "ui.h"
#include "cell.h"

#include <stdlib.h>
#include <stdio.h>


/*****************
      CLUI TODO: Change class to namespace
*****************/

void CLUI::printNeuronalNetwork(NeuronField Field) {
//   clearScreen();

   char field[XMAXSIZE][YMAXSIZE];

   for(int x = 0; x < XMAXSIZE; x++)
      for(int y = 0; y < YMAXSIZE; y++)
         field[x][y] = Field.getFieldStat(x, y);

   printf("\n\n\t");
   for(int i = 0; i < XMAXSIZE; i++)
      printf("%d\t", i);

   for(int j = 0; j < YMAXSIZE; j++) {
      printf("\n%d\t", j);
      for(int i = 0; i < XMAXSIZE; i++)
         printf("%c\t", field[i][j]);
   }
   printf("\n");
}

void CLUI::printNeuron() {};

void CLUI::clearScreen() {
   system("clear");
}

