#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include"segment-interface.h"
#include"../../factories/vehicle-factory/vehicle-factory-interface.h"

using namespace std;

int Segment::Percent = 0;

void Segment::setPercent(int PValue){
    Segment::Percent = PValue;
}

Segment::Segment(Entrance* entr,int cap,Segment* prev, int n) :
    carCap(cap), entrance(entr), nextSegment(nullptr){
    
    cout << "Creating Segment " << n <<"..."<< endl;
    
    int carsInside = rand() % (cap * 2/3) + 1;
    
    vector<Vehicle*> carsToAdd = VehicleFactory::randVehicles(carsInside,this->entrance->getNode());
    for(Vehicle* car : carsToAdd){
        this->cars.push_back(car);
        cout << "Pushed back a car." <<endl;
    }
    this->lastEntered = 0;
    this->lastPassed = 0;
    this->segNum = n;
    this->setPrev(prev);

    cout << "Created Segment " << n << "!"<< endl;

}

Segment::~Segment(){
    cout << "Destroying a segment..." << endl;
    
    if(nullptr != this->prevSegment){
        this->prevSegment->nextSegment = nullptr;
    }
    if(nullptr != this->nextSegment){
        this->nextSegment->prevSegment = nullptr;
    }
    
    for(Vehicle* car : this->cars){
        delete car;
    }
    
}

void Segment::enter(vector<Vehicle*> vehiclesToAdd){

    int i = 0;
    while(
        (this->cars.size() < this->carCap) &&
        (vehiclesToAdd.size() != 0 ) ){ 
        cout << this->carCap - this->cars.size() << " cars may still be added.\n";
        cout << vehiclesToAdd.size() << " cars left to be added.\n"; 
        this->cars.push_back(vehiclesToAdd[0]);
        vehiclesToAdd[0]->enter(this->segNum);
        vehiclesToAdd.erase(vehiclesToAdd.begin());
        
    }

}

void Segment::exit(){
    cout << "Entered Segment::exit()" << endl;
    int i = 0; 
    while(i < this->cars.size()){
        cout << "Checking car " << i << "...\n";
        if(
            (this->cars[i]->isReady()) && 
            (this->cars[i]->getExit() == this->entrance->getNode())
        ){
            Vehicle* carToRemove = this->cars[i];
            this->cars.erase(this->cars.begin() + i);
            cout << "Car " << i << " removed from highway.\n";
            i--;                                    //ensures no vehicles skip the check and that the 
            delete carToRemove;                     //right ones are removed   
             
        }else if((this->cars[i]->getExit() == this->entrance->getNode())){
            cout << "Car " << i << " wants to exit but is not ready yet.\n";
        }else{
            cout << "Car " << i << " will exit at node " << this->cars[i]->getExit() <<".\n";
            cout << "Node number: " << this->entrance->getNode() << ".\n";
        }
        i++;
    }
    cout << "Exiting Segment::exit()" << endl;
}

void Segment::pass(){

    cout << "Entered Segment::pass()" << endl;

    if(nullptr == this->nextSegment){
        cout << "Called on first segment, exiting Segment::pass()" <<endl;
        return;
    }

    vector<Vehicle*> carsToPass;
    vector<Vehicle*> carsToAddBack;

    int i = 0;
    //find the cars that should be passed to the next stage
    while(i < this->cars.size()){
        if(
            (this->cars[i]->isReady()) && 
            (this->cars[i]->getExit() != this->entrance->getNode())
        ){
            cout << "Found ready car " << i << ".\n";
            carsToPass.push_back(this->cars[i]);
            this->cars.erase(this->cars.begin() + i);
            i--;
        }                                           
        i++;
    }

    //choose random cars to stay if the next segment ends up to be over capacity
    while(carsToPass.size() > this->nextSegment->carCap){
        cout << "Too many reasy cars, choosing one to wait.\n";
        i = rand() % carsToPass.size();
        carsToAddBack.push_back(carsToPass[i]);
        carsToPass.erase(carsToPass.begin() + i );
    }

    //add chosen cars back
    for( Vehicle* car : carsToAddBack){
        this->cars.push_back(car);
    }

    //add them to the next segment
    this->nextSegment->enter(carsToPass);
    this->lastPassed = carsToPass.size();


}

int Segment::getReadyVehicles(){
    int numOfReady = 0;
    for(Vehicle* car : this->cars){
        if(car->isReady()) numOfReady++;
    }
    return numOfReady;
}

void Segment::delayCheck(){
    string message = "";
    string node = to_string(this->entrance->getNode());
    int watingVs = this->entrance->waitingVehicles();
    int readyVs = this->getReadyVehicles() ;
    if(this->lastEntered < watingVs){
        message.append("\tDelays at node " + node  + "\n" );
    }
    if(this->getReadyVehicles() > this->lastPassed){
        message.append("\tDelays after node " + node  + "\n");
    }
    if("" == message){
        message.append("\tKeep your safety distance after node " + node + "\n");
    }
    cout << "\n" << endl;
    cout << "////////////////////////////////////////////////////////////////////" << endl;
    cout << message << endl;
    cout << "////////////////////////////////////////////////////////////////////" << endl;
    cout << "\n" << endl;
}

void Segment::operate(){

    //let the vehicles that want to leave the highway leave
    cout << "Exiting vehicles..." << endl;
    this->exit();
    cout << "Vehicles have exited the highway!" << endl;
    

    //take the vehicles from the previous segment
    if(!(nullptr == this->prevSegment)){
        cout << "Passing vehicles from the previous segment..." << endl;
        this->prevSegment->pass();
        cout << "Vehicles have passed!" << endl;
    }


    //if there's still room, let more vehicles enter through the entrance
    int spaceLeft = 0;
    if(this->getNoOfVehicles() < this->carCap){
        cout << "There is still space in this segment, fetching cars from the entrance..." << endl;
        spaceLeft = this->carCap - this->getNoOfVehicles();
        cout << "Space left: " << spaceLeft << endl;
        vector<Vehicle*> vsToAdd = this->entrance->operate(spaceLeft);
        cout << "Adding vehicles..." << endl;
        this->enter(vsToAdd);
        cout << "Allowed " << min<int>(spaceLeft, vsToAdd.size()) << " more cars to enter!" << endl;
    }else{
        cout << "No more room left in this segment." << endl;
    }
    this->lastEntered = spaceLeft;


    //prepare cars for the next cycle
    cout << "Preparing cars for the next cycle..." << endl;

    int carsToReadify = this->cars.size() * this->Percent/100 ;
    int randPicker = rand() % this->cars.size();
    int i = 0, readyCounter = this->getReadyVehicles() ;
    while(i < carsToReadify && readyCounter < this->getNoOfVehicles()){
        if(!this->cars[randPicker]->isReady()){
            this->cars[randPicker]->prepare();
            i++;
            readyCounter++;
        }
        randPicker = rand() % this->cars.size();                                                 
    }
    cout << "Prepared " << carsToReadify << " cars to pass for the next cycle." << endl;

    this->delayCheck();
}


void Segment::setPrev(Segment* seg){
    cout << "Setting next segment..." << endl;
    this->prevSegment = seg;
    if( seg != nullptr){
        seg->nextSegment = this;
    }
    cout<< "Next segment set!" << endl;
    
}