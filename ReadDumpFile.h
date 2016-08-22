//
//  ReadDumpFile.h
//  TEKMC
//
//  Created by Weiwei Chu on 8/17/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

#ifndef __TEKMC__ReadDumpFile__
#define __TEKMC__ReadDumpFile__

//get trajectory for all the ions
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Vector.h"
#include <algorithm>
#include "Eigen/Dense"


using namespace Eigen;
using namespace std;
typedef vector<string> sentence;
typedef string::size_type s_type;
typedef vector<Vector> atom;
typedef vector<vector<Vector> > trj;

class ReadDumpFile{
public:
    ReadDumpFile(char* fname,int nframe)
    :fname_(fname),
    nframe_(nframe),
    nion(0)
    {
        trajectory();
        //cout << iontrj[0][0][0] <<"  " <<"dumpfile"<< endl;
    }
    //get the trajectory for all the ions
    void trajectory();
    sentence split(const string& s);
    vector<double> box;
    trj iontrj;
    //number of ions
    long nion;
    //number of frame
    int nframe_;
    
private:
    char* fname_;
};

#endif
