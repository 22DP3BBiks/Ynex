#include <fstream>
#include <iostream>

int main(int argsc, char *args[]) {
    std::string keyW[] = { "var","if","else", "func", "out", "in", "&"};
    if (!args[1]) {
        std::cout << "Expected code file!" << " ";
        return -1;
    }

    std::ifstream code(args[1]);
    if (!args[2]) args[2] = "./main";
    std::ofstream com(args[2], std::ios::out | std::ios::trunc);

    if (!code.is_open()) {
        std::cout << "Couldn't open code file!" << std::endl;
        return -1;
    }
    if (!com.is_open()) {
        std::cout << "Couldn't open or make compiled file!" << std::endl;
        return -1;
    }

    std::string data;

    data.assign((std::istreambuf_iterator<char>(code)),
                std::istreambuf_iterator<char>());
    com << "int main(int argsc, char *args[]) {" << std::endl;



//    int i = 0;
//    while (i != std::string::npos || data.empty()) {
//        int n = 0;
//        for (int n = 0; n < sizeof(keyW)/sizeof(keyW[0]); ++n) {
//            n = data.find(keyW[n], i);
//            if(n!=0){
//
//                i=n;
//            }
//        }
//    }
    com << data;
    com << std::endl << "   return 0;" << std::endl << "}";
    code.close();
    com.close();
    return 0;
}
