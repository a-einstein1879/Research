#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cmn_struct.h"


#define NEURONGROWTHCHARACTERTIME         20
#define AXONGROWTHCHARACTERTIME           5
#define SPONTANEOUSACTIVITYCHARACTERTIME  1
#define CHARGEBATTERIESCHARACTERTIME      2

#define DELAYTIME             5000

#define NEURONGROWTH          true
#define AXONGROWTH            true
#define SPONTANEOUSACTIVITY   true
#define CHARGEBATTERIES       true

class Processor {
private:
   struct Process neuronGrowth, axonGrowth, spontaneousActivity, chargeBatteries;
   void RunNeuronGrowth();
   void RunAxonGrowth();
public:
   Processor();
   void Run();
};

#endif
