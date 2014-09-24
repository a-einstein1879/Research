#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cmn_struct.h"


#define NEURONGROWTHCHARACTERTIME         10
#define AXONGROWTHCHARACTERTIME           100
#define SPONTANEOUSACTIVITYCHARACTERTIME  10
#define CHARGEBATTERIESCHARACTERTIME      5
#define SPREADIMPULSECHARACTERTIME        1

#define DELAYTIME             50000

#define NEURONGROWTH          false
#define AXONGROWTH            false
#define SPONTANEOUSACTIVITY   true
#define CHARGEBATTERIES       true
#define SPREADIMPULSE         false

class Processor {
private:
   struct Process neuronGrowth, axonGrowth, spontaneousActivity, chargeBatteries, spreadImpulse;
   void RunNeuronGrowth();
   void RunAxonGrowth();
public:
   Processor();
   void Run();
};

#endif
