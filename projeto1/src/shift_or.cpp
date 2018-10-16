#include "shift_or.h"

Shift_Or::Shift_Or()
{
    for (unsigned int i = 0; i < AB_SIZE; i++)
    {
        this->ab += char(i);
    }
}

std::vector<unsigned int> Shift_Or::find(std::string text, std::string pat)
{
    unsigned int n = text.size();
    unsigned int m = pat.size();
    uint_fast64_t S = ~uint_fast64_t(0) >> (64 - m);
    uint_fast64_t msb = uint_fast64_t(1) << (m - 1);
    std::vector<unsigned int> qtd;
    if (this->c_mask.size() < 1)
    {
        this->set_char_mask(pat, m);
    }

    #if DEBUG
    // std::cout << "n   : " << n << std::endl;
    std::cout << "m   : " << m << std::endl;
    std::cout << "AB  : " << this->c_mask.size() << std::endl;
    std::bitset<64> S_b(S);
    std::bitset<64> msb_b(msb);
    std::cout << "S   : " << S_b << std::endl;
    std::cout << "msb : " << msb_b << std::endl;

    for (unsigned int i = 0; i < this->c_mask.size(); i++)
    {
        std::bitset<64> mask(this->c_mask[i]);
        std::cout << char(i) << "   : " << mask << std::endl;
        }
    #endif

    for (unsigned int i = 0; i < n; i++)
    {
        S = ((S << 1) | this->c_mask[int(text[i])]) & (~uint_fast64_t(0) >> (64 - m));
        #if DEBUG
            std::bitset<64> s_b(S);
            std::cout << "S[" << s << "]: " << s_b << std::endl;
        #endif
        if (S < msb)
        {
            qtd.push_back(i);
        }
    }
    return qtd;
}

void Shift_Or::set_char_mask(std::string pat, int m)
{
    if (m == -1){
        m = pat.size();
    }
    uint_fast64_t pos_mask = (~uint_fast64_t(0) - 1);
    uint_fast64_t one = uint_fast64_t(1);

    for (char s : this->ab)
    {
        this->c_mask.push_back(~uint_fast64_t(0) >> (64 - m));
    }

    for (char& s : pat)
    {
        this->c_mask[int(s)] = (this->c_mask[uint_fast64_t(s)]) & pos_mask & (~uint_fast64_t(0) >> (64 - m));
        pos_mask = (pos_mask << 1) | one;
    }
}