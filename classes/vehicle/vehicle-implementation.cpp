#include<iostream>
#include"vehicle-interface.h"

using namespace std;


Vehicle::Vehicle(int seg, int ex) : segment(seg), exitNode(ex){
    this->ready = false;
}

Vehicle::~Vehicle(){
    cout<< "Destroying a Vehicle..."<< endl;
}

vehicleResponse Vehicle::progress(){
    if(!this->ready){
        return FAILIURE;
    }

    this->changeSegment();
    if(this->segment == this->exitNode){ //if this is true, the segment
        return EXIT;                     //the car would normally enter
    }                                    //is actually further than the
                                         //exit point    
    return SUCCESS;
}

void Vehicle::changeSegment(){
    this->segment++;
    this->ready = false;
}
