#ifndef ENTRANCECLASS_H
#define ENTRANCECLASS_H
#include<string>
#include<vector>
#include"../../toll-booth/toll-booth-interface.h"

class Entrance{

    public:
        Entrance(int,int,int);
        ~Entrance();

        std::vector<Vehicle*> operate(int);
        
        int getNode()const{ return node;}
        int waitingVehicles();
        static void setK(int Kval){ K = Kval; }  //initialiser

    private:


        void addToBooths();
        std::vector<Vehicle*> removeFromBooths(int);
        void increment();
        void decrement();

        const int node;
        std::vector<MannedBooth*> mannedBooths;
        std::vector<UnmannedBooth*> unmannedBooths;

        int totalCap; //added here to help with some checks
        static int K ;
};


#endif // ENTRANCECLASS_H