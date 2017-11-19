//
//  main.cpp
//  Recursion
//
//  Created by minnah on 3/2/16.
//  Copyright © 2016 minnah. All rights reserved.
//

#include <iostream>

int rFibNum(int a, int b, int n);

using namespace std;

int main(int argc, const char * argv[]) {
    int firstFibNum = 0;
    int secondFibNum = 0;
    int nth = 0;
    
    cout << "Enter the first Fibonacci number: ";
    cin >> firstFibNum;
    cout << endl;
    
    cout << "Enter the second Fibonacci number: ";
    cin >> secondFibNum;
    cout << endl;
    
    cout << "Enter the position of the desired Fiboniacci number: ";
    cin >> nth;
    cout << endl;
    
    cout << "The Fibonacci number is: " << rFibNum(firstFibNum, secondFibNum, nth) << endl;
    return 0;
}

int rFibNum(int a, int b, int n){
    if(n == 1)
        return a;
    else if(n == 2)
        return b;
    else
        return rFibNum(a, b, n-1) + rFibNum(a, b, n-2);
}