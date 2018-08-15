#include <iostream>
#include <map>
#include <vector>
#include "rename_copy_check.cpp"
#include <string>
#include <sstream>
#include <cstdlib>
#include "generate_string_fix_len.cpp"
#include <dirent.h>
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace::std;
using std::string;
using std::vector;
using std::to_string;
using std::endl;

int main(){

 DIR *pDIR;
 struct dirent *entry;
 int n = 0; 
 string folder = "../PLA/";
 if ((pDIR = opendir(folder.c_str()))!=NULL){
     cout <<"hi:wq";
    while((entry = readdir(pDIR))!=NULL){
       cout << entry->d_name <<endl;
    }    
 }
    //   string result = generate_string_fix_len(13, 223,4);
//   if(result.empty()) cout <<"error"<<endl;
//    cout << result << endl; 
/*    string orgs = "1_2_3.jpg";
    std::stringstream ss(orgs);
   // vector<string> token;
    string item;
    getline(ss, item, '_'); 
   // while(getline(ss, item, "_")){
//      token.append(item);
   // }
    string tostr(item);
    int index = 7;
    string ind(std::to_string(index));
    int len_zero = 6 - item.length()-ind.length(); 
    tostr.insert(item.length(), len_zero, '0');
    tostr+=(ind); 
    cout << tostr << std::endl;
//   std::vector<int> a(2,0);
//   std::map<char, std::vector<int>> my;
//   string filefrom = "a.out";
//   string fileto = "./jing/goodnight.out"; 
//   copyFile(filefrom, fileto); 

//  std::vector<int>my;
  //my.emplace_back(3);
//    for(int i = 0; i<10; ++i){
//        my['x']=a;
//        my['x']=a;
//    }
  //  my['x'][0]=3;//.emplace_back(3);
  //  my['x'][1]=2;
 //my['x'].emplace_back(2);
 //my['x'].push_back(1);;
 // std::map<char,int> my;
//  ++my['x'];
//  ++my['y'];
//  ++my['x'];
  // my['x'].push_back(2);
//  my.emplace('x',100);
//  my.emplace('y',200);
//  my.emplace('z',300);
//  my.emplace('x',432);
  
  std::cout<<"my contains: ";
  for(auto &x : my){
     std::cout<< "[" <<x.first<< ':' << x.second.size()<< ']';
     std::cout<<"in the vector: ";
     if (x.second.size()>0){
        for (auto &y: x.second) {
              std::cout << y<<'-';
           }
      }
   }
    my['x'][0]=3;
    my['x'][1]=2;
    for(auto &x:my){
        if (x.second.size()>0){
        for (auto &y: x.second) {
            std::cout << y<<'-';
        }
    }    }
  std::cout<< '\n';
  */
  return 0;
 }
