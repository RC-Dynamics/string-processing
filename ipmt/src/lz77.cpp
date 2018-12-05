#include "lz77.h"

LZ77::LZ77(uint_fast16_t search_buffer_size, uint_fast16_t lookahead_buffer_size)
{
    for (unsigned int i = 0; i < AB_SIZE_LZ77; i++)
    {
        this->ab += char(i);
    }
    this->lookahead_buffer = lookahead_buffer_size;
    this->search_buffer = search_buffer_size;
    #if DEBUG_LZ77
        this->ab = "abc0123456789";
    #endif
}

void LZ77::set_buffer_size(uint_fast16_t search_buffer_size, uint_fast16_t lookahead_buffer_size)
{
    this->lookahead_buffer = lookahead_buffer_size;
    this->search_buffer = search_buffer_size;
}

uint_fast16_t LZ77::char_in_ab(char c)
{
    return (uint_fast16_t) c;
    // DEBUG: When alphabet is not all all ASCII character
    // return this->ab.find(c);
}

std::vector<std::vector<uint_fast16_t> > LZ77::build_fsm(std::string const & pat)
{
    uint_fast16_t m = pat.size();
    uint_fast16_t l = this->ab.size();

    std::vector<std::vector<uint_fast16_t> > delta;

    std::vector<uint_fast16_t> temp;

    while (l--) {
        temp.push_back(0);
    }
    temp[this->char_in_ab(pat[0])] = 1;
    delta.push_back(temp);

    uint_fast16_t brd = 0;
    for (uint_fast16_t i = 1; i < m; i++) {
        temp.clear();
        for (char c : this->ab) {
            temp.push_back(delta[brd][this->char_in_ab(c)]);
        }
        temp[this->char_in_ab(pat[i])] = i + 1;
        brd = delta[brd][this->char_in_ab(pat[i])];

        delta.push_back(temp);
    }

    temp.clear();
    for (char c : this->ab) {
        temp.push_back(delta[brd][this->char_in_ab(c)]);
    }
    delta.push_back(temp);

    #if DEBUG_LZ77
        std::cout << "delta pat = " << pat << std::endl;
        for (char c : this->ab) {
            std::cout << c << " :";
            for (uint_fast16_t i = 0; i < m; i++) {
                std::cout << " " << delta[i][this->char_in_ab(c)];
            }
            std::cout << std::endl;
        }
    #endif

    return delta;
}

std::pair<uint_fast16_t, uint_fast16_t> LZ77::prefix_match(std::string const & window, std::string const & pat)
{
    std::vector<std::vector<uint_fast16_t> > fsm = this->build_fsm(pat);

    uint_fast16_t maxlen = 0;
    uint_fast16_t cur = 0;
    uint_fast16_t pos = 0;

    uint_fast16_t n = (uint_fast16_t) window.size();
    uint_fast16_t ls = n - pat.size();

    for (uint_fast16_t i = 0; i < n; i++) {
        cur = fsm[cur][this->char_in_ab(window[i])];
        #if DEBUG_LZ77
            std::cout << "cur: " << cur;
            std::cout << " maxlen: " << maxlen;
            std::cout << " i: " << i;
            std::cout << " ls: " << ls;
            std::cout << std::endl;
        #endif
        if ((cur > maxlen) && (( i - cur + 1) < ls)) {
            maxlen = cur;
            pos = i - cur + 1;
        }
    }
    maxlen = std::min(pat.size() - 1, maxlen);
    return std::make_pair(pos, maxlen);
}

std::string LZ77::int_encode(uint_fast16_t x, uint_fast16_t size)
{
    uint_fast16_t base = (u_int16_t) this->ab.size();
    uint_fast16_t code_size = (u_int16_t) ceil(log(size) / log(base));
    std::string code;

    uint_fast16_t bit;

    while (x > 0) {
        bit = x % base;
        code = ab[bit] + code;
        x /= base;
    }

    #if DEBUG_LZ77
        std::cout << "base: " << base;
        std::cout << " codesize: " << code_size;
        std::cout << " code: " << code;
        std::cout << std::endl;
    #endif
    
    return std::string(code_size - code.size(), this->ab[0]) + code;
}

uint_fast16_t LZ77::int_decode(std::string const & x)
{
    uint_fast16_t base = (u_int16_t)this->ab.size();
    uint_fast16_t power = 1;
    uint_fast16_t val = 0;

    for (int i = (x.size() - 1); i >= 0; i--)
    {
        val += this->ab.find(x[i]) * power;
        power *= base;
    }

    return val;
}

std::string LZ77::encode(std::string const & text)
{
    std::string W = std::string(this->search_buffer, this->ab[0]) + text;
    uint_fast16_t n = (u_int16_t) W.size();
    uint_fast16_t j = this->search_buffer;
    std::pair<uint_fast16_t, uint_fast16_t> pos_len;
    std::string code;
    while (j < n) {
        #if DEBUG_LZ77
            std::cout << "< " << W.substr(j - this->search_buffer, this->search_buffer) << " | " << W.substr(j, std::min(n, j + this->lookahead_buffer) - j) << " >" << std::endl;
        #endif
        pos_len = this->prefix_match(W.substr(j - this->search_buffer, std::min(n, j + this->lookahead_buffer) - (j - this->search_buffer)), W.substr(j, std::min(n, j + this->lookahead_buffer) - j));
        #if DEBUG_LZ77
            std::cout << "p: " << pos_len.first << " l: " << pos_len.second << std::endl;
        #endif
        code += this->int_encode(pos_len.first, this->search_buffer);
        code += this->int_encode(pos_len.second, this->lookahead_buffer);
        code += W[j + pos_len.second];
        j += (pos_len.second + 1);
    }
    return code;
}

std::string LZ77::decode(std::string const & code)
{
    std::string text(this->search_buffer, ab[0]);
    uint_fast16_t l = this->ab.size();
    uint_fast16_t bs = (uint_fast16_t)ceil(log(this->search_buffer) / log(l));
    uint_fast16_t bl = (uint_fast16_t)ceil(log(this->lookahead_buffer) / log(l));
    uint_fast16_t j = 0;
    uint_fast16_t sb_init = 0;

    uint_fast16_t p;
    std::string c;

    while (j < code.size()) {
        p = int_decode(code.substr(j, bs));
        j += bs;
        l = int_decode(code.substr(j, bl));
        j += bl;
        c = code[j];
        j++;
        for (uint_fast16_t i = 0; i < l; i++) {
            text += text[sb_init + p + i];
        }
        text += c;
        sb_init += (l + 1);
    }

    return text.substr(this->search_buffer, text.size() - this->search_buffer);
}
