#ifndef YNEX_COMPILER_H
#define YNEX_COMPILER_H
#include <iostream>
bool check(std::string *data, int &index, std::string type);
std::string *lexer(std::string data, int &size);
std::string *parser(std::string *data);
void emitter(std::ofstream &file, std::string *data);

#endif //YNEX_COMPILER_H
