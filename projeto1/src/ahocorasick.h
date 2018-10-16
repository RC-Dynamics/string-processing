#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include <string>
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <algorithm>

#define AB_SIZE 128

class Ahocorasick
{
    public:
        Ahocorasick();
        std::vector<std::vector<uint_fast16_t>> find(std::string text, std::vector<std::string> patts);
        void build_fsm(std::vector<std::string> patts);
    private:
        std::string ab;
        std::vector<uint_fast16_t> f;
        std::vector<std::vector<uint_fast16_t>> o;
        std::unordered_map<std::pair<uint_fast16_t, char>, uint_fast16_t> g;

        uint_fast16_t build_goto(std::vector<std::string> patts);
        void build_fail(std::vector<std::string> patts, int n);
};

#endif // AHOCORASICK_H
