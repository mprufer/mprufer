#ifndef FileOps_hpp
#define FileOps_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include "RoundRobin.hpp"
#include "Fifo.hpp"

using namespace std;

class FileOps{
public:
    FileOps();
    void parse(string argument);
    void readFile(string file);
private:
    RoundRobin robin;
    Fifo ff;
    int qsize;
    string file;
    int quantum;
    string schedule;
    size_t pos;
    size_t lpos;
    string line;
    int count;
    string name;
    int arrival;
    int duration;
    string token;
};

#endif
