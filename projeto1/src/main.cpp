#include <iostream>

#include "utils.h"


void test();


int main (int argc, char* argv[]){
    utils::argmnts arg;
    utils::getArguments(&arg, argc, argv);
    int ch = utils::choseAlg(&arg);
    if (ch == ahocorasick){
        // printf("\nAHOCORASICK\n");
        Ahocorasick d;
        d.build_fsm(arg.patterns);
        int count = utils::run_aho(arg, &d);
        if(arg.count_only)
            printf("\nTotal Number of Occurrences: %d\n", count);
    }
    else if (ch == shiftor){
        // printf("\nSHIFTOR\n");
    }
    else if (ch == wumanber)
    {
        // printf("\nWUMANBER\n");
    }
    else if (ch == sellers)
    {
        // printf("\nSELLERS\n");
    }
    else
        printf("\nInvalid Option Choose\n");
    return 0;
}

