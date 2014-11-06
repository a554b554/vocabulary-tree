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
extern int quickpow(int m,int n);
using namespace std;
class ee
{
public:
    ee(){cout<<"ee()"<<endl;};
    ~ee(){cout<<"~ee()"<<endl;};
};
void go()
{
    cout<<"go"<<endl;
    ee *q = new ee;
}
int main(int argc, const char * argv[]) {
    /*vector<featurepoint> pointset;
    const int testsize = 10000;
    featurepoint *temp = new  featurepoint;
   // srand(time(0));
    for (int i = 0; i<testsize; i++) {
       
        temp->set(rand()%100, rand()%100);
        pointset.push_back(*temp);
    }
    delete temp;

    cout<<"~~~~~~~~~~"<<endl;
    vocabularytree tree;
    tree.setroot(pointset);
   
    //cout<<"size:"<<tree.root->size()<<endl;
    tree.construction(*tree.root);
    cout<<"tree info"<<endl;
    tree.printnode(*tree.root);
    */
    cout<<"1"<<endl;
    go();
    cout<<2<<endl;
    cout<<quickpow(3,3)<<endl;
    
    
    
    return 0;
}
