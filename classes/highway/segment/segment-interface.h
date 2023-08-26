#ifndef SEGMENTCLASS_H
#define SEGMENTCLASS_H
#include<vector>
#include"entrance/entrance-interface.h"
#include"../../vehicle/vehicle-interface.h"

class Segment{

    public:
        Segment(Entrance*,int,Segment*,int);
        ~Segment();
                
        int getNoOfVehicles()
            {return cars.size();}

        void operate();

        void setPrev(Segment*);

        static void setPercent(int); //initialiser

    private:

        void enter(std::vector<Vehicle*>);
        void exit();
        void pass();

        void delayCheck();

        int getReadyVehicles();

        Entrance* entrance;
        std::vector<Vehicle*> cars;
        const int carCap;
        Segment* nextSegment;
        Segment* prevSegment;
        
        static int Percent;

        int lastEntered;
        int lastPassed;
        int segNum;

};


#endif // SEGMENTCLASS_H