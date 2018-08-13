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

// function: files in a directory with names like 'ID_NoVideos_NoSlide'
//           count the number of ID, the vidoes per ID, and frames per video
// g++ -std=c++11 filestats.cpp -o filestats

void listFile(string&);
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
    cout<<std::setw(10)<<"view" <<std::setw(10)<<"numIds "<<std::setw(12)<<"numVideos"<<std::setw(12)<<"numImages "<<setw(14)<<"avg/min/max video:id"<< setw(14)<<"images:id"<<setw(16)<<"images:video"<<endl;
    std::vector<string> views = {"PLA","PSA","A4C","A2C","A3C","SSX","SCX"};
    std::vector<string>::iterator it;
    for (it = views.begin(); it!=views.end(); ++it){
        cout<<setw(10)<<*it;
        listFile(*it);
        //cout<<endl;
    }
    
   // string file = "A2C";
   // listFile(file);
   
    return 0;
}

void listFile(string &directory){
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
    
    std::ofstream writefile( "./Result/"+directory+"_brief_stats.txt");

    writefile << setw(6)<< "id" << setw(12) << "numVideos" <<setw(12)<< "numImages"<<setw(21)<<"VideoID : numImage" << endl;
    
    for(it = uid.begin(); it != uid.end(); ++it){
        writefile << setw(6) << *it << " ";
        while( sort_id[++i] == *it && i < id.size() ){
            if ( video_image.find(sort_video[i]) == video_image.end() ){
                video_image.emplace(sort_video[i], 1);
            } else {
                ++video_image[sort_video[i]];
            }
            ++sum_img;
        }
       
        writefile << setw(12) << video_image.size() <<setw(12)<< sum_img <<setw(12);
        sum_video += video_image.size();
        for (std::map<int,int>::iterator iv = video_image.begin(); iv!=video_image.end(); ++iv){
            writefile << iv->first << " : " << iv->second << ",  ";
            if (iv->second>max_image_video) max_image_video = iv->second;
            if (iv->second<min_image_video) min_image_video = iv->second;
        }
        writefile << endl;
        if(video_image.size()>max_video) max_video = video_image.size();
        if(video_image.size()<min_video) min_video = video_image.size();
        if(sum_img>max_image) max_image = sum_img;
        if(sum_img<min_image) min_image = sum_img;
        video_image.clear();
        sum_img=0;
    }
    int len = 28;
    int len2 = 14;
    
     writefile<<setw(len)<<"num id: "<< setw(len2)<< uid.size()<<endl;
    writefile<<setw(len)<<"num video: "<< setw(len2)<<sum_video<<endl;
    writefile<<setw(len)<<"num images: "<<setw(len2)<< id.size()<<endl;
    writefile<<setw(len)<<"avg/min/max video/id: "<< setw(4)<<std::setprecision (4) << (double(sum_video)/uid.size()) <<setw(1)<<"/" << setw(4)<<min_video<<setw(1)<<"/" << setw(4)<<max_video << endl;
    writefile<<setw(len)<<"avg/min/max images/id: "<< setw(4)<<std::setprecision (4) << double(slides.size())/uid.size()<< setw(1)<<"/" <<setw(4)<<min_image<<setw(1)<<"/"<<setw(4)<<max_image << endl;
    writefile<<setw(len)<<"avg/min/max images/video: "<< setw(4)<<std::setprecision (4) << double(slides.size())/sum_video<< setw(1)<<"/" <<setw(4)<<min_image_video << setw(1)<<"/"<< setw(4)<<max_image_video << endl;
    int len3 = 10;
    cout<<setw(len3)<< uid.size();
    cout<<setw(len3)<<sum_video;
    cout<<setw(len3)<<id.size();
    cout<<setw(len3)<<std::setprecision (4) << (double(sum_video)/uid.size()) <<setw(1)<<"/" << setw(4)<<min_video<<setw(1)<<"/" << setw(4)<<max_video;
    cout<<setw(len3)<<std::setprecision (4) << double(slides.size())/uid.size()<< setw(1)<<"/" <<setw(4)<<min_image<<setw(1)<<"/"<<setw(4)<<max_image ;
    cout<<setw(len3)<<std::setprecision (4) << double(slides.size())/sum_video<< setw(1)<<"/" <<setw(4)<<min_image_video << setw(1)<<"/"<< setw(4)<<max_image_video << endl;
    writefile.close();
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

