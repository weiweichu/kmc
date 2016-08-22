//
//  main.cpp
//  TEKMC
//
//  Created by Weiwei Chu on 8/17/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Eigen/Dense"
#include "KineticMC.h"

using namespace std;
using namespace Eigen;
int main(int argc, const char * argv[]) {

	     
	//char fname[]="npt.lammpstrj";
	//double dgrid=40;
	//int nframe=20;
	//TransitionMatrix t(fname,dgrid,nframe);
	
	
	
    char fname[]="npt.lammpstrj";
    double dgrid=20;
    int nstep=10000;
    int nframe=20;
    vector<Vector> realtr;
    vector<double> msd;
    KineticMC sys;  
    sys.run(fname, dgrid, nstep,nframe);
    ofstream msdo;
    ofstream trj;
    realtr=sys.realtr_;
    msd=sys.msd_;
    msdo.open("msd.txt");
    trj.open("trj.txt");
    msdo<<msd.size()<<endl;
    for (int i=0; i<msd.size(); i++) {
        msdo<<msd[i]<<endl;
    }
    trj<<realtr.size()<<endl;
    for (int j=0; j<realtr.size(); j++) {
        trj<<realtr[j][0]<<"  "<<realtr[j][1]<<"   "<<realtr[j][2]<<endl;
    }
    
}
