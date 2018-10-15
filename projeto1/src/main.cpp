#include <iostream>
#include <map>
#include "shift_or.h"

int main (int argc, char* argv[]){
    Shift_Or a;
    a.set_char_mask("aba");
    unsigned int q = a.find("abcababa", "aba");
    std::cout << q << std::endl;
    return 0;
}