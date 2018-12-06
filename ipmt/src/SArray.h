#ifndef SARRAY_H
#define SARRAY_H

#include <stdint.h>
#include <string.h>
#include <string>
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
        SArray();
        void init(char *txt);
        long long int search(char* pat, bool print = false);
        void build_prefix();
        void build_hash();
        void sa_invert();
        void lr_lcp();
        long long int lcp_p(long long int i, long long int j);
        long long int lcp_bf(char* X, char* Y);
        void fill_lrlcp(long long int left, long long int right);

        void print_lines(long long int left, long long int right);
        long long int succ2(char *pat);
        long long int pred2(char* pat);
        std::vector<long long int> SArr;
        std::vector<long long int> Llcp;
        std::vector<long long int> Rlcp;
        long long int n = 0;
        long long int l = 0;
        char *txt;

      private:
        std::vector<std::vector<long long int> > P;
        long long int hash[256];

};


#endif // SARRAY_H