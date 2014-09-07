#ifndef CMN_STRUCT_H
#define CMN_STRUCT_H

#define XMAXSIZE 15
#define YMAXSIZE 15
#define FIELDNAMELENGTH (1 + 1) //1 for type as: N, A, D, E; 1 for id length
#define PRECISENESS 1
#define MAXNUMBEROFNEURONS 3
#define FIRSTNEURONNUMBER 0

struct Coordinates {
   int CoordX;
   int CoordY;
};

struct Axon {
   int Length;
   double Azimuth;
};

#endif
