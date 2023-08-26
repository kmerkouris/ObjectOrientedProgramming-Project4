#include<iostream>
#include<cstdlib>
#include<time.h>
#include"controller-interface.h"
#include"../highway/segment/segment-interface.h"
#include"../highway/toll-booth/toll-booth-interface.h"
#include"../highway/highway-interface.h"

using namespace std;

int Controller::Percent = 0;
int Controller::K = 0;
int Controller::NSegs = 0;
int Controller::N = 0;

void Controller::init(int NV, int NSegsV , int KV, int PercentV){
    
    srand(time(NULL));

    Segment::setPercent(PercentV);
    Entrance::setK(KV);
    Highway::setNsegs(NSegsV);

    Controller::Percent = PercentV;
    Controller::K = KV;
    Controller::NSegs = NSegsV;
    Controller::N = NV;

}