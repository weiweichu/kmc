//
//  ReadDumpFile.cpp
//  TEKMC
//
//  Created by Weiwei Chu on 8/17/16.
//  Copyright (c) 2016 Weiwei Chu. All rights reserved.
//

#include "ReadDumpFile.h"

sentence ReadDumpFile::split(const string &s){
    sentence a;
    s_type i=0;
    while(i!=s.size()) {
        while (i!=s.size() && isspace(s[i])) {
            ++i;
        }
        
        s_type j=i;
        while (j!=s.size() && !isspace(s[j])) {
            ++j;
        }
        
        if(i!=j) {
            a.push_back(s.substr(i,j-i));
            i = j;
        }
    }
    return a;
}

void ReadDumpFile::trajectory(){
   
    string line;
    sentence a;
    double b;
    int t;
    //the smallest id of ions
    int ib=0;  
    int natom=0;
    const string ts("TIMESTEP");
    const string bx("BOX");
    const string as("ATOMS");
    const string na("NUMBER");
    vector<int> idlist;
    int id=0;
    ifstream in(fname_);
    if (in.is_open()){
        cout << "file is open" << endl;
    }
    //read the first frame
    while (getline(in,line)) {
        a=split(line);
       // cout << line << "  "<<a.size()<<"  "<<a[0]<<endl;
   
        if ((a.size()==4) && (!a[1].compare(na))) {
			//cout << line <<endl;
            getline(in,line);
            a=split(line);
            istringstream(a[0])>>natom;
           // cout << natom <<" natom"<< endl;
        }
        else if ((a.size()==6) && (!a[1].compare(bx))) {
            getline(in,line);
            a=split(line);
            istringstream(a[0])>>b;
            box.push_back(b);
            istringstream(a[1])>>b;
            box.push_back(b);
            getline(in,line);
            a=split(line);
            istringstream(a[0])>>b;
            box.push_back(b);
            istringstream(a[1])>>b;
            box.push_back(b);
            getline(in,line);
            a=split(line);
            istringstream(a[0])>>b;
            box.push_back(b);
            istringstream(a[1])>>b;
            box.push_back(b);
           //cout << box[0] << "  box[0]"<< endl;
            
        }
        else if((a.size()==8) && (!a[1].compare(as))){
            for (int i=0; i<natom; i++) {
                getline(in,line);
                a=split(line);
                istringstream(a[2])>>t;
                if (t==18){
                    istringstream(a[0])>>id;
                    idlist.push_back(id);
                    
                }
            }
            sort(idlist.begin(), idlist.end());
			ib=idlist[0];
			nion = idlist.size();
			//cout << nion << endl;
			break;
        }
    }
   // cout << nion << endl;
    vector<Vector> mv;
    mv.resize(nframe_,Vector(0,0,0));
    iontrj.resize(nion,mv);
    //cout<<iontrj.size()<<endl;
	int nf=-1;
    while (getline(in, line)) {
        a=split(line);
        if ((a.size()==4) && (!a[1].compare(na))){
			nf++;
			if (nf==nframe_){
				break;}
			}
        if(a.size()>5){
            istringstream(a[2])>>t;
            if (t==18) {
                istringstream(a[0])>>id;
                double x,y,z;
                istringstream(a[3])>>x;
                istringstream(a[4])>>y;
                istringstream(a[5])>>z;
                //cout << x <<"  "<<y<<"  "<<z<<endl;
                //cout << id-ib << endl;
                iontrj[id-ib][nf][0]=x;
                iontrj[id-ib][nf][1]=y;
                iontrj[id-ib][nf][2]=z;
                
            }
       // cout << iontrj[1][nf][0] << endl;
        }
    }
   // cout << iontrj.size()<<endl;
}
