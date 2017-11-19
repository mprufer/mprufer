#ifndef RoundRobin_hpp
#define RoundRobin_hpp

#include <stdio.h>
#include "Queue.hpp"
#include "Actors.hpp"

class RoundRobin{
public:
    RoundRobin();
    void createQueue(int size);
    void fillQueue(string name, int arrival, int duration);
    void print();
    void applyMakeup();
    void setQuantum(int qTime);
    void setQMax(int size);
private:
    Actors current;
    Queue qu;
    int quantum;
    int timer;
    int wTime;
    int qMax;
};

#endif /* RoundRobin_hpp */
