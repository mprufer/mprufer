#include "Actors.hpp"
#include <iostream>

using namespace std;
//The following uses Object Orientation. Each actor is an object with the variables: name, rounds, and arrival time.
Actors::Actors(){
    name = "";
    rounds = 0;
    duration = 0;
    time = 0;
}

Actors::~Actors(){
    
}

void Actors::setActor(string actor, int rounds, int min, int time){
    setName(actor);
    setRounds(rounds);
    setDuration(min);
    setArrival(time);
}

void Actors::setName(string actor){
    name = actor;
}

void Actors::setRounds(int _rounds){
    rounds = _rounds;
}

void Actors::setDuration(int min){
    duration = min;
}

void Actors::setArrival(int _time){
    time = _time;
}

string Actors::getName(){
    return name;
}

int Actors::getRounds(){
    return rounds;
}

int Actors::getDuration(){
    return duration;
}

int Actors::getArrival(){
    return time;
}
