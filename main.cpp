#include <fstream>
#include <iostream>
#include "./compiler.h"

int main(int count, char *args[]) {
    std::cout << count << " " << args[1] << " " << args[2] << std::endl;
    if (!args[1]) {
        throw std::invalid_argument("Expected code file!");
    }
    std::ifstream code(args[1]);
    if (!code.is_open()) {
        throw std::invalid_argument("Couldn't open code file!");
    }
    if (!args[2]) args[2] = (char*)"./main";
    std::ofstream com(args[2], std::ios::out /*| std::ios::trunc*/);
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
    std::string *parserData = parser(lextedData);
    std::cout << "Parsing completed." << std::endl;
    emitter(com, parserData);
    std::cout << "Emitting completed." << std::endl;
    std::cout << "Compiling completed." << std::endl;
    delete[] lextedData;
    delete[] parserData;
    code.close();
    com.close();
    return  0;
}
