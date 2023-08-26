#include<vector>
#include<iostream>
#include"highway-interface.h"

using namespace std;

int Highway::NSegs = 0;

Highway::Highway(){

    int mannedNum, unmannedNum, carCap;
    vector<Segment*> segmentsToAdd;

    Segment* prevSeg = nullptr;
    this->vehNumber = 0;

    for(int i = 0; i < NSegs; i++){
        cout << "Enter capacity for segment" << i << "\n";
        cin >> carCap;

        mannedNum = rand() % 8 + 1;     //admission: each gate has at most 8 and
        unmannedNum = rand() % 8 + 1;   //at least 1 toll booth of each kind

        segmentsToAdd.push_back( new Segment(
            new Entrance(i,mannedNum,unmannedNum),
            carCap,
            prevSeg,
            i
        ));
        cout << "Created segment " << i << endl;
        prevSeg = segmentsToAdd[i];

        this->segments.push_back(segmentsToAdd[i]);
        this->vehNumber += segmentsToAdd[i]->getNoOfVehicles(); 
    }
    cout << "Highway in operation." << endl;
}

Highway::~Highway(){
    for(Segment* segment : this->segments){
        delete segment;
    }
}

void Highway::operate(){
    int i = 0;
    this->vehNumber = 0;
    cout << "Cycle begins!" << endl;
    cout << "Operating on " << this->segments.size() << " segments." << endl;
    for(int i = this->segments.size() - 1 ; i >=0; i-- ){
        cout << "Operating segment " << i << "\n";
        this->segments[i]->operate();        
        cout << "Segment " << i << " operation over.\n";
        this->vehNumber += this->segments[i]->getNoOfVehicles();
    }

    cout << "Cycle is ending.\nVehicles currently in the highway: " << this->vehNumber << endl;
    // for(Segment* segment : this->segments){
    //     cout << "Operating segment " << i << "\n";
    //     segment->operate();         
    //     cout << "Segment " << i << " operation over.\n";
    //     i++;
    // }
}