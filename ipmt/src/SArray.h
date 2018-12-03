#ifndef SARRAY_H
#define SARRAY_H

#include <stdint.h>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <tuple>


#define DEBUG_SARRAY 0
#if DEBUG_SARRAY
#include <iostream>
#endif

class SArray {
    public:
        SArray(char* txt);
        int search(char* pat);
        void build_prefix();
        void build_hash();
        void sa_invert();
        void lr_lcp();
        int lcp_p(int i, int j);
        int lcp_bf(char* X, char* Y);
        void fill_lrlcp(int left, int right);

        int succ2(char* pat);
        int pred2(char* pat);

      private:
        std::vector<std::vector<int> > P;
        std::vector<int> SArr;
        std::vector<int> Llcp;
        std::vector<int> Rlcp;
        int hash[256];
        int n = 0;
        int l = 0;
        char *txt;

};


#endif // SARRAY_H