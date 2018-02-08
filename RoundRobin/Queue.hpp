#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include "Actors.hpp"

class Queue{
public:
    Queue();
    ~Queue();
    void makeQueue(int size);
    string getName();
    int getRounds();
    int getDuration();
    int getArrival();
    Actors getActor();
    bool isEmpty();
    bool isFull();
    void dequeue();
    void enqueue(string name, int rounds, int duration, int arrival);
    void updateRounds(string name, int rounds, int duration, int arrival);
    bool hasOneElem();
    int getNextArrival();
    void print();
private:
    Actors *acQueue;
    Actors act;
    int front;
    int end;
    int max;
    int count;
};

#endif /* Queue_hpp */
