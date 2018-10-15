#include <iostream>
#include <map>
#include "shift_or.h"
#include "wu_manber.h"

int main (int argc, char* argv[]){
    Shift_Or a;
    a.set_char_mask("aba");
    unsigned int q_s = a.find("abcababa", "aba");
    std::cout << "Shift_Or : " << q_s << std::endl;

    Wu_Manber b;
    b.set_char_mask("cada");
    unsigned int q_w = b.find("abadac", "cada", 4);
    std::cout << "Wu_Manber: " << q_w << std::endl;
    return 0;
}