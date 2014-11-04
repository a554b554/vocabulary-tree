//
//  main.cpp
//  testcode
//
//  Created by DarkTango on 10/25/14.
//  Copyright (c) 2014 DarkTango. All rights reserved.
//

#include <iostream>
#include <vector>
#include "candidatekeyframeselection.h"
using namespace std;
int main(int argc, const char * argv[]) {
    vector<featurepoint> pointset;
    const int testsize = 100;
    featurepoint *temp = new  featurepoint;
   // srand(time(0));
    for (int i = 0; i<testsize; i++) {
       
        temp->set(rand()%100, rand()%100);
        pointset.push_back(*temp);
    }
    delete temp;
    for (int i=0; i<testsize; i++) {
        cout<<"x:"<<pointset[i].getx()<<"y:"<<pointset[i].gety()<<endl;
    }
    vocabularytree tree;
    
    return 0;
}