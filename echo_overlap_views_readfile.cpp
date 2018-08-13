//
//  echo_overlap_views.cpp
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
#include <boost/filesystem.hpp>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::setw;
using std::map;
using std::vector;
// function: write in a file statistical result
//           files in a directory with names like 'ID_NoVideos_NoSlide'
//        printf:    Id numImages per View   and sum the number of images
// e.g        1  127  128  127  128
// numPla:100 numPsa: 105 pla_psa: 99 min: 11326 max: 29781
// g++ -std=c++11 filestats.cpp -o filestats

void listFile(string&, std::map<int, std::vector<int>>&, int);
std::vector<int> split_space(const string&, char);
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
std::map<int,int>read_file(string filename){
     std::ifstream readfile;
    std::vector<int> tokens;
    std::map<int, int>id_image;
    string line; 
    readfile.open( filename);
    int count = 0;
    while( getline(readfile, line)){
      std::stringstream linestream(line); 
      int value;
            while(linestream >> value){
         tokens.push_back(value);
         ++count;
      }
      id_image.emplace(tokens[0], tokens[3]);
    /*  for(auto &x:id_image){
        cout<<" [" << x.first << ':' << x.second << ']'<<'\n';
      }*/
     tokens.clear();
    }
    readfile.close();
    return id_image; 
}
int main(){
    //cout<<std::setw(10)<<"view" <<std::setw(10)<<"numIds "<<std::setw(12)<<"numVideos"<<std::setw(12)<<"numImages "<<setw(14)<<"avg/min/max video:id"<< setw(14)<<"images:id"<<setw(16)<<"images:video"<<endl;
    std::map<int, int>id_image;
    string file =  "./Result/pla_psa_overlap.txt";
    id_image = read_file(file);
    cout << id_image.size() <<endl;  
/* 
    std::vector<string> views = {"PLA","PSA"};//,"A4C","A2C","A3C","SSX","SCX"};
    std::vector<string>::iterator it;
    std::map<int, std::vector<int>> id_images;//(107,std::vector<int>(7,0));
    std::vector<int> zero_v (views.size(),0);
    for(int i = 0; i<107; ++i){
        id_images[i+1] = zero_v;
    }
    int vind = 0;
    cout <<setw(5)<<"Id";
    for (it = views.begin(); it!=views.end(); ++it){
        listFile(*it, id_images, vind);
        ++vind;
        //cout<<endl;
    }
    vector<int> temp;
    int id_v = 0;
    for( auto&it : id_images ) {
        
        //cout << setw(5)<<t.first ;
        temp = it.second;
        if (temp[0]!=0 && temp[1] !=0){
            writefile << setw(5)<<it.first<< setw(10)<<temp[0] <<setw(10)<<temp[1] <<setw(10)\
                <<std::min(temp[0], temp[1])<<setw(10) << std::max(temp[0], temp[1])<<endl;
        }
    }
    //cout<<"numPla: "<<pla_num<<" numPsa: "<<psa_num <<" pla_psa "<< pla_psa << " min: "<< min_num<<" max: "<<max_num<<endl;
    writefile.close();
 */   return 0;
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
    std::ofstream writefile();
    const char dir_path[]="~\\Documents\\Jcodes\\Echo\\dataset\\code_dataset\\" + directory +"\\";
    DIR * newdataDir = opendir(dir_path.c_str());

    boost::filesystem::path dir(dir_path);
    if (dir){
      closedir(dir);
    }else if (ENOENT ==errno) {
//    if(boost::filesystem::create_directory(dir)){     
      boost::filesystem::create_directory(dir); 
      cout<<"sucess" <<'\n';
    } 
}
/*
    string folder = "../"+directory+"/";
    
    std::set<int> uid;
    if( (pDIR = opendir(folder.c_str()))!= NULL){
        
        while((entry = readdir(pDIR)) != NULL){
            file_name = entry -> d_name;
            if( file_name.find("jpg") != std::string::npos ){
                std::size_t pos = file_name.find('.');
                true_name = file_name.substr(0, pos);
                
                id_vd_slide = split_space(true_name, '_');
                ++id_images[id_vd_slide[0]][vind];
            }
        }
        closedir(pDIR);
    }*/
}

std::vector<int> split_space(const string &s, char delim) {
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

