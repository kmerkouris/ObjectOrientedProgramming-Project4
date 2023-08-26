#include<iostream>
#include"toll-booth-interface.h"
#include"../../vehicle/vehicle-interface.h"

using namespace std;

TollBooth::TollBooth(const vector<Vehicle*>& vehicles) {

    for( Vehicle* vehicle : vehicles ){
        this->addToQueue(vehicle);
    }   
}

TollBooth::~TollBooth(){
    for(Vehicle* vehicle : this->waitingVehicles){
        delete vehicle;
    }
}

void TollBooth::addToQueue(Vehicle* vehicle){

    this->waitingVehicles.push_back(vehicle);

}

vector<Vehicle*> TollBooth::removeFromQueue(int amountNeeded){
    //this bit of logic will be left up to the Entrance Class
    // if(amountNeeded >= this->entryCap){
    //     amountNeeded = this->entryCap; 
    // }
    if(amountNeeded > this->waitingVehicles.size()){
        cout<< "Not enough cars waiting in toll booth, passing "
            << this->waitingVehicles.size() << " instead of "
            << amountNeeded << endl;
        amountNeeded = this->waitingVehicles.size();
    }
    cout << "Entered TollBooth::removeFromQueue()" << endl;
    cout << "Attempting to remove " << amountNeeded << " vehicles from this booth" << endl;
    vector<Vehicle*> vehiclesToRemove;

    for(int i = 0 ; i < amountNeeded ; i++ ){       //FIFO implementation
        cout << "Chose vehicle " << i << ".\n" ; 
        Vehicle* v = this->waitingVehicles[0];
        vehiclesToRemove.push_back(v);
        cout << "Erasing vehicle from the toll booth...\n";
        this->waitingVehicles.erase( this->waitingVehicles.begin()); //check later
        cout << "Vehicle erased!\n" ; 
    }

    cout << "Exiting TollBooth:removeFromQueue()" << endl;
    return vehiclesToRemove;
}

int TollBooth::queueSize(){
    return this->waitingVehicles.size();
}


MannedBooth::MannedBooth(const std::vector<Vehicle*>& vehicles ) : TollBooth(vehicles){}

UnmannedBooth::UnmannedBooth(const std::vector<Vehicle*>& vehicles ) : TollBooth(vehicles){
}

