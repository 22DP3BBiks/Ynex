#include <iostream>
#include "./compiler.h"

void resize(std::string *&arr, int &size, int amount){
    if(amount>1){
        size+=amount;
    }else{
        ++size;
    }
    auto *temp = new std::string[size];
    for (size_t i = 0; i<size-amount;++i){
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
}

std::string IDENTType(std::string *data, int index, std::string *var, int size){
    for(int i = 0; i <= size; i+=2){
        if(var[i] == data[index-1]){
            if(std::stoi(var[i-1])){
                return "Token.INT";
            }else if(std::stod(var[i-1])){
                return "Token.FLOAT";
            }else{
                return "Token.STRING";
            }
        }
    }
    throw std::invalid_argument("Unknown variable: "+data[index-1]+" or no value given...");
}

bool check(std::string *data, int &index, std::string type){
    std::cout << data[index+2] << " " << type << std::endl;
    if(data[index+2] == type) {
        index += 2;
        return true;
    }
    return false;
}
bool equcheck(std::string *data, int &index, std::string *var, int size){
    std::string v1 = data[index-2] == "Token.IDENT" ? IDENTType(data, index, var, size) : data[index-2], v2 = data[index+2] == "Token.IDENT" ? IDENTType(data, index, var, size) : data[index+2];
    if(v1 == v2){
        index+=2;
        return true;
    }
    return false;
}
bool checkAnyType(std::string *data, int &index, bool alsoTable=false){
    return check(data, index, "Token.STRING") || check(data, index, "Token.INT") || check(data, index, "Token.FLOAT") || check(data, index, "Token.IDENT") || check(data, index, "Token.TRUE") || check(data, index, "Token.FALSE") || (alsoTable && check(data, index, "Token.OPENBREACE"));
}

bool checkAnyComSign(std::string *data, int &index){
    return check(data, index, "Token.EQU") || check(data, index, "Token.GREAEQU") || check(data, index, "Token.GREATER") || check(data, index, "Token.LESSEQU") || check(data, index, "Token.LESS") || check(data, index, "Token.NOTEQU");
}

bool checkAnyMathSign(std::string *data, int &index){
    return check(data, index, "Token.DIVIDE") || check(data, index, "Token.MINUS") || check(data, index, "Token.PLUS") || check(data, index, "Token.MULTIPLY");
}

bool checkAnyLogicSign(std::string *data, int &index){
    return check(data, index, "Token.AND") || check(data, index, "Token.OR") || check(data, index, "Token.NOT");
}

bool expression(std::string *data, int &index, std::string *var, int size){
    if(!check(data, index, "Token.OPENPARENT") && check(data, index, "Token.CLOSEPARENT")) return false;
    if(checkAnyType(data, index)){
        while(!check(data, index, "Token.CLOSEPARENT")){
            if(checkAnyComSign(data, index) || checkAnyMathSign(data, index)) {
                if(!equcheck(data, index, var, size) && check(data, index, "Token.CLOSEPARENT")){
                    return false;
                }else if(!checkAnyType(data, index)){
                    return false;
                }
            }else{
                return true;
            }
        }
        return true;
    }else{
        return check(data, index, "Token.CLOSEPARENT");
    }
}

std::string *parser(std::string *data){
    int size = 0;
    auto *val = new std::string[size];
    int index = -2;
    while(!check(data, index, "Token.EOF")){
        if (check(data, index, "Token.COMMENT") || check(data, index, "Token.CLOSEBRACE")) continue;
        else if(check(data, index, "Token.LET") && check(data, index, "Token.IDENT")){
            if (check(data, index, "Token.SET")) {
                if (checkAnyType(data, index)) {
                    if(checkAnyComSign(data, index) || checkAnyMathSign(data, index)){
                        if(check(data, index, "Token.ENDLINE")){
                            throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
                        }
                        while(!check(data, index, "Token.ENDLINE")){
                            if (equcheck(data, index, val, size)) {
                                if(!checkAnyComSign(data, index) && !checkAnyMathSign(data, index)){
                                    break;
                                }
                            }else{
                                throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
                            }
                        }
                    }else{
                        resize(val, size, 3);
                        val[size-3] = data[index-3];
                        val[size-2] = data[index-1];
                        val[size-1] = "0";
                        if(!check(data, index, "Token.ENDLINE")) throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
                    }
                }else{
                    throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
                }

            }
            else if(check(data, index, "Token.OPENPARENT")){
                while(!check(data, index, "Token.CLOSEPARENT")){
                    if(checkAnyType(data, index)){
                        if(!check(data, index, "Token.ENDLINE")){
                            throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
                        }
                    }else{
                        throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
                    }
                }
                if(!check(data, index, "Token.ENDLINE")) throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
            }else{
                if(!check(data, index, "Token.ENDLINE")) throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
            }
        }
        else if(check(data, index, "Token.IF") || check(data, index, "Token.WHILE")){
            if(!(expression(data, index, val, size) && check(data, index, "Token.OPENBREACE"))) throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
        }
        else if(check(data, index, "Token.ELSE")){
            if(check(data, index, "Token.IF")){
                if(!(expression(data, index, val, size) && check(data, index, "Token.OPENBREACE")))throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
            }
            else{
                if(!check(data, index, "Token.OPENBREACE")) throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
            }
//            if(check(data, index, "Token.CLOSEPARENT")){
//                error = true;
//                break;
//            }
//            while(!check(data, index, "Token.CLOSEPARENT")){
//                if(checkAnyType(data, index)){
//                    if(!(checkAnyComSign(data, index) || checkAnyMathSign(data, index))){
//                        if(check(data, index, "Token.CLOSEPARENT")) break;
//                        error=true;
//                        break;
//                    }
//                }
//                else{
//                    error=true;
//                    break;
//                }
//            }
//            error = (!check(data, index, "Token.OPENBREACE") || !check(data, index, "Token.ENDLINE")) && check(data, index, "Token.EOF");
//            if(error){
//                break;
//            }
        }
        else if(check(data, index, "Token.FOR")){
//            error = !(expression(data, index) && check(data, index, "Token.OPENBREACE"));
//            if(error) break;
        }
        else if((check(data, index, "Token.OUT") || check(data, index, "Token.IN"))){
            if(!(expression(data, index, val, size) && check(data, index, "Token.ENDLINE")))
                throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
        }
        else{
            throw std::invalid_argument("Invalid statement at: "+ (index == -2 ? "0, data: "+data[0]+" ("+data[0]+")" : std::to_string(index/2+1)+", data: "+data[index+1]+" ("+data[index]+")"));
        }
    }
}