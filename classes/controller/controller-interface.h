#ifndef CONTROLLERCLASS_H
#define CONTROLLERCLASS_H


class Controller{

    public:
        static void init(int,int,int,int);
        static int getNSegs()
            {return NSegs;}
    private:
        static int NSegs;
        static int N;
        static int K;
        static int Percent;
};


#endif // CONTROLLERCLASS_H