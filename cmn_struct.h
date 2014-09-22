#ifndef CMN_STRUCT_H
#define CMN_STRUCT_H

#define XMAXSIZE 10
#define YMAXSIZE 10
#define FIELDNAMELENGTH (1 + 1) //1 for type as: N, A, D, E; 1 for id length
#define MAXNUMBEROFNEURONS 5
#define FIRSTNEURONNUMBER 0

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
