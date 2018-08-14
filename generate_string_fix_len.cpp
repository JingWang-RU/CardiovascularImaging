#include <iostream>

using namespace::std;
using std::string;
using std::to_string;
using std::endl;

string generate_string_fix_len(int char_front, int char_back, int fix_len){
// generate a string with fixed length fix_len; 
//  char_front 000...0 char_end 
    string result = "";
    result += to_string(char_front);
    string strback(to_string(char_back));
    if ( result.length()+strback.length() > fix_len ){
        cout << " out of range " << endl;
        return "";
    }
    result.insert( result.length(), fix_len - result.length() - strback.length(), '0' ); 
    result += strback; 
    return result;
}

