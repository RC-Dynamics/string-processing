#include "sellers.h"

Sellers::Sellers()
{
}

std::vector<unsigned int> Sellers::find(std::string text, std::string pat, int r)
{
    unsigned int n = text.size();
    unsigned int m = pat.size();
    std::vector<unsigned int> qtd;
    unsigned int last = 1;
    unsigned int prev = 0;
    std::vector<std::vector<int> > D;
    std::vector<int> D_aux;

    for (unsigned int i = 0; i <= m; i++){
        D_aux.push_back(int(i));
    }
    D.push_back(D_aux);
    D.push_back(D_aux);

#if DEBUG_SELLERS
    std::cout << "n   : " << n << std::endl;
    std::cout << "m   : " << m << std::endl;

    std::cout << "D[0]:";
    for (unsigned int i = 0; i < D[0].size(); i++)
    {
        std::cout << D[0][i];
    }
    std::cout << std::endl;

    std::cout << "D[1]:";
    for (unsigned int i = 0; i < D[1].size(); i++)
    {
        std::cout << D[1][i];
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
#endif

    for (unsigned int j = 0; j < n; j++)
    {
        D[last][0] = 0;
        for (unsigned int i = 1; i <= m; i++)
        {
            D[last][i] = std::min({D[prev][i-1] + this->phi(pat[i-1], text[j]), D[prev][i] + 1, D[last][i-1] + 1});
        }
        if (D[last][m] <= r)
        {
            qtd.push_back(j);
        }
#if DEBUG_SELLERS
        std::cout << "D[0]:";
        for (unsigned int i = 0; i < D[0].size(); i++)
        {
            std::cout << D[0][i];
        }
        std::cout << std::endl;

        std::cout << "D[1]:";
        for (unsigned int i = 0; i < D[1].size(); i++)
        {
            std::cout << D[1][i];
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
#endif
        last = (last + 1) % 2;
        prev = (prev + 1) % 2;
    }
    return qtd;
}

int Sellers::phi(char p, char s)
{
    return int(p != s);
}
