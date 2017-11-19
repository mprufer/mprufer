#include "Queue.hpp"
#include <string>
#include <iostream>

using namespace std;

Queue::Queue(){
    front = -1;
    end = -1;
    max = 0;
}

Queue::~Queue(){
    
}

//PreCondition: size has been passed from the appropriate schedule class (ie which schedule type was parsed from the argument)
//PostCondition: a dynamic array of class Actor is created with the size passed
void Queue::makeQueue(int size){
    max = size;
    acQueue = new Actors[max];
    
}

bool Queue::isEmpty(){
    if (front == -1 && end == -1)
        return true;
    else
        return false;
}

bool Queue::isFull(){
    if (isEmpty()){
        return false;
    }
    //+1 to end because if queue is full, end is the one before front.
    else if((end+1)%max == front){
        return true;
    }
    else{
        return false;
    }
}
void Queue::print(){
    cout << front << " " << end << endl;
}
bool Queue::hasOneElem(){
    return (front == end);
}

void Queue::enqueue(string name, int rounds, int duration, int arrival){
    if(isEmpty()){
        front += 1;
        end +=1;
        act.setActor(name, rounds, duration, arrival);
        acQueue[end] = act;
    }
    else{
        end = (end+1)%max;
        act.setActor(name, rounds, duration, arrival);
        acQueue[end] = act;
    }
}

void Queue::dequeue(){
    if(isEmpty()){
        front = -1;
        end = -1;
    }
    //queue only has one element - makes queue empty again
    else if (front == end){
        front =  -1;
        end = -1;
    }
    else{
        front = (front+1)%max;
    }
}
//Rounds is not actually being updated!
void Queue::updateRounds(string name, int rounds, int duration, int arrival){
    act.setActor(name, rounds, duration, arrival);
    acQueue[front] = act;
}
/*Note: 3 separate get functions were created for each part of the object to avoid creating multiple objects of the Actors class*/

//Gets the name of the actor (indicated by the index number) by calling the getName function in the Actor class
string Queue::getName(){
    return acQueue[front].getName();
}

//Gets the arrival time of the actor (indicated by the index number) by calling the getArrival function in the Actor class
int Queue::getRounds(){
    return acQueue[front].getRounds();
}

//Gets the duration time of the actor (indicated by the index number) by calling the getDuration function in the Actor class
int Queue::getDuration(){
    return acQueue[front].getDuration();
}

Actors Queue::getActor(){
    return acQueue[front];
}

int Queue::getArrival(){
    return acQueue[front].getArrival();
}

int Queue::getNextArrival(){
    return acQueue[front+1].getArrival();
}