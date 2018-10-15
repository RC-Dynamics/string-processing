#ifndef SHIFT_OR_H
#define SHIFT_OR_H

#include <string>
#include <map>
#include <stdint.h>


#define DEBUG 0
#if DEBUG
#include <utility>
#include <bitset>
#include <iostream>
#endif

class Shift_Or{
    public:
        Shift_Or();
        unsigned int find(std::string text, std::string pat);

    private:
        std::string ab;
        std::map<char, uint_fast64_t> char_mask(std::string pat, unsigned int m);
};


#endif // SHIFT_OR_H
