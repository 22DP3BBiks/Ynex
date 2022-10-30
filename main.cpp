#include <fstream>
#include <iostream>
#include "./compiler.h"

int main(int _, char *args[]) {
    if (!args[1]) {
        throw std::invalid_argument("Expected code file!");
    }
    std::ifstream code(args[1]);
    if (!args[2]) args[2] = (char*)"./main";
    std::ofstream com(args[2], std::ios::out /*| std::ios::trunc*/);

    if (!code.is_open()) {
        throw std::invalid_argument("Couldn't open code file!");
    }
    if (!com.is_open()) {
        throw std::invalid_argument("Couldn't open or make compiled file!");
    }
    std::string data;
    data.assign((std::istreambuf_iterator<char>(code)),
                std::istreambuf_iterator<char>());
    int SIZE = 0;
    std::string *lextedData = lexer(data, SIZE);
    for (size_t i = 0; i < SIZE; i+=2){
        std::cout << lextedData[i] << std::endl;
    }
    std::cout << "Lexing completed." << std::endl;
    parser(lextedData);
    std::cout << "Parsing completed." << std::endl;
    emitter(com, lextedData);
    std::cout << "Emitting completed." << std::endl;
    std::cout << "Compiling completed." << std::endl;
    delete[] lextedData;
    code.close();
    com.close();
    return  0;
}
