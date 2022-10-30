#include <fstream>
#include <iostream>
#include "compiler.h"
void emitter(std::ofstream &file, std::string *data){
    int index=-2;
    while(!check(data, index, "Token.EOF")){
        if(check(data, index, "Token.IN") || check(data, index, "Token.OUT")){
            file << "#include <iostream>" << std::endl;
            break;
        }else{
            index+=2;
        }
    }
    file << "int main(){" << std::endl;
    index=-2;
//    while(!check(data, index, "Token.EOF")){
//        if(check(data, index, "Token.COMMENT")) continue;
//        if(check(data, index, "Token.CLOSEBRACE")) file << "}" << std::endl;
//    }
    file << "return 0;" << std::endl;
    file << "}" << std::endl;
}