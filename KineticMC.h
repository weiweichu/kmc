//
//  KineticMC.h
//  TEKMC
//
//  Created by Weiwei Chu on 8/19/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

#ifndef __TEKMC__KineticMC__
#define __TEKMC__KineticMC__

#include <stdio.h>
#include "TransitionMatrix.h"

class KineticMC{
public:
    KineticMC(){};
    //~KineticMC(){};
    void run(char* fname,double dgrid, int nstep, int nframe);
    vector<int> tr_;
    vector<Vector> realtr_;
    vector<double> msd_;
    
private:

};

#endif /* defined(__TEKMC__KineticMC__) */
