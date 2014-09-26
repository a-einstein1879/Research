#ifndef CMN_STRUCT_H
#define CMN_STRUCT_H

#define XMAXSIZE                          5
#define YMAXSIZE                          20

#define FIELDNAMELENGTH                   (1 + 2) //1 for type as: N, A, D, E; 1 for id length
#define IDOFFSET                          1
/* getNeuronByField function uses this parametrs. Be carefull changing it */

#define MAXNUMBEROFNEURONS                3
#define FIRSTNEURONNUMBER                 0

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
