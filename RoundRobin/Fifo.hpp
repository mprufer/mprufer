#ifndef Fifo_hpp
#define Fifo_hpp

#include <stdio.h>
#include "Actors.hpp"

class Fifo{
public:
    Fifo();
    ~Fifo();
    void applyMakeup(string name, int arrival, int duration);
    void fillQueue(string name, int arrival, int duration);
    void sort();
    void print();
private:
    int timer;
    int wtime;
    int counter;
    Actors aQueue[1000];
    Actors act;
};

#endif /* Fifo_hpp */
