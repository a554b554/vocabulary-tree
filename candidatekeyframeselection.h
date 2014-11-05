//
//  candidatekeyframeselection.h
//  openCV
//
//  Created by DarkTango on 11/3/14.
//  Copyright (c) 2014 DarkTango. All rights reserved.
//

#ifndef __openCV__candidatekeyframeselection__
#define __openCV__candidatekeyframeselection__

#include <stdio.h>
#include <list>
#include <vector>
#include "frame.h"
using namespace std;
class featurepoint
{
    double x;
    double y;
    int flag;
public:
    featurepoint():x(0),y(0),flag(-1){};
    featurepoint(double a,double b):x(a),y(b),flag(-1){};
    int getflag(){return flag;};
    void setflag(int i){flag=i;};

    void set(double x,double y)
    {
        this->x=x;
        this->y=y;
    };
    double getx()const{return x;};
    double gety()const{return y;};
    void operator=(featurepoint& rhs)
    {
        this->x=rhs.x;
        this->y=rhs.y;
    }
    void print();
};
class clusternode
{
    static int branchingfactor;
    static int totallevel;
public:
    vector <featurepoint> featureset;
    vector <clusternode*> child;
    static int getbranchingfactor();
    static int gettotallevel();
    clusternode();
    clusternode(clusternode &node);
    void init();
    int getlevel();
   // void appendchild(clusternode* node);
    //void appendfeatureset(featurepoint p);
    featurepoint& at(int i);
    size_t size()const{return featureset.size();};//size of featureset.
    void print();

};
class vocabularytree
{
private:

    int branchingfactor;
    int totallevel;
    double thresholdfoKmeans;
    int counterforlevel;
public:
    vector<clusternode> node;
    clusternode *root;
    vocabularytree();
    vocabularytree(const vector <featurepoint> &allfeatures,int level,int brach);
    void setroot(const vector<featurepoint> &all);
    const frame& findkeyframe();
    double dist(const featurepoint& p1,const featurepoint& p2);
    void kmean();
    void kmeanconstructor(clusternode &currentnode);
    void construction(clusternode &node);
    int getbranch(){return branchingfactor;};
    int gettotallevel(){return totallevel;};
    int getlevelofcurrenttree();
    void printinfo();
    void printnode(clusternode &node);
};
#endif /* defined(__openCV__candidatekeyframeselection__) */
