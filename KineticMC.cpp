//
//  KineticMC.cpp
//  TEKMC
//
//  Created by Weiwei Chu on 8/19/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

#include "KineticMC.h"
void KineticMC::run(char* fname,double dgrid,int nstep,int nframe){
    TransitionMatrix tmatrix(fname,dgrid,nframe);
    tmatrix.calculate();
    int r=int(rand()/RAND_MAX)*tmatrix.gridt_;
    int rn;
    for (int i=0; i<nstep; i++) {
        tr_.push_back(r);
        rn=tmatrix.move(r);
        msd_.push_back(tmatrix.displacement(rn, r)*tmatrix.displacement(rn, r));
        r=rn;
        
    }
    realtr_ = tmatrix.maptorealposition(tr_);
    
}
