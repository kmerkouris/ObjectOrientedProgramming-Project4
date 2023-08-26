#ifndef TOLLBOOTHCLASS_H
#define TOLLBOOTHCLASS_H
#include<vector>
#include<iostream>
#include"../../vehicle/vehicle-interface.h"

//class fragile, loosley defined connections with entrance, fix implementation later

// enum tollBoothResponse{
//     INCREASE,
//     DECREASE
// };

class TollBooth{

    public:
        TollBooth(const std::vector<Vehicle*>& );
        virtual ~TollBooth();

        void addToQueue(Vehicle*);
        std::vector<Vehicle*> removeFromQueue(int); //Argument: Amount of cars to be removed(pass through)

        int queueSize();


    protected:
        std::vector<Vehicle*> waitingVehicles;

};

class MannedBooth : public TollBooth{

    public:
        MannedBooth(const std::vector<Vehicle*>& );
        ~MannedBooth()
            {std::cout << "Destroying manned booth..." << std::endl;};

};

class UnmannedBooth : public TollBooth{

    public:
        UnmannedBooth(const std::vector<Vehicle*>& );
        ~UnmannedBooth()
            {std::cout << "Destroying unmanned booth..." << std::endl;}

};

#endif // TOLLBOOTHCLASS_H