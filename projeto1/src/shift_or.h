#ifndef SHIFT_OR_H
#define SHIFT_OR_H

#include <string>
#include <stdint.h>
#include <vector>

#define AB_SIZE 128

#define DEBUG 0
#if DEBUG
#include <utility>
#include <bitset>
#include <iostream>
#endif

class Shift_Or
{
    public:
        Shift_Or();
        std::vector<unsigned int> find(std::string text, std::string pat);
        void set_char_mask(std::string pat, int m = -1);

    private:
        std::string ab;
        std::vector<uint_fast64_t> c_mask = std::vector<uint_fast64_t>();
};


#endif // SHIFT_OR_H
