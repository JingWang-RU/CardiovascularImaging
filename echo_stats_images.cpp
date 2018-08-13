//
//  echo_stats_images.cpp
//  
//
//  Created by JingWang on 8/13/18.
//
//
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include<sstream>
#include<dirent.h>
#include<iterator>
#include<iomanip>
#include<numeric>
#include<set>
#include<map>
#include<algorithm>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::setw;
using std::map;
using std::vector;

// function: output statistical result
//           files in a directory with names like 'ID_NoVideos_NoSlide'
//        printf:    Id numImages per View   and sum the number of images
// e.g ID PLA PSA A4C A2C A3C SSX SCX sum
//      1 127  128  87  0  87  63  14  506
// g++ -std=c++11 filestats.cpp -o filestats

void listFile(string&, std::map<int, std::vector<int>>&, int);
std::vector<int> split_dash(const string&, char);
bool isequal(int, int);
template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {
    
    // initialize original index locations
    std::vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);
    
    // sort indexes based on comparing values in v
    std::sort(idx.begin(), idx.end(),[&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
    
    return idx;
}
int main(){
    //cout<<std::setw(10)<<"view" <<std::setw(10)<<"numIds "<<std::setw(12)<<"numVideos"<<std::setw(12)<<"numImages "<<setw(14)<<"avg/min/max video:id"<< setw(14)<<"images:id"<<setw(16)<<"images:video"<<endl;
    std::vector<string> views = {"PLA","PSA","A4C","A2C","A3C","SSX","SCX"};
    std::vector<string>::iterator it;
    std::map<int, std::vector<int>> id_images;//(107,std::vector<int>(7,0));
    std::vector<int> zero_v (views.size(),0);
    for(int i = 0; i<107; ++i){
        id_images[i+1] = zero_v;
    }
    cout <<setw(10)<<"Id"<<setw(20)<<"numImages per view"<< setw(20) <<"sum" <<endl;
    int vind = 0;
    cout <<setw(5)<<"Id";
    for (it = views.begin(); it!=views.end(); ++it){
        cout<<setw(10)<<*it;
        listFile(*it, id_images, vind);
        ++vind;
        //cout<<endl;
    }
    cout <<setw(20)<<"sum"<<endl;
    int id_v = 0;
    for( auto&t : id_images ) {
        cout << setw(5)<<t.first ;
        for( auto &x  : t.second ){
            cout << setw(10) << x;
            id_v+=x;
        }
        cout << setw(5)<<id_v<<endl;
        id_v = 0;
    }
    
    return 0;
}

void listFile(string &directory, std::map<int, std::vector<int>>& id_images, int vind){
    DIR *pDIR;
    struct dirent *entry;
    int n = 0;
    std::vector<int> id_vd_slide;
    std::vector<int> id;
    std::vector<int> video;
    std::vector<int> slides;
    string file_name;
    string true_name;
    //
    string folder = "../"+directory+"/";
    
    std::set<int> uid;
    if( (pDIR = opendir(folder.c_str()))!= NULL){
        
        while((entry = readdir(pDIR)) != NULL){
            file_name = entry -> d_name;
            if( file_name.find("jpg") != std::string::npos ){
                std::size_t pos = file_name.find('.');
                true_name = file_name.substr(0, pos);
                
                id_vd_slide = split_dash(true_name, '_');
                ++id_images[id_vd_slide[0]][vind];
            }
        }
        closedir(pDIR);
    }
    
   }

std::vector<int> split_dash(const string &s, char delim) {
    stringstream ss(s);
    string item;
    std::vector<int> tokens;
    while (getline(ss, item, delim)) {
        
        tokens.push_back(std::stoi(item));
    }
    return tokens;
}

bool isequal(int i, int j){
    return (i=j);
}

