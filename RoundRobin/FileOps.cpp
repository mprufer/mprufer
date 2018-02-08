#include "FileOps.hpp"
#include <iostream> 
#include <fstream>

using namespace std;

stringstream cnvrt;

FileOps::FileOps(){
    file = "";
    qsize = 0;
    quantum = 0;
    schedule = "";
    pos = 0;
    lpos = 0;
    line = "";
    count = 0;
    name = "";
    arrival = 0;
    duration = 0;
    token = "";
}

//Recursive: Each part of the argument is parsed. If the argument being parsed is not quantum (aka the last argument to be parsed) then the function is called again to parse the next part of the argument.
//PostCondition: Each part of the argument is parsed and passed properly.
void FileOps::parse(string argument){
    //Each part of the argument always has an equal sign and parsing it one-by-one
    pos = argument.find_first_of('=');
    //Since quantum does not end with a ';', only need to find and parse for arguments before
    if (file == "" || qsize == 0 || schedule == ""){
        lpos = argument.find_first_of(';');
        if(file == ""){
            file = argument.substr(pos+1, lpos-(pos+1));
            parse(argument.substr(lpos+1));
        }
        else if(qsize == 0){
            cnvrt.clear();
            cnvrt << argument.substr(pos+1, lpos-(pos+1));
            cnvrt >> qsize;
            parse (argument.substr(lpos+1));
        }
        //The last thing to be parsed ending with a ';' is the schedule. After that you can't find the pos of ';' since it dne at the end of quantum so it breaks out of this if statement next call
        else{
            schedule = argument.substr(pos+1, lpos-(pos+1));
            parse(argument.substr(lpos+1));
        }
    }
    //Last part of argument (quantum) is parsed.
    else{
        //If schedule is roundrobin, then find quantum. Otherwise, don't need to waste computer time finding it for fifo.
        if(schedule == "roundrobin"){
            cnvrt.clear();
            cnvrt << argument.substr(pos+1);
            cnvrt >> quantum;
            //Queue needs to be created first before it can be filled.
            robin.createQueue(qsize);
            robin.setQMax(qsize);
            robin.setQuantum(quantum);
            readFile(file);
        }
        else if(schedule == "shortfifo"){
            readFile(file);
        }
        else{
            readFile(file);
            //nothing else needs to passed.
        }
    }//end else
}

//Reads the file line by line, then does it each by tab (which is the argument parser). It then fills queue (which should've already been created by a call in the parse function)
void FileOps::readFile(string file){
    ifstream openfile(file);
    if(openfile.fail()){
        cout << "File couldn't be opened." << endl;
        exit(1);
    }
    else{
        //Checks if file is empty. If it is then nothing is outputted.
        if(openfile.peek() == std::ifstream::traits_type::eof()){
            //Apparently no one needs to get their make-up done. I see how it is.
        }
        //Read file line by line
        else{
            while(getline(openfile, line)){
                stringstream linestream(line);
                if(line.at(0) == '#'){
                    //do nothing since it's a comment
                }
                else{
                    //Parse line by tab
                    while(getline(linestream, token, '\t')){
                        //Name is set first
                        if(count == 0){
                            name = token;
                            count++;
                        }
                        //Arrival is set since it is the second part of the line
                        else if(count == 1){
                            cnvrt.clear();
                            cnvrt << token;
                            cnvrt >> arrival;
                            count++;
                        }
                        //Duration is set as it is the last part of the line
                        else{
                            cnvrt.clear();
                            cnvrt << token;
                            cnvrt >> duration;
                            count = 0; //reset count for the next line to be read
                        }
                    }//end by tab while
                    //Fill queue depending on which schedule is being used
                    if(schedule == "roundrobin"){
                        robin.fillQueue(name, arrival, duration);
                    }
                    else if(schedule == "shortfifo"){
                        ff.fillQueue(name, arrival, duration);
                    }
                    else{
                        //Passes to fifo fill queue
                        ff.applyMakeup(name, arrival, duration);
                    }
                }//end else
            }//end getline while
        }//end getline else
    }//end eof if statement
    openfile.close();
    //print the full schedule/simluation of make-up application
    if(schedule == "roundrobin"){
        robin.print();
    }
    else if(schedule == "shortfifo"){
        ff.sort();
    }
}
