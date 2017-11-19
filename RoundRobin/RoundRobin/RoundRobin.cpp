#include "RoundRobin.hpp"
#include <string>
#include <iostream>

using namespace std;

static int clk = 0;

RoundRobin::RoundRobin(){
    quantum = 0;
    timer = 0;
    wTime = 0;
    qMax = 0;
}

//Creates the queue once the number has been parsed from the argument in FileOps and passes it to the Queue class to create the queue (note: it was not passed to queue directly from FileOps because this class needs to create a queue obj regardless so to avoid multiples objs being created it's passed here first)
void RoundRobin::createQueue(int size){
    qu.makeQueue(size);
}

//Applies the make-up to each actor that has arrived. If the actor is not finished by the time the quantum expires, then they are passed to fillQueue to be enequeued.
    //Note: Each actor that is NOT finished in 1 round will be enqeued so they can be compared and the right order of operations will be done. 
void RoundRobin::applyMakeup(){
    if(timer==4){
        for(int i=0; i<2; i++){
            cout << clk << '\t' << "relax" << endl;
            clk++;
        }
        timer = 0;
    }
    else if(qu.isEmpty()){
        cout << clk << '\t' << "waiting" << endl;
        clk++;
    }
    else{
        if(qu.getRounds() == qu.getDuration()-1){
            cout << clk << '\t' << qu.getName() << '\t' << qu.getDuration() << '\t' << "completed" << endl;
            qu.dequeue();
            clk++;
            timer++;
        }
        else{
            cout << clk << '\t' << qu.getName() << '\t' << qu.getDuration() << '\t' << "makeup" << endl;
            clk++;
            qu.updateRounds(qu.getName(), qu.getRounds()+1, qu.getDuration(), qu.getArrival());
            if(qu.getRounds()%quantum==0 && qMax > 1){
                current = qu.getActor();
                qu.dequeue();
                qu.enqueue(current.getName(), current.getRounds(), current.getDuration(), current.getArrival());
            }//if qu.getRounds(0) % quantum == 0
        }
    }
}

//Fills the queue after being passed from readFile in the FileOps class.
//IMPORTANT: This will change drastically. Really need to think it out first before writing it.
void RoundRobin::fillQueue(string name, int arrival, int duration){
    if(arrival <= clk){
        if(qu.isFull()){
            do{
                applyMakeup();
            }while(qu.isFull());
            qu.enqueue(name, 0, duration, arrival);
        }
        else{
            qu.enqueue(name, 0, duration, arrival);
        }
    }//end if arrival <= clk
    else{
        do{
            applyMakeup();
        }while(clk < arrival);
        if(qu.isFull()){
            do{
                applyMakeup();
            }while(qu.isFull());
            qu.enqueue(name, 0, duration, arrival);
        }
        else{
            qu.enqueue(name, 0, duration, arrival);
        }
    }
}

//Check if queue empty or not after reading in file.
//If queue isn't empty. prints what's leftover in the queue.
void RoundRobin::print(){
    if(!qu.isEmpty()){
        while(!qu.isEmpty()){
            applyMakeup();
        }
    }
}
void RoundRobin::setQuantum(int qTime){
    quantum = qTime;
}

void RoundRobin::setQMax(int size){
    qMax = size;
}