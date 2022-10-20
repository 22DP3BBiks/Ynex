#include <fstream>
#include <iostream>
#include "./compiler.h"


int main(int argsc, char *args[]) {
    if (!args[1]) {
        std::cerr << "Expected code file!" << " ";
        return -1;
    }
    std::ifstream code(args[1]);
    if (!args[2]) args[2] = "./main";
    std::ofstream com(args[2], std::ios::out | std::ios::trunc);

    if (!code.is_open()) {
        std::cerr << "Couldn't open code file!" << std::endl;
        return -1;
    }
    if (!com.is_open()) {
        std::cerr << "Couldn't open or make compiled file!" << std::endl;
        return -1;
    }
    std::string data;
    data.assign((std::istreambuf_iterator<char>(code)),
                std::istreambuf_iterator<char>());
    data += '\n';
    int size = 0;
    bool error = false;
    std::string *parserData = lexer(data, error, size);
    if(error){
        std::cerr << parserData[size-1];
    }else{
        parser(parserData);
//        for (size_t i = 0; i < size; i+=2){
//            std::cout << parser[i] << std::endl;
//        }
    }
    delete[] parserData;
    code.close();
    com.close();
    return 0;
}
