//
//  TransitionMatrix.cpp
//  TEKMC
//
//  Created by Weiwei Chu on 8/18/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

#include "TransitionMatrix.h"

void TransitionMatrix::calculate(){
    ngrid_=grid_.ngrid_;
    gridt_=ngrid_[0]*ngrid_[1]*ngrid_[2];
    cout << gridt_<<endl;
    //gridt_=100;
    mtrj.resize(nion_,nframe_);
   // mt_=MatrixXd::Zero(gridt_, gridt_);
    MatrixXf mtt(gridt_,gridt_);
    for (int ia = 0; ia<nion_; ia++) {
        for (int iff=0; iff<nframe_; iff++) {
			int a=grid_.Grid_index(Vector(iontrj_[ia][iff][0],iontrj_[ia][iff][1],iontrj_[ia][iff][2]));
			//cout << a << endl;
            mtrj(ia,iff)=a;
        }
    }
    //cout<< mtrj << endl;

    
    ////for each row of mtrj, calculate a mti, then do normalization for each colomn of mti
    ////sum up all mti and take the mean, this is mtt
    ////make mtt symmetric matrix, that is aij=aji to apply the detailed balance
    vector<MatrixXf> mtc;
    
    
    ////cout<< mtd<<endl;
    MatrixXf mti(gridt_,gridt_);
    int si=0;
    MatrixXd mtd= MatrixXd::Zero(gridt_,gridt_);
    for (int i=0; i<mtrj.rows(); i++) {		
        for (int j=0; j<mtrj.cols()-1; j++) {
            mtd(mtrj(i,j),mtrj(i,j+1))++;
        }
        }
       //// cout<<mtd<<endl;
        ////sum up every colomn and each element shoud devided by the sum of the colomn
        MatrixXd vs(1,gridt_);
        vs = mtd.colwise().sum();
       // cout << vs << endl;
        //cout << mtd.rows()<<"  "<<mtd.cols()<<endl;
        for (int i =0; i < mtd.rows(); i++) {
			for (int j=0; j< mtd.cols(); j++) {
				if(vs(0,j) != 0){
				mti(i,j) = mtd(i,j)/vs(0,j);}
				else{
					mti(i,j)=mtd(i,j);}
			}		
		}
		//cout << mti<<endl;
   
    mt_=(mti+mti.transpose())/2;
    //cout << mt_ << endl;
}

int TransitionMatrix::move(int a){
    double r = rand()/RAND_MAX;
    int i = 1;
    while (mt_.block(0, a, i, 1).sum()< r) {
        i++;
    }
    return i;
}

vector<Vector> TransitionMatrix::maptorealposition(vector<int> gm){
    vector<Vector> rtrj;
    for (int i=0; i<gm.size(); i++) {
        rtrj.push_back(grid_.unwrap(gm[i]));
    }
    return rtrj;
}

double TransitionMatrix::displacement(int a, int b){
    double d;
    d=grid_.disgrid(a,b);
    return d;
}






