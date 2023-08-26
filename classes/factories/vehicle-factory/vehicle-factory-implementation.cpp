#include<iostream>
#include<cstdlib>
#include"vehicle-factory-interface.h"
#include"../../controller/controller-interface.h"

using namespace std;

int VehicleFactory::tUsed = 0;

vector<Vehicle*> VehicleFactory::randVehicles(int amount, int entryNode){

    int exitableNodes = Controller::getNSegs();
    vector<Vehicle*> vehiclesToMake;
    int exitNode = 0;

    for(int i = 0; i < amount; i++){

        exitNode = VehicleFactory::rangedRand(entryNode,exitableNodes);
        Vehicle* vehicle = new Vehicle(-1, exitNode);
        vehiclesToMake.push_back(vehicle);
        
        VehicleFactory::tUsed++;
    }

    return vehiclesToMake;

}

//Provides a random integer between the first argument and the second argument.
//The number will never be equal to the highest argument
// i E [lowerBound,upperBound)
int VehicleFactory::rangedRand(int lowerBound, int upperBound){

    return  (upperBound - 1 - lowerBound ) != 0 ? 
            (rand() % (upperBound - 1 - lowerBound )) + lowerBound :
            lowerBound;

}