//
//  candidatekeyframeselection.cpp
//  openCV
//
//  Created by DarkTango on 11/3/14.
//  Copyright (c) 2014 DarkTango. All rights reserved.
//
#include <cstdio>
#include "candidatekeyframeselection.h"
clusternode::clusternode()
{
    
}
vocabularytree::vocabularytree()
{
    root = new clusternode;
    this->branchingfactor = 3;
    this->totallevel = 3;
    thresholdfoKmeans = 10;
    counterforlevel = 0;
}
void vocabularytree::kmeanconstructor(clusternode &currentnode)//currentnode is a node which contain a lots of featurepoint, center is a featurepoint.
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
        currentcenter[i] = currentnode.at(rand()%currentnode.size());
        currentnode.at(i%currentnode.size()).setflag(i);
       // precenter[i]=currentnode->at(i);
        currentcenter[i].print();
        cout<<"~~~~~~~~~~~~~~~~~"<<endl;
    }
    for (int i = 0; i<currentnode.size(); i++) {
        currentnode.at(i).setflag(i%branchingfactor);
    }
    while (!breakflag) {
        for (int i = 0; i<currentnode.size(); i++) {
            mincost = dist(currentnode.at(i), currentcenter[0]);
            currentnode.at(i).setflag(0);
            for (int j=1; j<this->branchingfactor; j++) {
                temp=dist(currentnode.at(i), currentcenter[j]);
                
                //currentcenter[j].print();
                
                if (temp<mincost) {
                    mincost=temp;
                    currentnode.at(i).setflag(j);
                }
            }
        }
 
        for (int i = 0; i<this->branchingfactor; i++) {
            count=0;
            tempx=0;
            tempy=0;
            
            for (int j=0; j<currentnode.size(); j++) {
                if (currentnode.at(j).getflag()==i) {
                    count++;
                    tempx+=currentnode.at(j).getx();
                    tempy+=currentnode.at(j).gety();
                }
            }
            tempx/=count;
            tempy/=count;
            currentcenter[i].set(tempx, tempy);
           // cout<<i<<" "<<currentcenter[i].getx()<<" "<<currentcenter[i].gety()<<endl;
        }
        breakflag = true;
        for (int i = 0; i<branchingfactor; i++) {
            if (dist(currentcenter[i], precenter[i])>thresholdfoKmeans) {
                breakflag = false;
                break;
            }
        }
        
        for (int i = 0 ; i<branchingfactor; i++) {
            /*cout<<"pre:";
            precenter[i].print();
            cout<<"cur:";
            currentcenter[i].print();*/
            precenter[i] = currentcenter [i];
        }
        cout<<"~~~~~~~~"<<endl;
    }
   //new node for cluster
    
    for (int i = 0; i<branchingfactor; i++) {
        clusternode *newnode = new clusternode;
        for (int j = 0; j<currentnode.size(); j++) {
            if (currentnode.at(j).getflag()==i) {
                newnode->featureset.push_back(currentnode.at(j));
                
            }
        }
        currentnode.child.push_back(newnode);
        cout<< i<<": "<<currentnode.child[i]->featureset.size()<<endl;
       // delete  newnode;
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
    return (p1.getx()-p2.getx())*(p1.getx()-p2.getx())+(p1.gety()-p2.gety())*(p1.gety()-p2.gety());
}

void vocabularytree::setroot(const vector<featurepoint> &all)
{
    int i;
    for (i=0; i<all.size(); i++) {
        root->featureset.push_back(all[i]);
    }
}

void clusternode::init()
{
    featureset.clear();
    child.clear();
}

void featurepoint::print()
{
    printf("x:%lf,y:%lf\n",this->x,this->y);
}

clusternode::clusternode(clusternode &node)
{
    this->featureset=node.featureset;
    for (int i = 0; i<node.child.size(); i++) {
        this->child.push_back(node.child[i]);
    }
}

void vocabularytree::construction(clusternode &node)//recursive construction for vocabulary.
{
    kmeanconstructor(node);
    if (getlevelofcurrenttree()<totallevel) {//wait for implement.
        for (int i = 0; i<branchingfactor; i++) {
            construction(*(node.child[i]));
        }
    }
   
}

int vocabularytree::getlevelofcurrenttree()
{
    int counter=1;
    clusternode *p;
    p=root;
    while (!p->child.empty()) {
        p=p->child[0];
        counter++;
    }
    return counter;
}

void vocabularytree::printinfo()
{
    clusternode *p = new clusternode;
    p=root;
    p->print();
   
}

void clusternode::print()
{
    printf("nodesize:%zu\n",size());
}

void vocabularytree::printnode(clusternode &node)
{
    clusternode *p = new clusternode;
    p=&node;
    counterforlevel++;
    cout<<"node:"<<counterforlevel;
    p->print();
    if(!(p->child.empty())){
        for (int i = 0; i<branchingfactor; i++) {
            
            printnode(*(p->child[i]));
            
        }
    }
}