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
    while(!check(data, index, "Token.EOF")){
        if(check(data, index, "Token.COMMENT")) continue;
        else if(check(data, index, "Token.CLOSEBRACE")) file << "}" << std::endl;
        else{
            throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
        }
    }
    file << "return 0;" << std::endl;
    file << "}" << std::endl;
}