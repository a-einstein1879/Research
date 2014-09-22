#include "processor.h"
#include "cmn_struct.h"
#include "field.h"
#include "ui.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*struct Process {
   int  ProcessId;
   int  TimeLeft;
   bool Enabled;
};

#define NEURONGROWTHCHARACTERTIME 10
#define AXONGROWTHCHARACTERTIME   1
#define DELAYTIME                 1000

#define NEURONGROWTH true
#define AXONGROWTH   true
   struct Process neuronGrowth, axonGrowth;
*/

Processor::Processor() {
   neuronGrowth.Enabled  = NEURONGROWTH;
   neuronGrowth.TimeLeft = rand()%NEURONGROWTHCHARACTERTIME;

   axonGrowth.Enabled   = AXONGROWTH;
   axonGrowth.TimeLeft  = rand()%AXONGROWTHCHARACTERTIME;
};

void Processor::RunNeuronGrowth() {};
void Processor::RunAxonGrowth() {};

void Processor::Run() {
   srand (time(NULL));
   NeuronField field1;
   field1.addNeuron();
   CLUI ui;
   int time = 0;

   while(time < 1000) {
      /* actions */
      if (neuronGrowth.TimeLeft == 0 and neuronGrowth.Enabled == true) {
         field1.addNeuron(); 
         neuronGrowth.TimeLeft = rand()%NEURONGROWTHCHARACTERTIME;
      }
      if (axonGrowth.TimeLeft   == 0 and axonGrowth.Enabled   == true) {
         field1.growAxon(rand()%field1.getNumberOfCells(), 1); 
         axonGrowth.TimeLeft  = rand()%AXONGROWTHCHARACTERTIME;
      }

      /* printing actions */
      ui.printNeuronalNetwork(field1);
      field1.printFieldStat(time++);

      /* post actions */
      if (neuronGrowth.TimeLeft != 0) {neuronGrowth.TimeLeft--;}
      if (axonGrowth.TimeLeft   != 0) {axonGrowth.TimeLeft--;  }
      usleep(DELAYTIME);
   }
};
