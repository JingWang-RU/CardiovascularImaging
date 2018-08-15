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
//#include <boost/filesystem.hpp>
#include "make_directory.cpp"
#include "rename_copy_check.cpp"
#include "generate_string_fix_len.cpp"
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

void listFile(string&, std::map<int, int>&, string, int, bool);
std::vector<int> split_space(const string&, char);
bool isequal(int, int);
std::map<int,int>read_file(string filename);

int main(){
    std::map<int, int> id_image;
    string file =  "./Result/pla_psa_overlap.txt";
    id_image = read_file(file);
//    cout << id_image.size() << endl;  
 
    std::vector<string> views = {"PLA", "PSA"};//,"A4C","A2C","A3C","SSX","SCX"};
    std::vector<string>::iterator it;
    bool is_mkdir = false; 
    int fix_len = 4;
    for (it = views.begin(); it!=views.end(); ++it){
        string dir_path ="~/Documents/Jcodes/Echo/symdataset/sym" + *it +"/";
//	cout << "dr path: "<<dir_path<< endl;
        listFile(*it, id_image, dir_path, fix_len, is_mkdir);
    }
    cout << "well done !" << "\n";
    return 0;
}

void listFile( string &directory, std::map<int, int>& id_image, string dir_path, int fix_len, bool is_mkdir ){
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
    string true_path = "../../symdataset/sym"+directory+"/";//"~/Documents/Jcodes/Echo/dataset/" + directory + "/";
    string folder = "../"+directory+"/";
    cout << "folder : "<< folder <<endl;
    std::set<int> uid;
    string fileto;
    if( (pDIR = opendir(folder.c_str()))!= NULL){
        cout <<"good job"<<endl;    
        while((entry = readdir(pDIR)) != NULL){
            cout << "hello" << endl;
            file_name = entry -> d_name;
            if( file_name.find("jpg") != std::string::npos ){
                std::size_t pos = file_name.find('.');
                true_name = file_name.substr(0, pos);
                id_vd_slide = split_space(true_name, '_');
                id = id_vd_slide[0];
                ++read_id_image[id];
               if( read_id_image[id] <=  id_image[id]){
      		    fileto =  generate_string_fix_len(id, read_id_image[id], fix_len);  
 		    cout << folder+file_name<<endl;
                    cout << dir_path+fileto+".jpg"<<endl;
                    copyFile(folder+file_name, (true_path + fileto + ".jpg").c_str());
                } 
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

