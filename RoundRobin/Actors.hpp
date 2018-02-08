#ifndef Actors_hpp
#define Actors_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Actors{
public:
    Actors();
    ~Actors();
    void setName(string actor);
    void setRounds(int time);
    void setDuration(int min);
    void setArrival(int _time);
    string getName();
    int getRounds();
    int getDuration();
    int getArrival();
    void setActor(string actor, int rounds, int min, int time);
private:
    string name;
    int rounds;
    int duration;
    int time = 0;
};

#endif /* Actors_hpp */
