#ifndef LZ77_H
#define LZ77_H

#include <string>
#include <stdint.h>
#include <vector>

#define AB_SIZE_LZ77 128

#define DEBUG_LZ77 0
#if DEBUG_LZ77
#include <utility>
#include <bitset>
#include <iostream>
#endif

class LZ77
{
    public:
        LZ77();
        std::vector<unsigned int> find(std::string text, std::string pat);

    private:
        std::string ab;
};


#endif // LZ77_H
