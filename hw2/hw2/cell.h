//
//  cell.h
//  hw2
//
//  Created by minnah on 3/11/16.
//  Copyright © 2016 minnah. All rights reserved.
//

#ifndef cell_h
#define cell_h

#include <string>

using namespace std;

struct cell{
    cell *cHead;
    cell *cLast;
    cell *cTrvr;
    cell *nxt;
    cell *prv;
    string data;
    //Functions
    cell();
    ~cell();
};

#endif /* cell_h */
