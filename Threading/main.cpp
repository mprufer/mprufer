//Minnah Prufer
//COSC 3360
//Spring 2017
//Assignment 3

//Please use command in UNIX: g++ -std=c++11 -pthread *.cpp

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include "cars.h"

using namespace std;

//Static variables maintained by all threads and functions
static int maxweight = 0;
static int currentweight = 0;
static pthread_cond_t ok = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mylock;
static pthread_t child [100];

cars acar;
//keeps track of all cars that want to cross the bridge
cars crossing[1000];

void *vehicle(void *arg);
void enterbridge(int weight);
void leavebridge(int weight);

int main(int argc, const char * argv[]) {
    pthread_mutex_init(&mylock, NULL);
    pthread_cond_init(&ok, NULL);
    string line = "";
    ifstream ofile;
    string arg1 = "";
    string arg2 = "";
    string arg3 = "";
    string arg4 = "";
    int count = 0;
    maxweight = stoi(argv[1]);
    
    //Block of code just so input redirection works in xcode
    //MUST be commented out to work in UNIX
    ifstream arq(getenv("MYARQ"));
    cin.rdbuf(arq.rdbuf());
    
    pthread_mutex_init(&mylock, NULL);
    
    //Block of code to get output in UNIX
    //Does not need to be commented out in xcode
    while (getline(cin, line)){
        stringstream ss(line);
        ss >> arg1 >> arg2 >> arg3 >> arg4;
        acar.license = arg1;
        acar.prevarrive = stoi(arg2);
        acar.totalweight = stoi(arg3);
        acar.crossecs = stoi(arg4);
        crossing[count] = acar;
        count++;
    }
   //Read each line in text and puts in array
    for(int j=0; j<count; j++){
        //sleep func here
        sleep(crossing[j].prevarrive);
        cout << "Vehicle " << crossing[j].license << " arrives at bridge."  << endl;
        cout << "Current bridge load: " << currentweight << endl;
        cout << endl;
        //create each child thread
        pthread_create(&child[j], NULL, vehicle, (void *)&crossing[j]);
    }
    //Have each thread join so program does not terminate until all threads complete
    for(int j=0; j<count; j++){
        pthread_join(child[j], NULL);
    }
    exit(0);
}

void *vehicle(void *arg){
    cars *current = (cars*) arg;
    
    //Check to see if vehicle weight is greater than bridge max weight
    //If it is, deny it from crossing and terminate its thread
    if(current->totalweight > maxweight){
        pthread_cond_signal(&ok);
        pthread_mutex_unlock(&mylock);
        pthread_exit(NULL);
    }
    //If vehicle weight is less than maxweight of bridge but its current weight won't allow it cross
    //Have the thread wait until it can cross
    pthread_mutex_lock(&mylock);
    while ((current->totalweight + currentweight) > maxweight){
        pthread_cond_wait(&ok, &mylock);
    }
    enterbridge(current->totalweight);
    
    pthread_mutex_unlock(&mylock);
    pthread_mutex_lock(&mylock);
    cout << "Vehicle " << current->license << " crosses the bridge." << endl;
    cout << "Current bridge load: " << currentweight << endl;
    cout << endl;
    pthread_mutex_unlock(&mylock);
    //Vehicle is crossing
    sleep(current->crossecs);
    
    pthread_mutex_lock(&mylock);
    leavebridge(current->totalweight);
    cout << "Vehicle " << current->license << " leaves the bridge" << endl;
    cout << "Current bridge load: " << currentweight << endl;
    cout << endl;
    
    //Vehicle has left allow threads currently waiting to check if they can cross
    pthread_cond_broadcast(&ok);
    pthread_mutex_unlock(&mylock);
    pthread_exit(NULL);
}

void enterbridge(int weight){
    currentweight = currentweight + weight;
}

void leavebridge(int weight){
    currentweight = currentweight - weight;
}
