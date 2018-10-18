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

#define AB_SIZE_AHOCORASICK 128

class Ahocorasick
{
    public:
        Ahocorasick();
        std::vector<std::vector<uint_fast16_t> > find(std::string text, std::vector<std::string> patts);
        void build_fsm(std::vector<std::string> patts);
    private:
      struct pair_hash
      {
          template <class T1, class T2>
          std::size_t operator()(const std::pair<T1, T2> &pair) const
          {
              return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
          }
      };
      std::string ab;
      std::vector<uint_fast16_t> f;
      std::vector<std::vector<uint_fast16_t> > o;
      std::unordered_map<std::pair<uint_fast16_t, char>, uint_fast16_t, pair_hash> g;

      uint_fast16_t build_goto(std::vector<std::string> patts);
      void build_fail(int n);
    
      void print_fsm(std::unordered_map<std::pair<uint_fast16_t, char>, uint_fast16_t, pair_hash> g, std::vector<std::vector<uint_fast16_t>> o, std::string ab);
};


#endif // AHOCORASICK_H
