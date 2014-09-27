#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cmn_struct.h"

#define NEURONGROWTHCHARACTERTIME         5
#define AXONGROWTHCHARACTERTIME           15
#define DENDRGROWTHCHARACTERTIME          30
#define SPONTANEOUSACTIVITYCHARACTERTIME  10
#define CHARGEBATTERIESCHARACTERTIME      8
#define SPREADIMPULSECHARACTERTIME        1

#define DELAYTIME             1

#define NEURONGROWTH          true
#define AXONGROWTH            true
#define DENDRGROWTH           true
#define SPONTANEOUSACTIVITY   true
#define CHARGEBATTERIES       true
#define SPREADIMPULSE         true

class Processor {
private:
   struct Process neuronGrowth, axonGrowth, dendrGrowth, spontaneousActivity, chargeBatteries, spreadImpulse;
   void RunNeuronGrowth();
   void RunAxonGrowth();
public:
   Processor();
   void Run();
};

#endif
