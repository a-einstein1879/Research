#ifndef CMN_STRUCT_H
#define CMN_STRUCT_H

#define XMAXSIZE 10
#define YMAXSIZE 10
#define FIELDNAMELENGTH (1 + 1) //1 for type as: N, A, D, E; 1 for id length
#define PRECISENESS 1
#define MAXNUMBEROFNEURONS 3
#define FIRSTNEURONNUMBER 1

struct Coordinates {
   int CoordX;
   int CoordY;
};

struct Axon {
   int Length;
   double Azimuth;
   bool Exist;
};

struct DendrArea {
   int Preciseness;
   int Area[XMAXSIZE][YMAXSIZE];
};

#endif
