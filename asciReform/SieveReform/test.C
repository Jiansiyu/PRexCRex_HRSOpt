#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

inline std::string getFileName(const std::string & s){
	char sep = '/';
#ifdef _WIN32
        sep = '\\';
#endif
	size_t i = s.rfind(sep, s.length());
	if(i != std::string::npos){
	    return(s.substr(i+1, s.length()-i));
	}  
        return("");
}

inline std::string getFilePath(const std::string & s){
	char sep = '/';
#ifdef _WIN32
        sep = '\\';
#endif
	size_t i = s.rfind(sep, s.length());
	if(i != std::string::npos){
	    return(s.substr(0, i+1));
	}  
        return("");
}

void test(const std::string & s){

std::cout<<getFileName(s).c_str()<<std::endl;
std::cout<<getFilePath(s).c_str()<<std::endl;
}