#ifndef LZ77_H
#define LZ77_H

#include <stdint.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#define AB_SIZE_LZ77 128

#define DEBUG_LZ77 0
#if DEBUG_LZ77
#include <iostream>
#endif

class LZ77
{
    public:
        LZ77(uint_fast16_t search_buffer_size, uint_fast16_t lookahead_buffer_size);
        std::string encode(std::string text);
        std::string decode(std::string code);

      private:
        std::vector<std::vector<uint_fast16_t> > build_fsm(std::string pat);
        std::string int_encode(uint_fast16_t x, uint_fast16_t size);
        uint_fast16_t int_decode(std::string x);
        std::pair<uint_fast16_t, uint_fast16_t> prefix_match(std::string window, std::string pat);

        uint_fast16_t search_buffer = 0, lookahead_buffer = 0;
        std::string ab;
};


#endif // LZ77_H
