#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cmn_struct.h"
#include "field.h"

#define NEURONGROWTHCHARACTERTIME         1
#define AXONGROWTHCHARACTERTIME           5
#define DENDRGROWTHCHARACTERTIME          10
#define SPONTANEOUSACTIVITYCHARACTERTIME  20
#define CHARGEBATTERIESCHARACTERTIME      7
#define SPREADIMPULSECHARACTERTIME        5

#define MAXTIME               250000
#define DELAYTIME             10000

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
   void Scenario1(NeuronField field);
public:
   Processor();
   void Run();
};

#endif
