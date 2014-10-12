#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cmn_struct.h"
#include "field.h"
#include "cmn_defines.h"

class Processor {
private:
   struct Process neuronGrowth, axonGrowth, dendrGrowth, spontaneousActivity, chargeBatteries, spreadImpulse;
   void RunNeuronGrowth();
   void RunAxonGrowth();
/* Scenarios */
   void BuildScenario1(NeuronField* field);
   void BuildScenario2(NeuronField* field);
public:
   Processor();
   void Run();
};

#endif
