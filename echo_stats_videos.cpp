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

// function: output statistical result
//           files in a directory with names like 'ID_NoVideos_NoSlide'
//        printf:    Id numViews per View   and sum the number of videos
// e.g ID PLA PSA A4C A2C A3C SSX SCX sum
//      1 4    3   2  0    2   2  1  14
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
    std::map<int, std::vector<int>> id_videos;//(107,std::vector<int>(7,0));
    std::vector<int> zero_v (views.size(),0);
    for(int i = 0; i<107; ++i){
        id_videos[i+1] = zero_v;
    }
    cout <<setw(10)<<"Id"<<setw(20)<<"numVideos per view"<<endl;
    int vind = 0;
    cout <<setw(5)<<"Id";
    for (it = views.begin(); it!=views.end(); ++it){
        cout<<setw(10)<<*it;
        listFile(*it, id_videos, vind);
        ++vind;
        //cout<<endl;
    }
    cout <<endl;
    int id_v = 0;
    for( auto&t : id_videos ) {
        cout << setw(5)<<t.first ;
        for( auto &x  : t.second ){
            cout << setw(10) << x;
            id_v+=x;
        }
        cout << setw(5)<<id_v<<endl;
        id_v = 0;
    }
   // string file = "A2C";
   // listFile(file);
   
    return 0;
}

void listFile(string &directory, std::map<int, std::vector<int>>& id_videos, int vind){
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
                id.push_back(id_vd_slide[0]);
                uid.emplace(id_vd_slide[0]);
                video.push_back(id_vd_slide[1]);
                slides.push_back(id_vd_slide[2]);
            }
        }
        closedir(pDIR);
    }
    
    std::set<int>::iterator it;
    std::vector<int> sort_id;
    int sum_video = 0;
    std::vector<int> sort_video;
    
    for (int i:sort_indexes(id)){
        sort_video.push_back(video[i]);
        sort_id.push_back(id[i]);
    }
    std::map<int, int>video_image;
    int i = -1;
    int sum_img=0;
    int max_video=0;
    int min_video = 1e4;
    int max_image = 0;
    int min_image = 1e4;
    int max_image_video = 0;
    int min_image_video = 1e4;
    //Result/
    
    for(it = uid.begin(); it != uid.end(); ++it){
        while( sort_id[++i] == *it && i < id.size() ){
            if ( video_image.find(sort_video[i]) == video_image.end() ){
                video_image.emplace(sort_video[i], 1);
            } else {
                ++video_image[sort_video[i]];
            }
            ++sum_img;
        }
       
        sum_video += video_image.size();
        id_videos[*it].at(vind) = video_image.size();
        for (std::map<int,int>::iterator iv = video_image.begin(); iv!=video_image.end(); ++iv){
            if (iv->second>max_image_video) max_image_video = iv->second;
            if (iv->second<min_image_video) min_image_video = iv->second;
        }
        if(video_image.size()>max_video) max_video = video_image.size();
        if(video_image.size()<min_video) min_video = video_image.size();
        if(sum_img>max_image) max_image = sum_img;
        if(sum_img<min_image) min_image = sum_img;
        video_image.clear();
        sum_img=0;
        //id_videos[*it].emplace_back(sum_video);
        
    }
    int len = 28;
    int len2 = 14;
    
    int len3 = 10;
    /*cout<<setw(len3)<< uid.size();
    cout<<setw(len3)<<sum_video;
    cout<<setw(len3)<<id.size();
    cout<<setw(len3)<<std::setprecision (4) << (double(sum_video)/uid.size()) <<setw(1)<<"/" << setw(4)<<min_video<<setw(1)<<"/" << setw(4)<<max_video;
    cout<<setw(len3)<<std::setprecision (4) << double(slides.size())/uid.size()<< setw(1)<<"/" <<setw(4)<<min_image<<setw(1)<<"/"<<setw(4)<<max_image ;
    cout<<setw(len3)<<std::setprecision (4) << double(slides.size())/sum_video<< setw(1)<<"/" <<setw(4)<<min_image_video << setw(1)<<"/"<< setw(4)<<max_image_video << endl;
     */
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

