#ifndef WU_MANBER_H
#define WU_MANBER_H

#include <string>
#include <vector>
#include <stdint.h>

#define AB_SIZE_WU_MANBER 128

#define DEBUG_WU_MANBER 0
#if DEBUG_WU_MANBER
#include <utility>
#include <bitset>
#include <iostream>
#endif

class Wu_Manber
{
    public:
        Wu_Manber();
        std::vector<unsigned int> find(std::string text, std::string pat, unsigned int r);
        void set_char_mask(std::string pat, int m = -1);

    private:
        std::string ab;
        std::vector<uint_fast64_t> c_mask = std::vector<uint_fast64_t>();
};

#endif // WU_MANBER_H