#ifndef CMN_STRUCT_H
#define CMN_STRUCT_H


#define XMAXSIZE 600
#define YMAXSIZE 400
#define MAXNUMBEROFNEURONS 30
#define MAXNUMBEROFCONNECTIONS 15
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
