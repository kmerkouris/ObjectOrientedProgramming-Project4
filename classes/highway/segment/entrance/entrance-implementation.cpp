#include<iostream>
#include"entrance-interface.h"
#include"../../../factories/vehicle-factory/vehicle-factory-interface.h"

using namespace std;

int Entrance::K = 0;

Entrance::Entrance(int n, int manned, int unmanned): node(n){

    cout << "Creating Gate..." << endl;

    for(int i = 0 ; i < manned ; i++){
        int carsToEnter = rand() % 5 + 1 ; 
        vector<Vehicle*> vehicles = VehicleFactory::randVehicles(carsToEnter,this->node);
        this->mannedBooths.push_back(new MannedBooth(vehicles));
    }

    for(int i = 0 ; i < unmanned ; i++){
        int carsToEnter = rand() % 5 + 1 ;  
        vector<Vehicle*> vehicles = VehicleFactory::randVehicles(carsToEnter,this->node);
        this->unmannedBooths.push_back(new UnmannedBooth(vehicles));
    }

    this->totalCap = 3*Entrance::K;

    cout << "Gate Created!" << endl;
}

Entrance::~Entrance(){
    cout << "Destroying an entrance..." << endl;
    for(MannedBooth* booth : this->mannedBooths){
        delete booth;
    }
    for(UnmannedBooth* booth : this->unmannedBooths){
        delete booth;
    }
}


vector<Vehicle*> Entrance::operate(int segCapacity){
    
    cout << "Operating entrance..." << endl;
    cout << "Removing " << segCapacity << " cars from toll booths..." << endl;
    vector<Vehicle*> removedCars = this->removeFromBooths(segCapacity);

    cout << "Vehicles removed from toll booths." << endl;

    if( segCapacity >= this->totalCap){
        this->increment();
    }else{
        this->decrement();
    }
    
    this->addToBooths();

    return removedCars;
   
}

void Entrance::increment(){
    totalCap = totalCap + 3;
}

void Entrance::decrement(){
    this->totalCap = this->totalCap - 3 ;  
}

//Lets min(segmentCap,totalCap) cars through the entrance into the next segment
vector<Vehicle*> Entrance::removeFromBooths(int segmentCap){
    vector<Vehicle*> vehiclesToRemove;

    if(this->totalCap < segmentCap){
        segmentCap = this->totalCap;
    }
    
    //1 thirdof the total load is handled by the manned Toll Booths
    int handledByManned = min<int>(segmentCap / 3, Entrance::K) ;
    cout << handledByManned << " cars will be handled by manned booths" << endl;
    //2 thirds(2K) are handled by the unmanned Toll Booths
    int handledByUnmanned = min<int>(segmentCap - handledByManned, 2*Entrance::K); //=2segmentcap/3, most of the load goes to unmanned booths
    cout << handledByUnmanned << " cars will be handled by unmanned booths" << endl;

    //The load a single booth handles is, at maximum, singleLoad + 1
    int singleLoad = handledByManned / this->mannedBooths.size();
    cout << "Each manned booth will handle at least " << singleLoad << " vehicles." << endl;
    int leftovers = handledByManned % this->mannedBooths.size();
    cout << leftovers << " leftover cars, will each be handled by a different booth." << endl;

    //For every booth, if we have leftovers, we make is handle its load + 1 more car.
    //If we dont, it just handles its own load
    cout << "Removing cars from manned booths..." << endl;
    for(MannedBooth* booth : this->mannedBooths){
        vector<Vehicle*> vs;
        if( 0 != leftovers){
            cout << "Removing " << singleLoad << " cars + 1 leftover car..." << endl;
            vs = booth->removeFromQueue(singleLoad + 1);
            leftovers--;
            cout << "Cars removed!" << endl;
        }else if (singleLoad != 0){
            cout << "Removing " << singleLoad << " cars..." << endl;
            vs = booth->removeFromQueue(singleLoad);
            cout << "Cars removed!" << endl;
        }
        for(Vehicle* vehicle : vs){
            cout << "Pushing removed vehicles through..." << endl;
            vehiclesToRemove.push_back(vehicle);
            cout << "Vehicles from this booth passed!" << endl;
        }
    } 

    singleLoad = handledByUnmanned / this->unmannedBooths.size();
    cout << "Each unmanned booth will handle at least " << singleLoad << " vehicles." << endl;
    leftovers = handledByUnmanned % this->unmannedBooths.size();
    cout << leftovers << " leftover cars, will each be handled by a different booth." << endl;
    
    cout << "Removing cars from unmanned booths..." << endl;
    for(UnmannedBooth* booth : this->unmannedBooths){
        vector<Vehicle*> vs;
        if( 0 != leftovers){
            cout << "Removing " << singleLoad << " cars + 1 leftover car..." << endl;
            vs = booth->removeFromQueue(singleLoad + 1);
            leftovers--;
            cout << "Cars removed!\n";
        }else if (singleLoad != 0){
            cout << "Removing " << singleLoad << " cars..." << endl;
            vs = booth->removeFromQueue(singleLoad);
            cout << "Cars removed!\n";
        }else{
            cout << "No cars to push from this toll booth\n" ;
        }
        cout << "Pushing " << vs.size() << " removed vehicles through..." << endl;
        for(Vehicle* vehicle : vs){
            vehiclesToRemove.push_back(vehicle);
        }
        cout << "Vehicles from this booth passed!" << endl;
    }
    cout << "Passing vehicles to the segment..." << endl;
    return vehiclesToRemove;
}

//Adds vehicles to the entrance's TollBooths
void Entrance::addToBooths(){

    for(MannedBooth* booth : this->mannedBooths){
        int amount = rand() % 3 ;
        vector<Vehicle*> vehiclesToAdd = VehicleFactory::randVehicles(amount,this->node);
        for(Vehicle* vehicle : vehiclesToAdd){
            booth->addToQueue(vehicle);
        }
    }
    for(UnmannedBooth* booth : this->unmannedBooths){
        int amount = rand() % 3 ;
        vector<Vehicle*> vehiclesToAdd = VehicleFactory::randVehicles(amount,this->node);
        for(Vehicle* vehicle : vehiclesToAdd){
            booth->addToQueue(vehicle);
        }
    }

}

int Entrance::waitingVehicles(){
    int size = 0;
    for(MannedBooth* booth : this->mannedBooths){
        size+= booth->queueSize();
    }
    for(UnmannedBooth* booth : this->unmannedBooths){
        size+= booth->queueSize();
    }
    return size;
}