#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <dirent.h>

using namespace std;

void make_dir_macos_char(char char_path[]){
  DIR *pdir;
//  const char char_path[] = "jing";
  string dir_path(char_path);
  pdir = opendir(char_path);
  if (pdir==NULL){
     const int dir_err = system(string("mkdir -p "+dir_path).c_str());
     if (-1==dir_err){
           std::cout << "error";
     }
  }
}

void make_dir_macos(string dir_path){
  const int dir_err = system(string("mkdir -p "+ dir_path).c_str());
  if (-1==dir_err){
    std::cout << "error";
  }
}
int main(){
  string path = "abc";
 // make_dir_macos(path);
   char char_path[] = "jing";
   make_dir_macos_char(char_path);
}
