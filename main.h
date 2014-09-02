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
