#ifndef CMN_STRUCT_H
#define CMN_STRUCT_H


#define XMAXSIZE 20
#define YMAXSIZE 20
#define MAXNUMBEROFNEURONS 3
#define MAXNUMBEROFCONNECTIONS 5
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
