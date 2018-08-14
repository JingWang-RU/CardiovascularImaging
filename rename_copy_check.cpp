#include <stdio.h>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <iostream>
using namespace std;
using std::cout;
using std::string;

bool fileExists(const string& filename);
static void copyFile(const string& filefrom, const string& fileto);
int renamefile_from_to(char filefrom[], char fileto[]);
/*
int main(){
     int result;
    //   char oldname[] = "a_out.o";
    //   char newname[] = "a.out";
    //   result = renamefile_from_to(oldname, newname);
    string filefrom = "a.out";
    string fileto = "./jing/goodday.out";
    copyFile(filefrom, fileto);
    return 0;
}
*/
int renamefile_from_to(char filefrom[], char fileto[]){
    int result = rename(filefrom, fileto);
    if (result ==0){
        puts("success rename");
     }else{
        perror("error rename");
     }
     return result;    
}

bool fileExists(const std::string& filename){
  std::fstream file;
  file.open(filename.c_str(), std::ios::in);
  if (file.is_open() == true){
     file.close();
     return true;
  }
  file.close();
  return false;
}

static void copyFile(const std::string& filefrom, const std::string& fileto){
   assert(fileExists(filefrom));
   cout << "filefrom exist \n";   
   std::ifstream in (filefrom.c_str());
   std::ofstream out (fileto.c_str());
 
   out << in.rdbuf();
   out.close();
   in.close();
}

