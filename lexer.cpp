#include <iostream>
#include "./compiler.h"
int *s;

void resize(std::string *&arr, int amount){
    if(amount>1){
        *s+=amount;
    }else{
        ++*s;
    }
    std::string *temp = new std::string[*s];
    for (size_t i = 0; i<*s-amount;++i){
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
}

std::string *lexer(std::string data, int &size){
    s = &size;
    std::string *lexData = new std::string[*s];
    for(int currCharPosition = 0; currCharPosition<data.length();++currCharPosition) {
        char l = data.at(currCharPosition);
        //std::cout << l << std::endl;
        if (l == ' ' || l == '\n' || l == '\r' || l == '\t') continue;
        if (l == '-') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.MINUS";
            lexData[*s-1] = "-";
        } else if (l == '+') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.PLUS";
            lexData[*s-1] = "+";
        } else if (l == '*') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.MULTIPLY";
            lexData[*s-1] = "*";
        } else if (l == ';') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.ENDLINE";
            lexData[*s-1] = ";";
        } else if (l == '(') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.OPENPARENT";
            lexData[*s-1] = "(";
        } else if (l == ')') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.CLOSEPARENT";
            lexData[*s-1] = ")";
        } else if (l == '{') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.OPENBREACE";
            lexData[*s-1] = "{";
        } else if (l == '}') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.CLOSEBRACE";
            lexData[*s-1] = "}";
        } else if (l == '[') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.OPENBRACKET";
            lexData[*s-1] = "[";
        } else if (l == ']') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.CLOSEBRACKET";
            lexData[*s-1] = "]";
        } else if (l == '/') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '/') {
                std::string comment;
                while (data.length() >= currCharPosition && data.at(currCharPosition) != '\n') {
                    comment+=data.at(currCharPosition++);
                }
                resize(lexData, 2);
                lexData[*s-2] = "Token.COMMENT";
                lexData[*s-1] = comment;
            } else {
                resize(lexData, 2);
                lexData[*s-2] = "Token.DIVIDE";
                lexData[*s-1] = "/";
            }
        } else if (l == '#') {
            resize(lexData, 2);
            lexData[*s - 2] = "Token.LENGTH";
            lexData[*s - 1] = "#";
        } else if (l == '?') {
            resize(lexData, 2);
            lexData[*s-2] = "Token.QUSTIONMARK";
            lexData[*s-1] = "?";
        } else if (l == "'"[0] || l == '"') {
            std::string string = "\"";
            ++currCharPosition;
            while (data.at(currCharPosition) != "'"[0] && data.at(currCharPosition) != '"') {
                if (data.length() == currCharPosition + 1) {
                    throw std::invalid_argument("Unknown token at "+ std::to_string(currCharPosition+1)+": "+l);
                    resize(lexData, *s);
                    lexData[*s-1] = "Missing end char \' or \" at: " + std::to_string(currCharPosition + 1);
                    return lexData;
                }
                string+=data.at(currCharPosition);
                ++currCharPosition;
            }
            string+="\"";
            resize(lexData, 2);
            lexData[*s-2] = "Token.STRING";
            lexData[*s-1] = string;
        } else if (l == '=') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '=') {//==
                resize(lexData, 2);
                lexData[*s-2] = "Token.EQU";
                lexData[*s-1] = "==";
                ++currCharPosition;
            } else {
                resize(lexData, 2);
                lexData[*s-2] = "Token.SET";
                lexData[*s-1] = "=";
            }
        } else if (l == '>') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '=') {//>=
                resize(lexData, 2);
                lexData[*s-2] = "Token.GREAEQU";
                lexData[*s-1] = ">=";
                ++currCharPosition;
            } else {
                resize(lexData, 2);
                lexData[*s-2] = "Token.GREATER";
                lexData[*s-1] = ">";
            }
        } else if (l == '<') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '=') {//<=
                resize(lexData, 2);
                lexData[*s-2] = "Token.LESSEQU";
                lexData[*s-1] = "<=";
                ++currCharPosition;
            } else {
                resize(lexData, 2);
                lexData[*s-2] = "Token.LESS";
                lexData[*s-1] = "<";
            }
        } else if (l == '!') {
            if (data.length() > currCharPosition && data.at(currCharPosition + 1) == '=') {//!=
                resize(lexData, 2);
                lexData[*s-2] = "Token.NOTEQU";
                lexData[*s-1] = "!=";
                ++currCharPosition;
            } else {
                resize(lexData, 2);
                lexData[*s-2] = "Token.NOT";
                lexData[*s-1] = "!";
            }
        } else if (l == '&' && data.length() > currCharPosition && data.at(currCharPosition + 1) == '&') {//&&
            resize(lexData, 2);
            lexData[*s-2] = "Token.AND";
            lexData[*s-1] = "&&";
            ++currCharPosition;
        } else if (l == '|' && data.length() > currCharPosition && data.at(currCharPosition + 1) == '|') {//||
            resize(lexData, 2);
            lexData[*s-2] = "Token.OR";
            lexData[*s-1] = "||";
            ++currCharPosition;
        } else if (std::isdigit(l)) {
            std::string number;
            while (data.length() > currCharPosition && std::isdigit(data.at(currCharPosition))) {
                number+=data.at(currCharPosition++);
            }
            if (data.length() >= currCharPosition && data.at(currCharPosition) == '.') {
                number+='.';
                int last = ++currCharPosition;
                while (data.length() > currCharPosition && std::isdigit(data.at(currCharPosition))) {
                    number+=data.at(currCharPosition++);
                }
                if (last == currCharPosition) {
                    throw std::invalid_argument("Expeted int after decimal point at: " + std::to_string(currCharPosition + 1));
                }
                resize(lexData, 2);
                lexData[*s-2] = "Token.FLOAT";
                lexData[*s-1] = number;
            }else{
                resize(lexData, 2);
                lexData[*s-2] = "Token.INT";
                lexData[*s-1] = number;
            }
            --currCharPosition;
        } else {
            int start = 0, oldpos = currCharPosition;
            std::string keywords[] = {"if", "else", "for", "while", "let", "in", "out", "true", "false"}, keyword;
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
                while (data.length() > currCharPosition && std::isalnum(data.at(currCharPosition))) {
                    token+=data.at(currCharPosition++);
                }
                --currCharPosition;
                resize(lexData, 2);
                lexData[*s-2] = "Token.IDENT";
                lexData[*s-1] = token;
            } else {
                if (keyword.empty()) {
                    throw std::invalid_argument("Unknown token at "+ std::to_string(currCharPosition+1)+": "+l);
                } else {
                    resize(lexData, 2);
                    std::string token;
                    for(size_t i = 0;i<keyword.length();++i){
                        token+=(char)toupper(keyword[i]);
                    }
                    lexData[*s-2] = "Token."+token;
                    lexData[*s-1] = token;
                }
            }
        }
    }
    resize(lexData, 2);
    lexData[*s-2] = "Token.EOF";
    lexData[*s-1] = "EOF";
    return lexData;
}