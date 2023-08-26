#ifndef VEHICLEFACTORYCLASS_H
#define VEHICLEFACTORYCLASS_H
#include<vector>
#include"../../vehicle/vehicle-interface.h"


class VehicleFactory{

    public:
        
        static std::vector<Vehicle*> randVehicles(int,int);
        static int timesUsed();

    private:
        static int tUsed;
        static int rangedRand(int,int);
        
};


#endif // VEHICLEFACTORYCLASS_H