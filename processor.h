#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cmn_struct.h"


#define NEURONGROWTHCHARACTERTIME 10
#define AXONGROWTHCHARACTERTIME   1
#define DELAYTIME                 5000

#define NEURONGROWTH true
#define AXONGROWTH   true

class Processor {
private:
   struct Process neuronGrowth, axonGrowth;
   void RunNeuronGrowth();
   void RunAxonGrowth();
public:
   Processor();
   void Run();
};

#endif
