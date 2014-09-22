#include "processor.h"
#include "cmn_struct.h"
#include "field.h"
#include "ui.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

Processor::Processor() {
   neuronGrowth.Enabled          = NEURONGROWTH;
   neuronGrowth.TimeLeft         = rand()%NEURONGROWTHCHARACTERTIME;

   axonGrowth.Enabled            = AXONGROWTH;
   axonGrowth.TimeLeft           = rand()%AXONGROWTHCHARACTERTIME;

   spontaneousActivity.Enabled   = SPONTANEOUSACTIVITY;
   spontaneousActivity.TimeLeft  = rand()%SPONTANEOUSACTIVITYCHARACTERTIME;

   chargeBatteries.Enabled       = CHARGEBATTERIES;
   chargeBatteries.TimeLeft      = rand()%CHARGEBATTERIESCHARACTERTIME;

   spreadImpulse.Enabled         = SPREADIMPULSE;
   spreadImpulse.TimeLeft        = rand()%SPREADIMPULSECHARACTERTIME;
};

void Processor::RunNeuronGrowth() {};
void Processor::RunAxonGrowth() {};

void Processor::Run() {
   srand (time(NULL));
   NeuronField field1;
   CLUI ui;
   int time = 0;

   field1.addNeuron(2, 10);
   field1.addNeuron(2, 12);
   field1.growAxon(0, 3, 0);
   while(time < 1000) {
      /* actions */
      if (neuronGrowth.TimeLeft             == 0 and
          neuronGrowth.Enabled              == true) {
         field1.addNeuron(); 
         neuronGrowth.TimeLeft         = rand()%NEURONGROWTHCHARACTERTIME;
      }
      if (axonGrowth.TimeLeft               == 0 and
          axonGrowth.Enabled                == true) {
         field1.growAxon(rand()%field1.getNumberOfCells(), 1); 
         axonGrowth.TimeLeft           = rand()%AXONGROWTHCHARACTERTIME;
      }
      if (spontaneousActivity.TimeLeft      == 0
          and spontaneousActivity.Enabled   == true
          and time > 50) {
         field1.fireNeuron();
         spontaneousActivity.TimeLeft  = rand()%SPONTANEOUSACTIVITYCHARACTERTIME;
      }
      if (chargeBatteries.TimeLeft          == 0 and
          chargeBatteries.Enabled           == true
          and time > 70) {
         field1.chargeBatteries();
         chargeBatteries.TimeLeft      = rand()%CHARGEBATTERIESCHARACTERTIME;
      }
      if (spreadImpulse.TimeLeft            == 0 and
          spreadImpulse.Enabled             == true
          and time > 50) {
         field1.spreadImpulse();
         spreadImpulse.TimeLeft        = rand()%SPREADIMPULSECHARACTERTIME;
      }

      /* post actions */
      if (neuronGrowth.TimeLeft          != 0) {neuronGrowth.TimeLeft--;       }
      if (axonGrowth.TimeLeft            != 0) {axonGrowth.TimeLeft--;         }
      if (spontaneousActivity.TimeLeft   != 0) {spontaneousActivity.TimeLeft--;}
      if (chargeBatteries.TimeLeft       != 0) {chargeBatteries.TimeLeft--;    }
      if (spreadImpulse.TimeLeft         != 0) {spreadImpulse.TimeLeft--;      }
      field1.unchargeBatteries();

      /* printing actions */
      ui.printNeuronalNetwork(field1, time++);

      usleep(DELAYTIME);
   }
};
