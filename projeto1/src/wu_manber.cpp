#include "wu_manber.h"

Wu_Manber::Wu_Manber()
{
    for (unsigned int i = 0; i < AB_SIZE_WU_MANBER; i++)
    {
        this->ab += char(i);
    }
}

std::vector<unsigned int> Wu_Manber::find(std::string text, std::string pat, unsigned int r)
{
    unsigned int n = text.size();
    unsigned int m = pat.size();
    std::vector<uint_fast64_t> S;
    uint_fast64_t S_1, S_2;
    uint_fast64_t msb = uint_fast64_t(1) << (m - 1);
    std::vector<unsigned int> qtd;
    if (this->c_mask.size() < 1)
    {
        this->set_char_mask(pat, m);
    }

    S.push_back(~uint_fast64_t(0) >> (64 - m));
    for (unsigned int i = 1; i <= r; i ++){
        S.push_back((S[i - 1] << 1) & S[0]);
    }

#if DEBUG_WU_MANBER
    std::cout << "n   : " << n << std::endl;
    std::cout << "m   : " << m << std::endl;
    std::cout << "AB  : " << this->c_mask.size() << std::endl;
    std::cout << "S   : " << S.size() << std::endl;
    for (unsigned int i = 0; i < S.size(); i++)
    {
        std::bitset<64> S_b(S[i]);
        std::cout << "S[" << i << "]: " << S_b << std::endl;
    }
    std::bitset<64> msb_b(msb);
    std::cout << "msb : " << msb_b << std::endl;

    // for (unsigned int i = 0; i < this->c_mask.size(); i++)
    // {
    //     std::bitset<64> mask(this->c_mask[i]);
    //     std::cout << char(i) << "   : " << mask << std::endl;
    // }
#endif

    for (unsigned int i = 0; i < n; i++)
    {
        S[0] = ((S[0] << 1) | this->c_mask[int(text[i])]) & (~uint_fast64_t(0) >> (64 - m));
        S_1 = S[0];
        for (unsigned int q = 1; q <= r; q++) {
            S_2 = S[q];
            S[q] = ((S[q] << 1) | this->c_mask[int(text[i])]) & (S[q - 1] << 1) & (S_1 << 1) & (S_1);
            // S[q] = ((S[q - 1] << 1) | this->c_mask[int(text[i])]) & (S[q] << 1) & (S_1 << 1) & (S_1);
            S_1 = S_2;
        }
        if (S[r] < msb)
        {
            qtd.push_back(i);
        }
#if DEBUG_WU_MANBER
        std::cout << std::endl << text[i] << std::endl;
        for (unsigned int j = 0; j <= r; j++)
        {
            std::bitset<64> S_b(S[j]);
            std::cout << "S[" << j << "]: " << S_b << std::endl;
        }
#endif
    }
    return qtd;
}

void Wu_Manber::set_char_mask(std::string pat, int m)
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