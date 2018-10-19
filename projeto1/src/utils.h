#include <getopt.h>
#include <vector>
#include <string>
#include <fstream>

#include "shift_or.h"
#include "wu_manber.h"
#include "sellers.h"
#include "ahocorasick.h"

#define DEBUG_UTILS 0

#define AHO "aho-corasick"
#define SHI "shiftOr"
#define WU "wuManber"
#define SEL "sellers"

enum e_algrthm {
    ahocorasick = 0,
    shiftor,
    wumanber,
    sellers
} e_algrthm;

namespace utils {
    struct option long_options[] = {
        {"algorithm", required_argument, NULL, 'a'},
        {"edit", required_argument, NULL, 'e'},
        {"pattern", required_argument, NULL, 'p'},
        {"count", no_argument, NULL, 'c'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}};

    typedef struct argmnts
    {
        char *algorithm = nullptr;
        std::vector<std::string> patterns;
        uint max_pattern = 0;
        std::vector<std::string> txt_files;
        uint8_t edit_dist = 0;
        char *pattern_file = nullptr;
        bool count_only = false;
    } argmnts;

    void print_help()
    {
        printf("pmt [-a {%s, %s, %s, %s}] [-c] [-e NUM] [-p FILE]|PATTERN FILE [FILE2...]\n", AHO, SHI, WU, SEL);
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

    bool getArguments(argmnts *arg, int argc, char *argv[])
    {
        char opt;
        while ((opt = getopt_long(argc, argv, "a:e:p:ch", long_options, NULL)) != -1)
        {
            switch (opt)
            {
            case 'a':
                arg->algorithm = strdup(optarg);
                break;
            case 'e':
                arg->edit_dist = atoi(optarg);
                break;
            case 'p':
                arg->pattern_file = strdup(optarg);
                break;
            case 'c':
                arg->count_only = true;
                break;
            case 'h':
                print_help();
                return true;
            default:
                abort();
            }
        }

        if (arg->pattern_file == nullptr)
        {
            arg->patterns.push_back(argv[optind]);
        }
        else
        {
            std::ifstream f(arg->pattern_file);
            std::string str;
            while (getline(f, str))
            {
                arg->patterns.push_back(str);
                if(str.size() > arg->max_pattern)
                    arg->max_pattern = str.size();
            }
        }

        for (int i = optind + (arg->pattern_file == nullptr); i < argc; i++)
        {
            arg->txt_files.push_back(argv[i]);
        }
#if DEBUG_UTILS
        printf("Pattern File: %s\n", arg->pattern_file);
        printf("Patterns: ");
        for (auto a : arg->patterns)
        {
            printf("%s, ", a.c_str());
        }
        printf("\nFiles: ");
        for (auto a : arg->txt_files)
        {
            printf("%s, ", a.c_str());
        }

        printf("\n");
        printf("Algorithm: %s\n", arg->algorithm);
        printf("Edit Dist: %d\n", arg->edit_dist);
        printf("Count: %d\n", arg->count_only);
#endif
        return true;
    }
    
    int choseAlg(argmnts *arg) {
        if (arg->algorithm != nullptr){
            if (!strcmp(arg->algorithm, AHO))
            {
                if (arg->edit_dist == 0)
                    return ahocorasick;
                else
                    return -1;
            }
            else if ((!strcmp(arg->algorithm, SHI)))
            {
                if (arg->edit_dist == 0 && arg->max_pattern <= 64 && arg->patterns.size() == 1)
                    return shiftor;
                else
                    return -1;
            }
            else if (!strcmp(arg->algorithm, WU))
            {
                if (arg->max_pattern <= 64 && arg->patterns.size() == 1)
                    return wumanber;
                else
                    return -1;
            }
            else if (!strcmp(arg->algorithm, SEL))
            {
                if (arg->patterns.size() == 1)
                    return sellers;
                else
                    return -1;
            } else {
                return -1;
            }
        } else if (arg->patterns.size() > 1) {
            if (arg->edit_dist == 0)
                return ahocorasick;
            else
                return -1;
        } else if (arg->edit_dist > 0) {
            return wumanber;
        } else {
            return wumanber;
        }
    }

    uint run_aho(argmnts arg, Ahocorasick *aho){
        uint count = 0;
        uint last_count = 0;
        for(uint i = 0; i < arg.txt_files.size(); i++){
            std::ifstream f(arg.txt_files[i]);
            std::string line;
            std::vector<std::vector<uint_fast16_t> > occ;
            while (getline(f, line)){
                occ = aho->find(line, arg.patterns);
                for(auto a : occ){
                    count += a.size();
                }
                if (!arg.count_only && last_count != count){
                    printf("%s\n", line.c_str());
                    
                }
                last_count = count;
            }
            
        }
        return count;
    }
}

#if DEBUG_UTILS
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
#endif
