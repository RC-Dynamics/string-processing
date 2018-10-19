#include <iostream>

#include "run_algorithms.h"


void test();


int main (int argc, char* argv[]){
    utils::argmnts arg;
    utils::getArguments(&arg, argc, argv);
    int ch = utils::choseAlg(&arg);
    int count;
    if (ch == ahocorasick)
    {
        Ahocorasick search;
        search.build_fsm(arg.patterns);
        count = runner::run_aho(arg, &search);
    }
    else if (ch == shiftor){
        Shift_Or search;
        search.set_char_mask(arg.patterns[0]);
        count = runner::run_shi(arg, &search);

    }
    else if (ch == wumanber)
    {
        Wu_Manber search;
        search.set_char_mask(arg.patterns[0]);
        count = runner::run_wu(arg, &search, arg.edit_dist);
    }
    else if (ch == sellers)
    {
        Sellers search;
        count = runner::run_sel(arg, &search, arg.edit_dist);
    }
    else{
        printf("\nInvalid Option Choose\n");
        utils::print_help();
        return 0;
    }
    if (arg.count_only)
        printf("%d\n", count);
    
    return 0;
}

