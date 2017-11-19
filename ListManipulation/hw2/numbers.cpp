#include <iostream>
#include "FileOps.hpp"

int main(int argc, char * argv[]) {
    FileOps fOps;
    char *file = NULL;
    file = argv[1];
    fOps.parseFile(file);
    fOps.print();
    return 0;
}
