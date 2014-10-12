#ifndef CMN_STRUCT_H
#define CMN_STRUCT_H

#include "cmn_defines.h"

struct Process {
   int  ProcessId;
   int  TimeLeft;
   bool Enabled;
};

struct Coordinates {
   int CoordX;
   int CoordY;
};

struct Axon {
   int    Length;
   double Azimuth;
};

#endif
