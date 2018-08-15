//
//  512*256 image generation
//
//  Created by JingWang on 8/15/18.
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
//#include <boost/filesystem.hpp>
#include "resize_image_opencv.cpp"
#include "make_directory.cpp"
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

void listFile(string&, string, bool, string);
std::vector<int> split_space(const string&, char);
bool isequal(int, int);
std::map<int,int>read_file(string filename);

int main(){
 
    std::vector<string> views = {"PLA", "PSA"};//,"A4C","A2C","A3C","SSX","SCX"};
    std::vector<string>::iterator it;
    bool is_mkdir = true; 
    string targetimage = "512256.png";
    for (it = views.begin(); it!=views.end(); ++it){
        string dir_path ="../../symdataset256/sym" + *it +"256/";
//	cout << "dr path: "<<dir_path<< endl;
        listFile(*it, dir_path, is_mkdir, targetimage);
    }
    //cout << "well done !" << "\n";
    return 0;
}

void listFile( string &directory, string dir_path, bool is_mkdir, string targetimage ){
    // id_images:the id, number of images for each id
    DIR *pDIR;
    struct dirent *entry;
    std::vector<int> id_vd_slide;
    std::map<int, int> read_id_image;
    int id;
    string file_name;
    string true_name;
    //make directory
    if (is_mkdir){
       make_dir_macos(dir_path);  
       cout << "directory is made " << endl;
    }
    string folder = "../../symdataset/sym"+directory+"/";//"~/Documents/Jcodes/Echo/dataset/" + directory + "/";
    if( (pDIR = opendir(folder.c_str()))!= NULL){
        //cout <<"good job"<<endl;    
        while((entry = readdir(pDIR)) != NULL){
            //cout << "hello" << endl;
            file_name = entry -> d_name;
            if( file_name.find("jpg") != std::string::npos ){
                std::size_t pos = file_name.find('.');
                true_name = file_name.substr(0, pos);
                resizeImage(folder+file_name, targetimage, dir_path+true_name+".png");
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
    std::ifstream readfile; std::vector<int> tokens;
    std::map<int, int>id_image;
   
    string line; 
    readfile.open( filename );
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

