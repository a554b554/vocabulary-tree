//
//  candidatekeyframeselection.h
//  openCV
//
//  Created by DarkTango on 11/3/14.
//  Copyright (c) 2014 DarkTango. All rights reserved.
//

#ifndef __openCV__candidatekeyframeselection__
#define __openCV__candidatekeyframeselection__

#include <queue>
#include <stdio.h>
#include <list>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
class featurepoint
{
    double x;
    double y;
    int flag;
    int point_id();
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
class frame
{
    int frame_id;
    double matchingvalue;
public:
    frame();
    vector<featurepoint*> point;
    int getframeid()const{return frame_id;};
    double getmachingvalue()const{return matchingvalue;};
};
class frameset
{
public:
    vector<frame*> point;
};
/*********above is temporary class*******/
class clusternode
{
    static int branchingfactor;
    static int totallevel;
public:
    vector <featurepoint> featureset;
    vector <clusternode*> child;
    static int getbranchingfactor();
    static int gettotallevel();
   // clusternode();
    //clusternode(clusternode &node);
    void init();
    int getlevel();
   // void appendchild(clusternode* node);
    //void appendfeatureset(featurepoint p);
    featurepoint& at(int i);
    size_t size()const{return featureset.size();};//size of featureset.
    void print();
    int getnumberofspannedframe();

};
class vocabularytree
{
private:

    int branchingfactor;
    int totallevel;
    double thresholdfoKmeans;
    int counterforlevel;
    int totalnumberofkeyframe;
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
    double getweight(clusternode &node);
    frameset candidatekeyframesearching(frameset &candidateframe,vector<featurepoint> &pointinliveframe);
    
    vector<clusternode*>* getnodebylevel(int level);
};
#endif /* defined(__openCV__candidatekeyframeselection__) */
