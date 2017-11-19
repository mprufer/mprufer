#include <stdio.h>
#include "List.h"

List::List(){
    nxtLine = NULL;
    prvLine = NULL;
    lstHead = NULL;
    lstTrvr = NULL;
    lstEnd = NULL;
    nxtC = NULL;
    prvC = NULL;
    data = "";
    cLast = NULL;
    lineCnt = 1;
    numTest = 0.0;
    hld = "";
}

List::~List(){
    List *tmp = lstHead;
    while(tmp){
        lstHead = lstHead->nxtLine;
        cTrvr = tmp;
        while(tmp){
            cTrvr = cTrvr->nxtC;
            delete tmp;
            tmp = cTrvr;
        }
        tmp = lstHead;
    }
    lstEnd = lstHead = NULL;
}

//PreCondition: Text file is read and parsed.
//PostCondition: Nodes are created to hold the content of each line (ie the sublists are created). If the text file is blank, then "" was passed and only one node was created.
void List::createCells(string info){
    List *newNode = new List;
    newNode->data = info;
    newNode->nxtC = NULL;
    newNode->prvC = NULL;
    //If cTrvr->data == "" then the line is empty and none of its contents have been passed.
    if(cTrvr->data == ""){
        cTrvr->data = newNode->data;
        cTrvr->nxtC = newNode->nxtC;
        cTrvr->prvC = newNode->prvC;
        cTrvr->cLast = cTrvr;
    }
    else{
        newNode->prvC = cTrvr->cLast;
        cTrvr->cLast->nxtC = newNode;
        cTrvr->cLast = newNode;
    }
}

//PreCondition: The file has been successfully read.
//PostCondition: At least one node has been created to represent a line in the text file (if the file is blank than an empty list is created). For every line is that read in the text file, a new node is created & inserted in the list to hold its contents.
void List::createLines(bool instCmmd){
    List *newNode = new List;
    newNode->prvLine = NULL;
    newNode->nxtLine = NULL;
    newNode->data = "";
    //cTrvr is set to the newNode so that the each new line added is kept track of and the contents of each line is added to the proper sublist.
    cTrvr = newNode;
    if(instCmmd == false){
        if(lstHead == NULL){
            lstHead = newNode;
            lstEnd = newNode;
        }
        else{
            newNode->prvLine = lstEnd;
            lstEnd->nxtLine = newNode;
            lstEnd = newNode;
        }
    }
    else{
        //Inserting line at last line
        if(lstTrvr == lstEnd->prvLine){
            newNode->prvLine = lstTrvr;
            newNode->nxtLine = lstEnd;
            lstEnd->prvLine = newNode;
            lstTrvr->nxtLine = newNode;
        }
        //Inserting line after last line
        else if(lstTrvr == lstEnd){
            lstTrvr->nxtLine = newNode;
            newNode->prvLine = lstTrvr;
            lstEnd = newNode;
        }
        else{
            newNode->prvLine = lstTrvr;
            newNode->nxtLine = lstTrvr->nxtLine;
            lstTrvr->nxtLine->prvLine = newNode;
            lstTrvr->nxtLine = newNode;
        }
    }
}

//PreCondition: Line number is successfully parsed and pased from getOp in FileOps class.
//PostCondition: lstTrvr points to the correct line number so ops can be done on that line.
void List::setLstTrvr(List *trvr, int lNum, int count){
    int tmp = lNum;
    if(tmp <= 1){
        lstTrvr = lstHead;
    }
    else if(count == tmp){
        //Trvr is set to the correct line.
    }
    else{
        if(lstTrvr->nxtLine == NULL){
            //Trvr set
        }
        else{
            lstTrvr = lstTrvr->nxtLine;
            setLstTrvr(lstTrvr, tmp, count+1);
        }
    }
}

//PreCondition: Line number is successfully pasred and passed from getOp in FileOps class.
//PostCondition: A new line is inserted at the line indicated and the line ordering is changed.
void List::insertLine(int line){
    lstTrvr = lstHead;
    if(lstHead == NULL){
        createLines(false);
    }
    else{
        lineCnt = 1;
        setLstTrvr(lstTrvr, line-1, lineCnt);
        List *newNode = new List;
        newNode->data = "";
        newNode->prvLine = NULL;
        newNode->nxtLine = NULL;
        if(line <= 2){
            switch(line){
                case(1):{
                    lstHead = newNode;
                    lstHead->nxtLine = lstTrvr;
                    lstTrvr->prvLine = lstHead;
                    break;
                }
                case(2):{
                    createLines(true);
                    break;
                }
            }
        }
        else{
            createLines(true);
        }
    }
}

//PreCondition: Line number to delete successfully parsed and passed from getOps in FileOps Class
//PostCondition: Line number is deleted and linked lists are correctly linked after deletion.
void List::deleteLine(int line){
    lstTrvr = lstHead;
    lineCnt = 1;
    setLstTrvr(lstTrvr, line, lineCnt);
    if(lstTrvr == lstHead){
        //Only one node left in list
        if(lstHead->nxtLine == NULL){
            lstHead = lstEnd = NULL;
            deallocate(lstTrvr);
        }
        else{
            lstHead = lstTrvr->nxtLine;
            lstHead->prvLine = NULL;
            deallocate(lstTrvr);
        }
    }
    else if(lstTrvr == lstEnd){
        lstEnd = lstTrvr->prvLine;
        lstEnd->nxtLine = NULL;
        deallocate(lstTrvr);
    }
    else{
        List *tmp = lstTrvr->prvLine;
        tmp->nxtLine = lstTrvr->nxtLine;
        tmp->nxtLine->prvLine = tmp;
        deallocate(lstTrvr);
    }
}

//Deletes node from linked list by traversing through the list's sub-list.
void List::deallocate(List *tmp){
    cTrvr = tmp;
    while(tmp){
        cTrvr = cTrvr->nxtC;
        delete tmp;
        tmp = cTrvr;
    }
}
void List::count(int line){
    lstTrvr = lstHead;
    lineCnt = 1;
    setLstTrvr(lstTrvr, line, lineCnt);
    int count = 0;
    cTrvr = lstTrvr;
    if(lstHead == NULL){
        createLines(false);
        createCells("0");
    }
    else{
        stringstream convert;
        convert.clear();
        convert << isDouble(cTrvr->data, count);
        convert >> hld;
        cTrvr = lstTrvr;
        createCells(hld);
    }
}

//Checks to see if the info contained in the node is a double.
//If it is, then the count goes up. If not, then the count remains the same.
//Base Case: The list has been fully traversed and the pointer points to nothing.
int List::isDouble(string info, int count){
    stringstream test;
    test.clear();
    test << info;
    test >> numTest;
    cTrvr = cTrvr->nxtC;
    if(cTrvr == NULL){
        if(test.fail()){
            return count;
        }
        else{
            return count+1;
        }
    }
    else{
        //If the list is empty, that means there is nothing to count which means count remains 0 (as it was passed being set to 0)
        if(info == ""){
            return isDouble(cTrvr->data, count);
        }
        else if(test.fail()){
            return isDouble(cTrvr->data, count);
        }
        else{
            return isDouble(cTrvr->data, count+1);
        }
    }
}

//Finds the max of the line passed by getOps in FileOps class.
void List::max(int line){
    double max = 0.0;
    lineCnt = 1;
    lstTrvr = lstHead;
    setLstTrvr(lstTrvr, line, lineCnt);
    cTrvr = lstTrvr;
    //If list is completely empty (as in all lines have been deleted), then a list is created and undefined is passed to be the contents of the first node.
    if(lstHead == NULL){
        createLines(false);
        createCells("undefined");
    }
    //If isDouble(which counts the number of numbers in a line) is == 0, that means there are no numbers in the line so undefined should be passed to indicate there is no max.
    else if(isDouble(cTrvr->data, max) == 0){
        cTrvr = lstTrvr;
        createCells("undefined");
    }
    else{
        cTrvr = lstTrvr;
        findMax(cTrvr, max);
    }
}

//Only called when the lstHead != NULL && it's been checked that the list does actually contain numbers.
//Finds the max number in the list.
void List::findMax(List *tmp, double max){
    stringstream cnvrt;
    cnvrt.clear();
    if(tmp == NULL){
        cTrvr = lstTrvr;
        cnvrt << trunc(max);
        cnvrt >> hld;
        createCells(hld);
    }
    else{
        cnvrt << tmp->data;
        cnvrt >> numTest;
        if(cnvrt.fail()){
            findMax(tmp->nxtC, max);
        }
        else{
            if(numTest >= max){
                max = numTest;
                findMax(tmp->nxtC, max);
            }
            else{
                findMax(tmp->nxtC, max);
            }
        }
    }
}

//The line to find the min of is passed from the getOps func in the File Ops class.
//Once passed, it sets the pointers to the correct line and performs operation based on the current condition of the list.
void List::min(int line){
    int count = 0;
    double min = 0.0;
    lineCnt = 1;
    lstTrvr = lstHead;
    setLstTrvr(lstTrvr, line, lineCnt);
    cTrvr = lstTrvr;
    //If list is completely empty (as in all lines have been deleted), then a list is created and undefined is passed to be the contents of the first node.
    if(lstHead == NULL){
        createLines(false);
        createCells("undefined");
    }
    //If isDouble(which counts the number of numbers in a line) is == 0, that means there are no numbers in the line so undefined should be passed to indicate there is no min.
    else if(isDouble(cTrvr->data, min) == 0){
        cTrvr = lstTrvr;
        createCells("undefined");
    }
    //The number contains numbers and is not empty therefore the min can be found.
    else{
        cTrvr = lstTrvr;
        findMin(cTrvr, min, count);
    }
}

//PreCondition: The list is not empty & it contains numbers to find the min of.
//PostCondition: Min is found and passed to be added to the end of a line's list.
void List::findMin(List *tmp, double min, int count){
    stringstream cnvrt;
    cnvrt.clear();
    //The whole sublist has been traversed so the recursion ends & the min is passed to be added to the end of the list.
    if(tmp == NULL){
        cTrvr = lstTrvr;
        cnvrt << trunc(min);
        cnvrt >> hld;
        createCells(hld);
    }
    else{
        cnvrt << tmp->data;
        cnvrt >> numTest;
        //If the node's content is a word then conversion fails and it moves on to the next node.
        if(cnvrt.fail()){
            findMin(tmp->nxtC, min, count);
        }
        else{
            //The first number of the list has been found and min is set to it. Required so that there's at least one number to start comparison to.
            if(count == 0){
                min = numTest;
                count++;
                findMin(tmp->nxtC, min, count);
            }
            else if(numTest <= min){
                min = numTest;
                findMin(tmp->nxtC, min, count);
            }
            else{
                findMin(tmp->nxtC, min, count);
            }
        }
    }
}

//Receives the line to calculate the mean from getOps func in File Ops class.
void List::mean(int line){
    stringstream avg;
    avg.clear();
    double mean = 0.0;
    int amnt = 0;
    lineCnt = 1;
    lstTrvr = lstHead;
    setLstTrvr(lstTrvr, line, lineCnt);
    cTrvr = lstTrvr;
    if(lstHead == NULL){
        createLines(false);
        createCells("undefined");
    }
    else{
        amnt = isDouble(cTrvr->data, amnt);
        if(amnt == 0){
            cTrvr = lstTrvr;
            createCells("undefined");
        }
        else{
            cTrvr = lstTrvr;
            mean = findMean(cTrvr, mean, amnt);
            avg << trunc(mean);
            avg >> hld;
            cTrvr = lstTrvr;
            createCells(hld);
        }
    }
}

//Calculates and returns the mean of the line recieved.
double List::findMean(List *trvr, double mean, int amnt){
    double num = 0.0;
    stringstream dbl;
    dbl.clear();
    if(trvr == NULL){
        mean = mean/amnt;
        return mean;
    }
    else{
        dbl << trvr->data;
        dbl >> num;
        if(dbl.fail()){
            return findMean(trvr->nxtC, mean, amnt);
        }
        else{
            mean += num;
            return findMean(trvr->nxtC, mean, amnt);
        }
    }
}

void List::normalize(int line){
    double avg = 0.0;
    int cnt = 0;
    lineCnt = 1;
    lstTrvr = lstHead;
    setLstTrvr(lstTrvr, line, lineCnt);
    cTrvr = lstTrvr;
    //Find amount of numbers in the line
    cnt = isDouble(cTrvr->data, cnt);
    cTrvr = lstTrvr;
    //Find mean of line
    avg = findMean(cTrvr, avg, cnt);
    cTrvr = lstHead;
    lstTrvr = lstHead;
    ///////
    if(avg == 0){
        normalizeByZero(lstTrvr, cTrvr, avg);
    }
    else{
        doNormalize(lstTrvr, cTrvr, avg);
    }
}

void List::doNormalize(List *lTmp, List *cTmp, double avg){
    stringstream tst;
    tst.clear();
    double num = 0.0;
    if(lTmp == NULL){
        //list finished
    }
    else{
        if(cTmp == NULL){
            lTmp = lTmp->nxtLine;
            cTmp = lTmp;
            doNormalize(lTmp, cTmp, avg);
        }
        else{
            tst << cTmp->data;
            tst >> num;
            if(tst.fail()){
                doNormalize(lTmp, cTmp->nxtC, avg);
            }
            else{
                num = num/avg;
                tst.clear();
                tst << trunc(num);
                tst >> hld;
                cTmp->data = hld;
                doNormalize(lTmp, cTmp->nxtC, avg);
            }
        }//end convert else
    }//end 1st else
}

void List::normalizeByZero(List *lTmp, List *cTmp, double avg){
    stringstream tst;
    tst.clear();
    double num = 0.0;
    if(lTmp == NULL){
            //list finished
    }
    else{
        if(cTmp == NULL){
            lTmp = lTmp->nxtLine;
            cTmp = lTmp;
            normalizeByZero(lTmp, cTmp, avg);
        }
        else{
            tst << cTmp->data;
            tst >> num;
            if(tst.fail()){
                normalizeByZero(lTmp, cTmp->nxtC, avg);
            }
            else{
                cTmp->data = "undefined";
                normalizeByZero(lTmp, cTmp->nxtC, avg);
            }
        }//end convert else
    }//end 1st else
}

//Sets both pointers before passing them to be printed recursively.
void List::print(){
    lstTrvr = lstHead;
    cTrvr = lstTrvr;
    printList(lstTrvr, cTrvr);
}

//Prints the linked list recursively.
void List::printList(List *lineTmp, List *cTmp){
    if(lineTmp == NULL){
        //list has been printed
    }
    else{
        if(cTmp->nxtC == NULL){
            cout << cTmp->data << endl;
            lineTmp = lineTmp->nxtLine;
            cTmp = lineTmp;
            printList(lineTmp, cTmp);
        }
        else{
            cout << cTmp->data << '\t';
            printList(lineTmp, cTmp->nxtC);
        }
    }
}