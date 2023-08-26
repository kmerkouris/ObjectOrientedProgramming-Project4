#ifndef HIGHWAYCLASS_H
#define HIGHWAYCLASS_H
#include"segment/segment-interface.h"
#include<vector>

class Highway{

    public:
        Highway();
        ~Highway();

        void operate();
        void print();

        static void setNsegs(int K)
            {NSegs = K;} //initialiser

    private:
        std::vector<Segment*> segments; //NSegs of these
        int vehNumber;
        int segmentNum;
        static int NSegs;
};


#endif // HIGHWAYCLASS_H