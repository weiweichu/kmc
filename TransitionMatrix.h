//
//  TransitionMatrix.h
//  TEKMC
//
//  Created by Weiwei Chu on 8/18/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

#ifndef __TEKMC__TransitionMatrix__
#define __TEKMC__TransitionMatrix__

//this is to calculate the transition matrix for all the ions
//read in the ion trajectory vector from ReadDumpFile
#include <stdio.h>
#include "ReadDumpFile.h"
#include "Grid.h"

using namespace Eigen;
using namespace std;

class TransitionMatrix{
public:
    TransitionMatrix(char* fname,double dgrid,int nframe):
    fname_(fname),
    dgrid_(dgrid),
    gridt_(1)
    {
        ReadDumpFile para(fname_,nframe);
        iontrj_=para.iontrj;
        //cout<<iontrj_.size()<<"size";
        box_=para.box;
        nframe_=para.nframe_;
        nion_=para.nion;
        grid_.setgrid(dgrid_, box_);
        calculate();
    };
    ~TransitionMatrix(){};
    ////this is used to calculate the transition matrix
    void calculate();
    ////this is to determine the motion of a bead at a, it returns the 1D grid index
    int move(int a);    
    ////this returns the 3D real position of the predicted move
    vector<Vector> maptorealposition(vector<int> gm);
    int gridt_;
    double displacement(int a, int b);
    
    
private:
    char* fname_;
    double dgrid_;
    //mtrj is the trajectory matrix for all the ions
    MatrixXd mtrj;
    //mt is the transition matrix we want
    VectorInt ngrid_;
    MatrixXf mt_;
    trj iontrj_;
    long nion_;
    vector<double> box_;
    int nframe_;
    Grid grid_;
   
    
};

#endif /* defined(__TEKMC__TransitionMatrix__) */
