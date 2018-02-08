#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "FileOps.hpp"

using namespace std;

int main(int argc, char * argv[]) {
    FileOps fops;
    string parameter = argv[1];
    //Parse the argument for each part of it. The rest of the program is operated from there.
    fops.parse(parameter);
    return 0;
}
