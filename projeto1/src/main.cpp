#include <iostream>
#include <map>
#include "shift_or.h"
#include "wu_manber.h"
#include "sellers.h"

int main (int argc, char* argv[]){
    Shift_Or a;
    a.set_char_mask("aba");
    std::vector<unsigned int> q_s = a.find("abcababa", "aba");
    std::cout << "Shift_Or : " << q_s.size() << " - [";
    for (unsigned int q : q_s)
    {
        std::cout << q << ", ";
    }
    std::cout << "]" << std::endl;

    Wu_Manber b;
    b.set_char_mask("cada");
    std::vector<unsigned int> q_w = b.find("abadac", "cada", 2);
    std::cout << "Wu_Manber: " << q_w.size() << " - [";
    for (unsigned int q : q_w)
    {
        std::cout << q << ", ";
    }
    std::cout << "]" << std::endl;

    Sellers c;
    std::vector<unsigned int> q_c = c.find("abadac", "cada", 2);
    std::cout << "Sellers: " << q_c.size() << " - [";
    for (unsigned int q : q_c)
    {
        std::cout << q << ", ";
    }
    std::cout << "]" << std::endl;

    return 0;
}