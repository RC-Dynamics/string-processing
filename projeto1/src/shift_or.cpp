#include "shift_or.h"

Shift_Or::Shift_Or()
{
    for (unsigned int i = 0; i < 128; i++){
        this->ab += char(i);
    }
}

unsigned int Shift_Or::find(std::string text, std::string pat)
{
    // unsigned int n = text.size();
    unsigned int m = pat.size();
    uint_fast64_t S = ~uint_fast64_t(0) >> (64 - m);
    uint_fast64_t msb = uint_fast64_t(1) << (m - 1);
    unsigned int qtd = 0;
    std::map<char, uint_fast64_t> C = this->char_mask(pat, m);

    #if DEBUG
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    std::bitset<64> S_b(S);
    std::bitset<64> msb_b(msb);
    std::cout << "S   : " << S_b << std::endl;
    std::cout << "msb : " << msb_b << std::endl;

    for (std::pair<char, uint_fast64_t> b : C){
        std::bitset<64> mask(b.second);
        std::cout << b.first << "   : " << mask << std::endl;
    }
    #endif

    for (char& s : text)
    {
        S = ((S << 1) | C[s]) & (~uint_fast64_t(0) >> (64 - m));
        #if DEBUG
        std::bitset<64> s_b(S);
        std::cout << "S[" << s << "]: " << s_b << std::endl;
        #endif
        if (S < msb)
        {
            qtd++;
        }
    }
    return qtd;
}

std::map<char, uint_fast64_t> Shift_Or::char_mask(std::string pat, unsigned int m)
{
    uint_fast64_t pos_mask = (~uint_fast64_t(0) - 1);
    std::map<char, uint_fast64_t> C;
    uint_fast64_t one = uint_fast64_t(1);

    for (char s : this->ab)
    {
        C[s] = ~uint_fast64_t(0) >> (64 - m);
    }

    for (char& s : pat)
    {
        C[s] = C[s] & pos_mask & (~uint_fast64_t(0) >> (64 - m));
        pos_mask = (pos_mask << 1) | one;
    }

    return C;
}