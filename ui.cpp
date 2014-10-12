#include "ui.h"
#include "cell.h"

#include <stdlib.h>

#include <graphics.h>
#include <X11/Xlib.h> //for XinitThreads function

/*****************
      CLUI TODO: Change class to namespace
*****************/

void CLUI::printNeuronalNetwork(NeuronField Field, int time) {
   clearScreen();

   char field[XMAXSIZE][YMAXSIZE];

   for(int x = 0; x < XMAXSIZE; x++)
      for(int y = 0; y < YMAXSIZE; y++) {
         field[x][y] = Field.getFieldType(x, y);
         if ( field[x][y] != EMPTYFIELDSYMBOL ) {field[x][y] = Field.getSpotStat(x, y) ? FIREDSYMBOL : field[x][y];}
      }   

   Message("\t");
   for(int i = 0; i < XMAXSIZE; i++)
      Print("%d ", i);

   for(int j = 0; j < YMAXSIZE; j++) {
      Print("\n%d\t", j);
      for(int i = 0; i < XMAXSIZE; i++)
         Print("%c ", field[i][j]);
   }
   Message("\n");
   Field.printFieldStat(time);
}

void CLUI::clearScreen() {
   system("clear");
}


/*****************
      GUI TODO: Change class to namespace
*****************/

GUI::GUI() {
   XInitThreads();
   int gd=DETECT,gm;
   initgraph(&gd,&gm,NULL);
}

GUI::~GUI() {
   closegraph();
}

void GUI::clearScreen() {
   for(int i = 0; i < XMAXSIZE; i++)
      for(int j = 0; j < YMAXSIZE; j++)
         putpixel(i, j, BLACK);
}

void GUI::printNeuronalNetwork(NeuronField Field, int time) {

   char field[XMAXSIZE][YMAXSIZE];

   for(int x = 0; x < XMAXSIZE; x++)
      for(int y = 0; y < YMAXSIZE; y++) {
         field[x][y] = Field.getFieldType(x, y);
         if ( field[x][y] != EMPTYFIELDSYMBOL ) {field[x][y] = Field.getSpotStat(x, y) ? FIREDSYMBOL : field[x][y];}
      }

   system("clear");
   Field.printFieldStat(time);
//   if ( time%( Field.getMaxNumberOfConnections() < 10 ? 50 : 5 ) != 0 ) {return;}
   for(int j = 0; j < YMAXSIZE; j++)
      for(int i = 0; i < XMAXSIZE; i++) {
         if (field[i][j] == NEURONSYMBOL)       {putpixel(i, j, NEURONCOLOR);    };
         if (field[i][j] == DENDRSYMBOL)        {putpixel(i, j, DENDRITECOLOR);  };
         if (field[i][j] == AXONSYMBOL)         {putpixel(i, j, AXONCOLOR);      };
         if (field[i][j] == FIREDSYMBOL)        {putpixel(i, j, FIRINGCOLOR);    };
//         if (field[i][j] == EMPTYFIELDSYMBOL)   {putpixel(i, j, EMPTYFIELDCOLOR);}; /* slows program too much. Needs thinking */
      }
}
