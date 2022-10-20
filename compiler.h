#ifndef YNEX_COMPILER_H
#define YNEX_COMPILER_H
#include <iostream>

std::string *lexer(std::string data,bool &error, int &size);
void parser(std::string *data);

#endif //YNEX_COMPILER_H
