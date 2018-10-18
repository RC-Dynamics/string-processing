#include <iostream>
#include <getopt.h>
#include <vector>
#include <string>
#include <fstream>

#include "shift_or.h"
#include "wu_manber.h"
#include "sellers.h"
#include "ahocorasick.h"

struct option long_options[] = {
    {"algorithm", required_argument, NULL, 'a'},
    {"edit", required_argument, NULL, 'e'},
    {"pattern", required_argument, NULL, 'p'},
    {"count", no_argument, NULL, 'c'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}};

void test();
void print_help();
int main (int argc, char* argv[]){
    char opt;
    char* algorithm = nullptr;
    uint8_t edit_dist = 0;
    char* pattern_file = nullptr;
    bool count_only = false;
    std::vector <std::string> patterns;
    while ((opt = getopt_long(argc, argv, "a:e:p:ch", long_options, NULL)) != -1) {
        switch (opt)
        {
            case 'a':
                algorithm = strdup(optarg);
                break;
            case 'e':
                edit_dist = atoi(optarg);
                break;
            case 'p':
                pattern_file = strdup(optarg);
                break;
            case 'c':
                count_only = true;
                break;
            case 'h':
                print_help();
                return 0;
            default:
                abort();
        }
    }
    
    if(pattern_file == nullptr){
        patterns.push_back(argv[optind]);
    } else {
        std::ifstream f(pattern_file);
        std::string str;
        while (getline(f, str))
        {
            patterns.push_back(str);
        }
    }

    printf("%d", optind);
    printf("Patterns: ");
    for (auto a : patterns){
        printf("%s ", a);
    }
    printf("\n");
    printf("Algorithm: %s\n", algorithm);
    printf("Edit Dist: %d\n", edit_dist);
    printf("Pattern: %s\n", pattern_file);
    printf("Count: %d\n", count_only);

    // test();

    return 0;
}

void test(){
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

void print_help()
{
    printf("pmt [-a {shiftOr,wuManber, sellers, aho-corasick}] [-c] [-e NUM] [-p FILE]|PATTERN FILE [FILE2...]\n");
    printf("Pattern search in files.\n");
    printf("Algorithms:\n");
    printf("ShiftOr, ");
    printf("WuManber, ");
    printf("Sellers, ");
    printf("Aho-Corasick\n");
    printf("\t--algorithm -a ALGORITHMS    Chose algorithm\n");
    printf("\t--count     -c               Print only occurrences count\n");
    printf("\t--edit      -e NUM           NUM chooses algorithm edit distance\n");
    printf("\t                               Used only if algorithm supports\n");
    printf("\t                               If no algoritmh chose, ...  \n");
    printf("\t--pattern   -p ARQUIVO       Search each pattern on file, one per line\n");
    printf("\t--help      -h               Show help\n");
}