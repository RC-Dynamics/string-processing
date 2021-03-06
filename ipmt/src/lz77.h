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
        LZ77(uint_fast16_t search_buffer_size = 512, uint_fast16_t lookahead_buffer_size = 128);

        std::string encode(std::string const & text);
        std::string decode(std::string const & code);
        
        void set_buffer_size(uint_fast16_t search_buffer_size, uint_fast16_t lookahead_buffer_size);

        std::string int_encode(uint_fast16_t x, uint_fast16_t size);
        uint_fast16_t int_decode(std::string const & x);
        
        int search_buffer = 0, lookahead_buffer = 0;

      private:
        uint_fast16_t char_in_ab(char c);
        std::vector<std::vector<uint_fast16_t>> build_fsm(std::string const &window, uint_fast16_t p_start, uint_fast16_t p_end);
        std::pair<uint_fast16_t, uint_fast16_t> prefix_match(std::string const &window, uint_fast16_t w_start, uint_fast16_t w_end, uint_fast16_t p_start, uint_fast16_t p_end);

        std::string ab;
};


#endif // LZ77_H
