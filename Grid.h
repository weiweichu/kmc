//
//  Grid.h
//  Solvation
//
//  Created by Weiwei Chu on 5/18/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

//Grid is used to
//1. return the grid index for all atoms
//2. determine the atom list for each grid point
//3. get neighbor list for a certain atom

#ifndef Solvation_Grid_h
#define Solvation_Grid_h
#include <vector>
#include "Vector.h"


using namespace std;

typedef vector<Vector> atom;
typedef vector<vector<Vector> > atomlist;

class Grid {
public:
    // box is a vector with size 6
    // ngrid should match each box dimension
    Grid():
    dgrid_(1.0),
    boxl_(1.0, 1.0, 1.0)
    {};
    
    void setgrid(double dgrid, vector<double> box)
    {
        box_=box;
        //cout <<"Grid.h"<< box_[0] <<endl;
        boxl_=Vector(box[1]-box[0],box[3]-box[2],box[5]-box[4]);
        ngrid_=VectorInt(ceil(boxl_[0]/dgrid), ceil(boxl_[1]/dgrid),ceil(boxl_[2]/dgrid));
        cout << ngrid_[0]<<"  "<< ngrid_[1] << "  "<< ngrid_[2] << endl;
        
    }
    //return the 1D grid index for a bead at position(p0,p1,p2)
    int Grid_index(Vector position){
        for(int i=0;i<3;i++){
            position[i] -= box_[i*2];
            while(position[i]<0){
                position[i]+=boxl_[i];}
            while(position[i]>boxl_[i]){
                position[i]-=boxl_[i];}
        }
        int a,b,c;
        a = ceil(position[0]*ngrid_[0]/boxl_[0]);
        b = ceil(position[1]*ngrid_[1]/boxl_[1]);
        c = ceil(position[2]*ngrid_[2]/boxl_[2]);
        return wrap(VectorInt(a,b,c));
    }
    
    //wrap 3D index into 1D
    int wrap(VectorInt a){
        if (a[0]>ngrid_[0]){
            a[0]-=ngrid_[0];}
        if (a[0]<=0){
            a[0]+=ngrid_[0];}
        
        if (a[1]>ngrid_[1]){
            a[1]-=ngrid_[1];}
        if (a[1]<=0){
            a[1]+=ngrid_[1];}
        
        if (a[2]>ngrid_[2]){
            a[2]-=ngrid_[2];}
        if (a[2]<=0){
            a[2]+=ngrid_[2];}
        //cout<<"gridindex  "<<a<<"  "<<b<<"   "<<c<<endl;
        int p;
        p = a[0]-1+ngrid_[0]*(a[1]-1+ngrid_[1]*(a[2]-1));
        return p;
    }
    
    //get the 3D grid index from 1D index
    VectorInt unwrap(int index){
        int x,y,z;
        z = index % ngrid_[1];
        y = ((index - z)/ngrid_[1]) % ngrid_[0];
        x = (((index - z)/ngrid_[1])-y)/ngrid_[0];
        VectorInt gp(x,y,z);
        return gp;
    }
    
    
    //return the distance between any two grid with 1D index a, b with periodic boundary condition
    double disgrid(int a, int b){
        VectorInt au = unwrap(a);
        VectorInt bu = unwrap(b);
        VectorInt c(0,0,0);
        double d;
        //first find their nearest image
        for (int i=0;i<3;i++){
            if (abs(au[i]-bu[i])>ngrid_[i]/2) {
                c[i]=ngrid_[i]-abs(au[i]-bu[i]);
            }
            else{
                c[i]=abs(au[i]-bu[i]);
            }
        }
        d = dgrid_ * sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
        return d;
        
    }
    VectorInt ngrid_;
    
    //return the atom list for each grid point
    
private:
    double dgrid_;
    Vector boxl_;
    vector<double> box_;
    
    
};

#endif
