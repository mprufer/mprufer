#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void initializeStack(int &stackTop);
bool isStackEmpty(int &stackTop);
bool isStackFull(int &stackTop);
void push(char brk, int &stackTop, char stack[]);
void pop(int &stackTop);
char queryTop(int &stackTop, char stack[]);
bool checkStack(int &stackTop, char stack[]);
void checkSymbol(char sym, int &stackTop, char stack[], int lNum);

int MAX = 2001;

int main(int argc, char * argv[]) {
    int stackTop = 0;
    int lNum = 1;
    char stack[MAX];
    ifstream readFile;
    string line = "";
    char *file = NULL;
    file = argv[1];
    readFile.open(file);
    if(readFile.fail()){
        cout << "Error reading." << endl;
        exit(1);
    }
    else{
        while(getline(readFile, line)){
            int i = 0;
            while(i != line.length()){
                if(line.at(i) == '(' || line.at(i) == '[' || line.at(i) == '{' || line.at(i) == '<'){
                    push(line.at(i), stackTop, stack);
                }
                else if(line.at(i) == ')' || line.at(i) == ']' || line.at(i) == '}' || line.at(i) == '>' || line.at(i) == 34 || line.at(i) == 39){
                    checkSymbol(line.at(i), stackTop, stack, lNum);
                }
                i++;
            }//end line length while
            lNum++;
        }//end file read while
    }
    readFile.close();
    if(isStackEmpty(stackTop)){
        cout << "ok" << endl;
    }
    else if (!isStackEmpty(stackTop)){
        cout << "Error in line " << lNum << ", top of stack=" << queryTop(stackTop, stack) << " current=$" << endl;
    }
    return 0;
}

void initializeStack(int &stackTop){
    stackTop = 0;
}

bool isStackEmpty(int &stackTop){
    return (stackTop == 0);
}

bool isStackFull(int &stackTop){
    return (stackTop == MAX);
}

void push(char brk, int &stackTop, char stack[]){
    if(!isStackFull(stackTop)){
        stack[stackTop] = brk;
        stackTop++;
    }
    else{
        cout << "Stack is full." << endl;
    }
}
void pop(int &stackTop){
    if(!isStackEmpty(stackTop)){
        stackTop--;
    }
    else{
        cout << "stack empty." << endl;
    }
}
char queryTop(int &stackTop, char stack[]){
    if(stackTop == 0){
        return ' ';
    }
    else{
        return stack[stackTop-1];
    }
}

void checkSymbol(char sym, int &stackTop, char stack[], int lNum){
    if(sym == 34 || sym == 39){
        if(queryTop(stackTop, stack) == sym){
            pop(stackTop);
        }
        else{
            push(sym, stackTop, stack);
        }
    }
    else if(isStackEmpty(stackTop)){
        cout << "Error in line " << lNum << ", top of stack=" << " current=" << sym << endl;
        exit(1);
    }
    else{
        switch(sym){
            case ')':{
                if(queryTop(stackTop, stack) != '('){
                    cout << "Error in line " << lNum << ", top of stack=" << queryTop(stackTop, stack) << " current=" << sym << endl;
                    exit(0);
                    break;
                }//end if
                else{
                    pop(stackTop);
                    break;
                }
                break;
            }//end case
            case ']':{
                if(queryTop(stackTop, stack) != '['){
                    cout << "Error in line " << lNum << ", top of stack=" << queryTop(stackTop, stack) << " current=" << sym << endl;
                    exit(0);
                    break;
                }
                else{
                    pop(stackTop);
                    break;
                }
                break;
            }//end case
            case '}':{
                if(queryTop(stackTop, stack) != '{'){
                    cout << "Error in line " << lNum << ", top of stack=" << queryTop(stackTop, stack) << " current=" << sym << endl;
                    exit(0);
                    break;
                }
                else{
                    pop(stackTop);
                    break;
                }
                break;
            }//end case
            case '>':{
                if(queryTop(stackTop, stack) != '<'){
                    cout << "Error in line " << lNum << ", top of stack=" << queryTop(stackTop, stack) << " current=" << sym << endl;
                    exit(1);
                    break;
                }
                else{
                    pop(stackTop);
                    break;
                }
                break;
            }//end case
        }
    }
}
