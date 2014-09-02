#define XMAXSIZE 4
#define YMAXSIZE 4
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
};

struct DendrArea {
   int Preciseness;
   int Area[XMAXSIZE][YMAXSIZE];
};

class Cell {
protected:
   struct Coordinates coord;
public:
   struct Coordinates getCoord();
};

class Neuron : public Cell {
private:
   int NeuronId;
   static DendrArea dendrArea;
   int dendrRad;
   struct Axon axon;
public:
   static int NumberOfNeurons;
   Neuron(int x = -1, int y = -1);
   int getNeuronId();
   void growAxon();
   void growDendr();
   void CheckForNewNeuroConnection(struct DendrArea dendrArea);
};

class Connection {
protected:
   int SourceID;
   int DestinationID;
public:
   int getSourceID();
   int getDestinationID();
};

class NeuroConnection : public Connection {
private:
   int delay;
   double probability;
public:
   int getDelay();
   double getProbability();
};

class UI {
private:
   virtual void printNeuron()=0;
   virtual void clearScreen()=0;
public:   
   virtual void printNeuronalNetwork(Neuron *neurons)=0;
};

class CLUI : public UI {
private:
   void printNeuron();
   void clearScreen();
public:
   void printNeuronalNetwork(Neuron *neurons);
};
