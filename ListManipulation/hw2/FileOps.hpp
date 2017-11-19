//
//  FileOps.hpp
//  hw2
//
//  Created by minnah on 3/11/16.
//  Copyright © 2016 minnah. All rights reserved.
//

#ifndef FileOps_hpp
#define FileOps_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "List.h"

using namespace std;

class FileOps{
public:
    FileOps();
    void parseFile(string argument);
    void buildList(string inFile);
    void doOps(string opFile);
    void getOp(string command);
    void print();
private:
    List lst;
    string line;
    string token;
    string command;
    string op;
    string iFile;
    string oFile;
    string lineNum;
    char com;
    size_t pos;
    size_t sPos;
    int lNum;
};

#endif /* FileOps_hpp */
