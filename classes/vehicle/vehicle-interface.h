#ifndef VEHICLECLASS_H
#define VEHICLECLASS_H

enum vehicleResponse{
    SUCCESS, //Vehicle progressed to the next segment
    FAILIURE,//Vehicle wasn't ready to progress yet
    EXIT,    //Vehicle wants to exit the highway
};

class Vehicle{

    public:
        
        Vehicle(int,int);
        ~Vehicle(); 

        bool isReady()
            {return this->ready;}
        int getExit()
            {return this->exitNode;}

        void prepare()
            {this->ready = true;}
        void enter(int seg)
            {this->segment = seg;}

        vehicleResponse progress();

    private:

        void changeSegment();

        const int exitNode;
        int segment; //-1 if they havent entered the highways yet
        bool ready;
};


#endif // VEHICLECLASS_H