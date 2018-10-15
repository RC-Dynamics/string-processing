#include <iostream>
#include "shift_or.h"

int main (int argc, char* argv[]){
    Shift_Or a;
    unsigned int q = a.find("abcabab", "aba");
    std::cout << q << std::endl;
    return 0;
}