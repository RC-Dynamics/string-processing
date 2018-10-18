#include <iostream>

#include "shift_or.h"
#include "wu_manber.h"
#include "sellers.h"
#include "ahocorasick.h"
#include "utils.h"


void test();


int main (int argc, char* argv[]){
    utils::argmnts arg;
    utils::getArguments(&arg, argc, argv);
    switch (utils::choseAlg(&arg)) {
        case ahocorasick:
            printf("\nAHOCORASICK\n");
            break;
        case shiftor:
            printf("\nSHIFTOR\n");
            break;
        case wumanber:
            printf("\nWUMANBER\n");
            break;
        case sellers:
            printf("\nSELLERS\n");
            break;
        default:
            printf("\nInvalid Option Choose\n");
            break;
    }
    return 0;
}

void test()
{
    Shift_Or a;
    a.set_char_mask("aba");
    std::vector<unsigned int> q_q = a.find("abcababa", "aba");
    std::cout << "Shift_Or : " << q_q.size() << " - [";
    for (unsigned int q : q_q)
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

    std::string txt = "she sells sea shells at the sea shore for her friends";
    std::vector<std::string> patts = {"he", "she", "his", "hers"};
    Ahocorasick d;
    d.build_fsm(patts);
    std::vector<std::vector<uint_fast16_t>> q_a = d.find(txt, patts);
    std::cout << "Ahocorasick : " << q_a.size() << " - [";
    for (std::vector<uint_fast16_t> q : q_a)
    {
        std::cout << "[ ";
        for (uint_fast16_t a : q)
        {
            std::cout << a << ", ";
        }
        std::cout << "], ";
    }
    std::cout << "]" << std::endl;
}

