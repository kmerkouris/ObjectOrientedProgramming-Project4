#include<iostream>
#include<string>
#include<cstdlib>
#include"classes/controller/controller-interface.h"
#include"classes/highway/highway-interface.h"

using namespace std;



int main(int argc, char *argv[]){

    int N = strtol(argv[1], nullptr, 10) ;
    int NSegs = strtol(argv[2], nullptr, 10) ;
    int K = strtol(argv[3], nullptr, 10) ;
    int Percent = strtol(argv[4], nullptr, 10) ;
    Controller::init(N,NSegs,K,Percent);
    cout<<"Project initialised with values:\n"
        <<"Number of trials: " << N << "\n"
        <<"Number of segments: " << NSegs << "\n"
        <<"Toll Booth entry cap: " << K << "\n"
        <<"Percentage of cars to prepare each trial: " << Percent << endl;

    Highway* highway = new Highway();

    for(int i = 0 ; i < N ; i++){
        highway->operate();
    }
    cout <<"Highway operation over." << endl;

    delete highway;

}