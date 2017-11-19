#include "FileOps.hpp"

stringstream toInt;

FileOps::FileOps(){
    line = "";
    token = "";
    iFile = "";
    oFile = "";
    command = "";
    lineNum = "";
    op = "";
    com = ' ';
    pos = 0;
    sPos = 0;
    lNum = 0;
}

//PreCondition: Argument is read and passed as a string to be parsed.
//PostCondition: File is parsed into two files: inputFile & opsFile. inputFile is passed to buildLists function to build linked list.
//opsFile is passed to doOps function to perform operations on built linked list.
void FileOps::parseFile(string argument){
    pos = argument.find_first_of("=");
    sPos = argument.find(";");
    //Parse iFile from argument
    iFile = argument.substr(pos+1, sPos-(pos+1));
    //Parse oFile from argument
    pos = argument.find_last_of("=");
    oFile = argument.substr(pos+1);
    //Pass files after being parsed to be read
    buildList(iFile);
    getOp(oFile);
}

//PreCondition: inputFile is parsed and passed to be read.
//PostCondition: File is read and linked list is built.
void FileOps::buildList(string iFile){
    ifstream openfile(iFile);
    if(openfile.fail()){
        cout << "File couldn't be opened." << endl;
        exit(1);
    }
    else{
        //Checks if file is empty. If it is, an empty list is created
        if(openfile.peek() == std::ifstream::traits_type::eof()){
            lst.createLines(false);
            lst.createCells("");
        }
        //Read file line by line
        else{
            while(getline(openfile, line)){
                //Only creates new node to hold line if there's another line read
                lst.createLines(false);
                stringstream linestream(line);
                //Parse line by tab
                while(getline(linestream, token, '\t')){
                    lst.createCells(token);
                }//end while
            }//end while
        }
    }//end eof if statement
    openfile.close();
}

//PreCondition: OpsFile successfully opened and parsed.
//PostCondition: Command is parsed and returned back to switch menu in doOps to perform the appropriate function.
//Note: lineNum is parsed diferently if it is a deleteline/insertline or a mathline. Since mathline has an additional command after the lineNum it must be parsed differently from deleteline/insertline hence the different parsing commands.
void FileOps::getOp(string command){
    ifstream openfile(oFile);
    if(openfile.fail()){
        cout << "File couldn't be opened." << endl;
        exit(1);
    }
    else{
        while(openfile >> command){
            if(command.at(0) == 'i' || command.at(0) == 'd'){
                pos = command.find_first_of(":");
                lineNum = command.substr(pos+1);
                command = command.substr(0, pos);
                //Convert lineNum to int to be passed
                toInt.clear();
                toInt << lineNum;
                toInt >> lNum;
                //////////////
                if(command == "insertline")
                    lst.insertLine(lNum);
                else
                    lst.deleteLine(lNum);
            }
            else{
                pos = command.find_first_of(":");
                sPos = command.find_last_of(":");
                lineNum = command.substr(pos+1, 1);
                //Convert lineNum to int to be passed
                toInt.clear();
                toInt << lineNum;
                toInt >> lNum;
                //////////////
                command = command.substr(sPos+1);
                if(command == "count"){
                    lst.count(lNum);}
                else if(command == "max"){
                    lst.max(lNum);}
                else if(command == "min"){
                    lst.min(lNum);}
                else if(command == "normalize"){
                    lst.normalize(lNum);}
                else if (command == "mean"){
                    lst.mean(lNum);
                }
                else{
                    //do nothing
                }
            }//end else(mathline)
        }//end while
    }//end else(file is_open)
}
void FileOps::print(){
    lst.print();
}