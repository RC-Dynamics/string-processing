#ifndef SELLERS_H
#define SELLERS_H

#include <string>
#include <stdint.h>
#include <vector>
#include <algorithm>

#define DEBUG 0
#if DEBUG
#include <utility>
#include <iostream>
#endif

class Sellers
{
    public:
        Sellers();
        unsigned int find(std::string text, std::string pat, int r);

    private:
        int phi(char p, char s);
};

#endif // SELLERS_H
