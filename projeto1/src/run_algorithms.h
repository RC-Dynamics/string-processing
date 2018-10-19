#include <fstream>

#include "utils.h"

#include "shift_or.h"
#include "wu_manber.h"
#include "sellers.h"
#include "ahocorasick.h"

#define DEBUG_RUN 0

namespace runner
    {
    uint run_aho(utils::argmnts arg, Ahocorasick *aho)
    {
        uint count = 0;
        uint last_count = 0;
        for (uint i = 0; i < arg.txt_files.size(); i++)
        {
            std::ifstream f(arg.txt_files[i]);
            std::string line;
            std::vector<std::vector<uint_fast16_t>> occ;
            while (getline(f, line))
            {
                occ = aho->find(line, arg.patterns);
                for (auto a : occ)
                {
                    count += a.size();
                }
                if (!arg.count_only && last_count != count)
                {
                    printf("%s\n", line.c_str());
                }
                last_count = count;
            }
        }
        return count;
        }

        uint run_shi(utils::argmnts arg, Shift_Or *shi)
        {
            uint count = 0;
            uint last_count = 0;
            for (uint i = 0; i < arg.txt_files.size(); i++)
            {
                std::ifstream f(arg.txt_files[i]);
                std::string line;
                std::vector<unsigned int> occ;
                while (getline(f, line))
                {
                    occ = shi->find(line, arg.patterns[0]);
                    count += occ.size();
                    if (!arg.count_only && last_count != count)
                    {
                        printf("%s\n", line.c_str());
                    }
                    last_count = count;
                }
            }
            return count;
        }

        uint run_wu(utils::argmnts arg, Wu_Manber *wu, int err)
        {
            uint count = 0;
            uint last_count = 0;
            for (uint i = 0; i < arg.txt_files.size(); i++)
            {
                std::ifstream f(arg.txt_files[i]);
                std::string line;
                std::vector<unsigned int> occ;
                while (getline(f, line))
                {
                    occ = wu->find(line, arg.patterns[0], err);
                    count += occ.size();
                    if (!arg.count_only && last_count != count)
                    {
                        printf("%s\n", line.c_str());
                    }
                    last_count = count;
                }
            }
            return count;
        }

        uint run_sel(utils::argmnts arg, Sellers *sel, int err)
        {
            uint count = 0;
            uint last_count = 0;
            for (uint i = 0; i < arg.txt_files.size(); i++)
            {
                std::ifstream f(arg.txt_files[i]);
                std::string line;
                std::vector<unsigned int> occ;
                while (getline(f, line))
                {
                    occ = sel->find(line, arg.patterns[0], err);
                    count += occ.size();
                    if (!arg.count_only && last_count != count)
                    {
                        printf("%s\n", line.c_str());
                    }
                    last_count = count;
                }
            }
            return count;
        }
}



#if DEBUG_RUN
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
