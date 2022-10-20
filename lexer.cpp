#include <iostream>
#include "./compiler.h"

void resize(std::string *&arr, int &size, int amount=1){
    if(amount>1){
        size+=amount;
    }else{
        ++size;
    }
    std::string *temp = new std::string[size];
    for (size_t i = 0; i<size-amount;++i){
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
}

std::string *lexer(std::string data,bool &error, int &size){
    std::string *lexData = new std::string[size];
    for(int currCharPosition = 0; currCharPosition<data.length();++currCharPosition) {
        char l = data.at(currCharPosition);
        //std::cout << l << std::endl;
        if (l == ' ' || l == '\n' || l == '\r' || l == '\t') continue;
        if (l == '-') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.MINUS";
            lexData[size-1] = "-";
        } else if (l == '+') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.PLUS";
            lexData[size-1] = "+";
        } else if (l == '*') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.MULTIPLY";
            lexData[size-1] = "*";
        } else if (l == ';') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.ENDLINE";
            lexData[size-1] = ";";
        } else if (l == '(') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.OPENPARENT";
            lexData[size-1] = "(";
        } else if (l == ')') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.CLOSEPARENT";
            lexData[size-1] = ")";
        } else if (l == '{') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.OPENBREACE";
            lexData[size-1] = "{";
        } else if (l == '}') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.CLOSEBRACE";
            lexData[size-1] = "}";
        } else if (l == '[') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.OPENBRACKET";
            lexData[size-1] = "[";
        } else if (l == ']') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.CLOSEBRACKET";
            lexData[size-1] = "]";
        } else if (l == '/') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '/') {
                std::string comment = "//";
                ++currCharPosition;
                while (data.length() > currCharPosition && data.at(currCharPosition + 1) != '\n') {
                    comment+=data.at(currCharPosition);
                    ++currCharPosition;
                }
                resize(lexData, size, 2);
                lexData[size-2] = "Token.COMMENT";
                lexData[size-1] = comment;
            } else {
                resize(lexData, size, 2);
                lexData[size-2] = "Token.DIVIDE";
                lexData[size-1] = "/";
            }
        } else if (l == '#') {
            resize(lexData, size, 2);
            lexData[size-2] = "Token.LENGTH";
            lexData[size-1] = "#";
        } else if (l == "'"[0] || l == '"') {
            std::string string = "\"";
            ++currCharPosition;
            while (data.at(currCharPosition) != "'"[0] && data.at(currCharPosition) != '"') {
                if (data.length() == currCharPosition + 1) {
                    error = true;
                    resize(lexData, size);
                    lexData[size-1] = "Missing end char \' or \" at: " + std::to_string(currCharPosition + 1);
                    return lexData;
                }
                string+=data.at(currCharPosition);
                ++currCharPosition;
            }
            string+="\"";
            resize(lexData, size, 2);
            lexData[size-2] = "Token.STRING";
            lexData[size-1] = string;
        } else if (l == '=') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '=') {//==
                resize(lexData, size, 2);
                lexData[size-2] = "Token.EQU";
                lexData[size-1] = "==";
                ++currCharPosition;
            } else {
                resize(lexData, size, 2);
                lexData[size-2] = "Token.SET";
                lexData[size-1] = "=";
            }
        } else if (l == '>') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '=') {//>=
                resize(lexData, size, 2);
                lexData[size-2] = "Token.GREAEQU";
                lexData[size-1] = ">=";
                ++currCharPosition;
            } else {
                resize(lexData, size, 2);
                lexData[size-2] = "Token.GREATER";
                lexData[size-1] = ">";
            }
        } else if (l == '<') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '=') {//<=
                resize(lexData, size, 2);
                lexData[size-2] = "Token.LESSEQU";
                lexData[size-1] = "<=";
                ++currCharPosition;
            } else {
                resize(lexData, size, 2);
                lexData[size-2] = "Token.LESS";
                lexData[size-1] = "<";
            }
        } else if (l == '!') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '=') {//!=
                resize(lexData, size, 2);
                lexData[size-2] = "Token.NOTEQU";
                lexData[size-1] = "!=";
                ++currCharPosition;
            } else {
                resize(lexData, size, 2);
                lexData[size-2] = "Token.NOT";
                lexData[size-1] = "!";
            }
        } else if (std::isdigit(l)) {
            std::string number;
            while (data.length() > currCharPosition && std::isdigit(data.at(currCharPosition))) {
                number+=data.at(currCharPosition);
                ++currCharPosition;
            }
            --currCharPosition;
            if (data.length() >= currCharPosition && data.at(currCharPosition) == '.') {
                number+='.';
                ++currCharPosition;
                int last = currCharPosition;
                while (data.length() > currCharPosition && std::isdigit(data.at(currCharPosition + 1))) {
                    number+=data.at(currCharPosition);
                    ++currCharPosition;
                }
                --currCharPosition;
                if (last == currCharPosition) {
                    error = true;
                    resize(lexData, size);
                    lexData[size-1] = "Expeted int after decimal point at: " + std::to_string(currCharPosition + 1);
                    return lexData;
                }
            }
            resize(lexData, size, 2);
            lexData[size-2] = "Token.DIGINT";
            lexData[size-1] = number;
        } else {
            int start = 0, oldpos = currCharPosition;
            std::string keywords[] = {"if", "else", "for", "while", "let", "in", "out"}, keyword;
            for (int index = 0; index < sizeof(keywords) / sizeof(keywords[0]) && keyword.empty(); ++index) {
                while (true) {
                    if (data.length() >= currCharPosition &&
                        tolower(data.at(currCharPosition)) == keywords[index][start]) {
                        if (keywords[index].length() == start + 1) {
                            keyword = keywords[index];
                            break;
                        } else {
                            ++start;
                            ++currCharPosition;
                        }
                    } else {
                        currCharPosition = oldpos;
                        start = 0;
                        break;
                    }
                }
            }
            if (std::isalpha(l) && keyword.empty()) {
                std::string token;
                while (data.length()>currCharPosition && std::isalnum(data.at(currCharPosition))) {
                    token+=data.at(currCharPosition);
                    ++currCharPosition;
                }
                --currCharPosition;
                resize(lexData, size, 2);
                lexData[size-2] = "Token.IDENT";
                lexData[size-1] = token;
            } else {
                if (keyword.empty()) {
                    error = true;
                    resize(lexData, size);
                    lexData[size-1] = "Unknown token at "+ std::to_string(currCharPosition+1)+": "+l;
                    return lexData;
                } else {
                    resize(lexData, size, 2);
                    std::string token;
                    for(size_t i = 0;i<keyword.length();++i){
                        token+=(char)toupper(keyword[i]);
                    }
                    lexData[size-2] = "Token."+token;
                    lexData[size-1] = token;
                }
            }
        }
    }
    return lexData;
}