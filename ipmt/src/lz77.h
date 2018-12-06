#ifndef LZ77_H
#define LZ77_H

#include <stdint.h>
#include <string>
#include <cmath>
#include <math.h>
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
        LZ77(uint_fast64_t search_buffer_size = 512, uint_fast64_t lookahead_buffer_size = 128);

        std::string encode(std::string const & text);
        std::string decode(std::string const & code);
        
        void set_buffer_size(uint_fast64_t search_buffer_size, uint_fast64_t lookahead_buffer_size);

        std::string int_encode(uint_fast64_t x, uint_fast64_t size);
        uint_fast64_t int_decode(std::string const & x);
        
        int search_buffer = 0, lookahead_buffer = 0;

      private:
        uint_fast64_t char_in_ab(char c);
        std::vector<std::vector<uint_fast64_t> > build_fsm(std::string const & pat);
        std::pair<uint_fast64_t, uint_fast64_t> prefix_match(std::string const & window, std::string const & pat);

        std::string ab;
};


#endif // LZ77_H
