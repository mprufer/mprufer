//
//  List.h
//  hw2
//
//  Created by minnah on 3/2/16.
//  Copyright © 2016 minnah. All rights reserved.
//

#ifndef List_h
#define List_h

#include <string>
#include <iostream>
#include <sstream>
#include <tgmath.h>

using namespace std;

class List{
public:
    List ();
    ~List();
    void newLine(bool eof); //creates new line in list of lines
    void createCells(string info); //creates new "cell" in desired line's list
    void createLines(bool instCmmd); //
    void print(); //sets the pointers then calls printList
    void printList(List *lineTmp, List *cTmp); //prints the contents of every list
    void insertLine(int line); //receives line to insert new empty line, sets pntrs, then calls newLine
    void deleteLine(int line); //receives line tbd, sets pointers, then calls deallocate to delete line
    void deallocate(List *tmp); //deletes the desired line
    void count(int line); //receives line whose numbers are to be counted, sets pntrs, then calls isDouble to count number of numbers in desired line
    int isDouble(string info, int count); //counts amount of numbers in desired line
    void max(int line); //receives line to find max of, sets pntrs, then calls findMax
    void findMax(List *tmp, double max); //finds the max number of a line
    void min(int line); // receives line to find min of, sets pntrs, then calls find min
    void findMin(List *tmp, double min, int count); //finds min of desired line
    void setLstTrvr(List *trvr, int lNum, int count); //sets the pntr to the desired line to do ops on
    void mean(int line); //receives line to calculate mean of and sets ptrs to desired line
    double findMean(List *trvr, double mean, int amnt); //calculates and returns mean of list received
    void normalize(int line);
    void normalizeByZero(List *lTmp, List *cTmp, double avg);
    void doNormalize(List *lTmp, List *cTmp, double avg);
private:
    //Variables for list of lines
    List *lstHead;
    List *lstEnd;
    List *lstTrvr;
    List *nxtLine;
    List *prvLine;
    string data;
    List *nxtC;
    List *prvC;
    List *cTrvr;
    List *cLast;
    int lineCnt;
    double numTest;
    string hld;
};

#endif /* List_h */
