//
//  echo_overlap_views.cpp
//
//  Created by JingWang on 8/14/18.
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
#include "kmake_directory.cpp"
#include "rename_copy_check.cpp"
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::setw;
using std::map;
using std::vector;
// function: read file which has ID the summary, minimal and maximal number Images in two views
//           rename, copy files 
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
std::map<int,int>read_file(string filename);

int main(){
    std::map<int, int>id_image;
    string file =  "./Result/pla_psa_overlap.txt";
    id_image = read_file(file);
    cout << id_image.size() <<endl;  
 
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
    return 0;
}

void listFile(string &directory, std::map<int, int>& id_images, int vind, bool is_mkdir){
    // id_images:the id, number of images for each id
    DIR *pDIR;
    struct dirent *entry;
    int n = 0;
    std::vector<int> id_vd_slide;
    std::map<int, int>read_id_image;
    int id;
    string file_name;
    string true_name;
    std::ofstream writefile();
    string dir_path ="~\\Documents\\Jcodes\\Echo\\dataset\\photo_dataset\\ph_" + directory +"\\";
    //make directory
    if (is_mkdir){
       make_dir_macos(dir_path);  
    }
    string folder = "../"+directory+"/";
    
    std::set<int> uid;
    if( (pDIR = opendir(folder.c_str()))!= NULL){
        
        while((entry = readdir(pDIR)) != NULL){
            file_name = entry -> d_name;
            if( file_name.find("jpg") != std::string::npos ){
                std::size_t pos = file_name.find('.');
                true_name = file_name.substr(0, pos);
                id_vd_slide = split_space(true_name, '_');
                id = id_vd_slide[0];
                ++read_id_image[id];
                while(read_id_image[id] <= id_imags[id]){
      			string fileto = "dir_path" + "%08d" + id ;
 			copyFile(true_name, dir_path+fileto);
                } 
                ++id_images[id_vd_slide[0]][vind];
            }
        }
        closedir(pDIR);
    }
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

