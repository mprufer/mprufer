#include "Fifo.hpp"
#include <iostream>

using namespace std;

static int clk = 0;

Fifo::Fifo(){
    timer = 0;
    wtime = 0;
    counter = 0;
}

Fifo::~Fifo(){
    
}

/*IMPORTANT NOTE: clk is always ONE MORE than ACTUAL clk since it increments after every operation. When it is complete, it increments and advances to the NEXT min.*/
void Fifo::fillQueue(string name, int arrival, int duration){
    act.setActor(name, 0, duration, arrival);
    aQueue[counter] = act;
    counter++;
}
//Sort the queue so that actors are sorted by their arrival time so that no actor in the queue is before an actor with an earlier arrival time.
//Pases the sorted actors to queue to fill it
//Sorted by bubble sort
void Fifo::sort(){
    for(int i=1; i<counter; i++){
        for(int j=0; j<counter-1; j++){
            if(aQueue[i].getArrival() == aQueue[j].getArrival()){
                if(aQueue[i].getDuration() < aQueue[j].getDuration()){
                    act = aQueue[i];
                    aQueue[i] = aQueue[j];
                    aQueue[j] = act;
                }
                else{
                    //in correct order
                }
            }
            else{
                //Different arrivals so no need to compare & sort
            }
        }//end int j for loop
    }// end int i for loop
    for(int i=0; i<counter; i++){
        applyMakeup(aQueue[i].getName(), aQueue[i].getArrival(), aQueue[i].getDuration());
    }
}

void Fifo::applyMakeup(string name, int arrival, int duration){
    //If the timer is 4, means 4 make-ups have been completed and the artist should take a 2-min break.
    if(timer == 4){
        for(int i=0; i<2; i++){
            cout << clk << '\t' << "relax" << endl;
            clk++;
        }
        //After the break has been taken, timer resets to 0 again.
        timer = 0;
    }
    //If the arrival is greater than the clock, waiting is output first before make-up is applied
    if (arrival > clk){
        wtime = clk;
        //Needed separate int to hold value of clock at time of last completion since doing (arrival-clk) while clk is incrementing means at some point, i == (arrival-clk) before the full waiting time is complete
        //ex) Actual waiting time is 5-min before next arrival but at some point, i==3 & (arrival-clk)==3 before i reaches 5 so the full wait time is not outputted before moving on to apply make-up.
        for(int i = 0; i<(arrival-wtime); i++){
            cout << clk << '\t' << "waiting" << endl;
            clk++;
        }
    }
    //Either way, make-up is applied just have to check and see if should wait or relax before applying.
    for(int i = 0; i<duration; i++){
        //It's (duration-1) since i starts at 0
        if(i  == (duration-1)){
            cout << clk << '\t' << name << '\t' << duration << '\t' << "completed" << endl;
            clk++;
            timer++;
        }
        else{
            cout << clk << '\t' << name << '\t' << duration << '\t' << "makeup" << endl;
            clk++;
        }
    }//end for loop
}
