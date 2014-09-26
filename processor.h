#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cmn_struct.h"


#define NEURONGROWTHCHARACTERTIME         20
#define AXONGROWTHCHARACTERTIME           5
#define DENDRGROWTHCHARACTERTIME          10
#define SPONTANEOUSACTIVITYCHARACTERTIME  1
#define CHARGEBATTERIESCHARACTERTIME      2
#define SPREADIMPULSECHARACTERTIME        1

#define DELAYTIME             5000

#define NEURONGROWTH          true
#define AXONGROWTH            true
#define DENDRGROWTH           true
#define SPONTANEOUSACTIVITY   false
#define CHARGEBATTERIES       false
#define SPREADIMPULSE         false

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
