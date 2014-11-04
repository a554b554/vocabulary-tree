//
//  candidatekeyframeselection.cpp
//  openCV
//
//  Created by DarkTango on 11/3/14.
//  Copyright (c) 2014 DarkTango. All rights reserved.
//

#include "candidatekeyframeselection.h"
/*vocabularytree::vocabularytree(const vector<featurepoint> &allfeatures,int level,int branch)
{
    this->branchingfactor = branch;
    this->totallevel = level;
    thresholdfoKmeans = 0.5;
    vector<featurepoint>::const_iterator iter;
    for (iter = allfeatures.begin(); iter != allfeatures.end(); iter++) {
        root->appendfeatureset(*iter);
    }
    node.push_back(*root);
}*/
void vocabularytree::kmeanconstructor(clusternode *currentnode)//cuurentnode is a node which contain a lots of featurepoint, center is a featurepoint.
{
    
    featurepoint *currentcenter = new featurepoint[this->branchingfactor];
    featurepoint *precenter = new featurepoint[this->branchingfactor];
    featurepoint point;
    double tempx,tempy;
    double mincost;
    double temp;
    bool breakflag=false;
    int count;
    
    
    for (int i = 0 ; i<this->branchingfactor ;i++) {
        currentcenter[i] = currentnode->at(i);
        currentnode->at(i).setflag(i);
        precenter[i]=currentnode->at(i);
        
    }
    while (!breakflag) {
        for (int i = 0; i<currentnode->size(); i++) {
            mincost = dist(currentnode->at(i), currentcenter[0]);
            currentnode->at(i).setflag(0);
            for (int j=1; j<this->branchingfactor; j++) {
                temp=dist(currentnode->at(i), currentcenter[j]);
                
                if (temp<mincost) {
                    mincost=temp;
                    currentnode->at(i).setflag(j);
                }
            }
        }
        for (int i = 0; i<this->branchingfactor; i++) {
            count=0;
            tempx=0;
            tempy=0;
            for (int j=0; j<currentnode->size(); j++) {
                if (currentnode->at(j).getflag()==i) {
                    count++;
                    tempx+=currentnode->at(j).getx();
                    tempy+=currentnode->at(j).gety();
                }
            }
            tempx/=count;
            tempy/=count;
            currentcenter[i].set(tempx, tempy);
        }
        breakflag = true;
        for (int i = 0; i<branchingfactor; i++) {
            if (dist(currentcenter[i], precenter[i])>thresholdfoKmeans) {
                breakflag = false;
                break;
            }
        }
        for (int i = 0 ; i<branchingfactor; i++) {
            precenter[i] = currentcenter [i];
        }
    }
    delete [] currentcenter;
    delete [] precenter;
    
}

featurepoint& clusternode::at(int i) //temporary.
{
    return featureset.at(i);
}

double vocabularytree::dist(const featurepoint &p1, const featurepoint &p2)//temporary.
{
    return p1.getx()*p1.getx()+p2.gety()*p2.gety();
}

void vocabularytree::setroot(const vector<featurepoint> &all)
{
    int i;
    for (i=0; i<all.size(); i++) {
        root->featureset.push_back(all[i]);
    }
}