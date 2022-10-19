#include <fstream>
#include <iostream>


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
    for(int currCharPosition = 0; currCharPosition<data.length();++currCharPosition){
        char l = data.at(currCharPosition);
        //std::cout << l << " ";
        if(l == ' ' || l == '\n' || l == '\r' || l == '\t') continue;
        if(l == '-'){
            std::cout << "Token.MINUS" << std::endl;
        }
        else if(l=='+'){
            std::cout << "Token.PLUS" << std::endl;
        }
        else if(l=='*'){
            std::cout << "Token.MULTIPLY" << std::endl;
        }
        else if(l==';'){
            std::cout << "Token.ENDLINE" << std::endl;
        }
        else if(l=='/'){
            if(data.length()>=currCharPosition+1 && data.at(currCharPosition+1) == '/'){
                ++currCharPosition;
                while (data.length()>=currCharPosition+1 && data.at(currCharPosition) != '\n') {
                    ++currCharPosition;
                }
                std::cout << "Token.COMMENT" << std::endl;
            }
            std::cout << "Token.DIVIDE" << std::endl;
        }
        else if(l=='#'){
            std::cout << "Token.LENGTH" << std::endl;
        }
        else if(l=="'"[0] || l=='"'){
            ++currCharPosition;
            while (data.at(currCharPosition) != "'"[0] && data.at(currCharPosition) != '"') {
                if(data.length()==currCharPosition+1){
                    std::cerr << "Missing end char \' or \" at: " << currCharPosition+1;
                    return -2;
                }
                ++currCharPosition;
            }
            std::cout << "Token.STRING" << std::endl;
        }
        else if(l=='='){
            if(data.length()>=currCharPosition+1 && data.at(currCharPosition+1) == '='){//==
                std::cout << "Token.EQU" << std::endl;
                ++currCharPosition;
                continue;
            }
            std::cout << "Token.SET" << std::endl;
        }
        else if(l=='>'){
            if(data.length()>=currCharPosition+1 && data.at(currCharPosition+1) == '='){//>=
                std::cout << "Token.GREAEQU" << std::endl;
                ++currCharPosition;
            }
        }
        else if(l=='<'){
            if(data.length()>=currCharPosition+1 && data.at(currCharPosition+1) == '='){//<=
                std::cout << "Token.LESSEQU" << std::endl;
                ++currCharPosition;
            }
        }
        else if(l=='!'){
            if(data.length()>=currCharPosition+1 && data.at(currCharPosition+1) == '='){//!=
                std::cout << "Token.NOTEQU" << std::endl;
                ++currCharPosition;
            }
        }
        else if(std::isdigit(l)){
            ++currCharPosition;
            while (std::isdigit(data.at(currCharPosition))) {
                ++currCharPosition;
            }
            if(data.length()>=currCharPosition && data.at(currCharPosition) == '.'){
                ++currCharPosition;
                int last = currCharPosition;
                while(std::isdigit(data.at(currCharPosition))){
                    ++currCharPosition;
                }
                if(last == currCharPosition){
                    std::cerr << "Expeted int after decimal point at: " << currCharPosition+1;
                    return -2;
                }
            }
            std::cout << "Token.DIGINT" << std::endl;
        }
        else{
            int start=0, oldpos = currCharPosition;
            std::string keywords[] = {"if", "else", "for", "while", "let"}, keyword;
            for(int index = 0; index<sizeof(keywords)/sizeof(keywords[0]) && keyword.empty();++index){
                while(true){
                    //std::cout << index << " " << start << " " << data.at(currCharPosition) << std::endl;
                    if(data.length()>=currCharPosition && tolower(data.at(currCharPosition)) == keywords[index][start]){
                        if(keywords[index].length() == start+1){
                            keyword=keywords[index];
                            break;
                        }else{
                            ++start;
                            ++currCharPosition;
                        }
                    }
                    else{
                        currCharPosition=oldpos;
                        start = 0;
                        break;
                    }
                }
            }

            if(keyword.empty()){
                std::cerr << "Unknown token at " << currCharPosition+1 << ": " << l;
                return -2;
            }
            else{
                std::cout << "Token." << keyword << std::endl;
            }
        }
        //com << l;
    }
    code.close();
    com.close();
    return 0;
}
