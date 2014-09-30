#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cmn_struct.h"
#include "field.h"

#define NEURONGROWTHCHARACTERTIME         1
#define AXONGROWTHCHARACTERTIME           5
#define DENDRGROWTHCHARACTERTIME          10
#define SPONTANEOUSACTIVITYCHARACTERTIME  10
#define CHARGEBATTERIESCHARACTERTIME      8
#define SPREADIMPULSECHARACTERTIME        5

#define DELAYTIME             10000

#define NEURONGROWTH          false
#define AXONGROWTH            false
#define DENDRGROWTH           false
#define SPONTANEOUSACTIVITY   false
#define CHARGEBATTERIES       true
#define SPREADIMPULSE         true

class Processor {
private:
   struct Process neuronGrowth, axonGrowth, dendrGrowth, spontaneousActivity, chargeBatteries, spreadImpulse;
   void RunNeuronGrowth();
   void RunAxonGrowth();
   void Scenario1(NeuronField field);
public:
   Processor();
   void Run();
};

#endif
