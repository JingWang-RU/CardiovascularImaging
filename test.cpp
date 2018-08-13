#include <iostream>
#include <map>
#include <vector>
int main(){
  std::map<char, std::vector<int>> my;
//  std::vector<int>my;
  //my.emplace_back(3); 
 my['x'].emplace_back(3);
 my['x'].emplace_back(2);
 my['x'].push_back(1);;
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
  std::cout<< '\n';
  
  return 0;
 }
