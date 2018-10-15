#include <iostream>
#include <map>
#include "shift_or.h"

int main (int argc, char* argv[]){
    Shift_Or a;
    std::map<char, uint_fast64_t> m = a.char_mask("aba", 3);
    unsigned int q = a.find("abcababa", "aba", m);
    std::cout << q << std::endl;
    return 0;
}