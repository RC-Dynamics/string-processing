#include "ahocorasick.h"



void Ahocorasick::print_fsm(std::unordered_map<std::pair<uint_fast16_t, char>, uint_fast16_t, pair_hash> g, std::vector<std::vector<uint_fast16_t> > o, std::string ab)
{
    int nxt = o.size();
    std::cout << "goto" << std::endl;
    for (int s = 0; s < nxt; s++){
        std::cout << s << ":";
        for (char a : ab) {
            if (g.find({s, a}) != (g).end()){
                std::cout << a << "-->" << g[{s, a}] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "occ" << std::endl;
    for (int s = 0; s < nxt; s++) {
        std::cout << s << ":";
        for(uint i = 0; i < o[s].size(); i++){
            std::cout << o[s][i] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


Ahocorasick::Ahocorasick()
{
    for (unsigned int i = 0; i < AB_SIZE; i++)
    {
        this->ab += char(i);
    }
}

void Ahocorasick::build_fsm(std::vector<std::string> patts)  {
    uint_fast16_t n = this->build_goto(patts);
    this->build_fail(n);
    print_fsm(this->g, this->o, this->ab);
    
}

uint_fast16_t Ahocorasick::build_goto(std::vector<std::string> patts) {
    unsigned int ms = patts.size();
    uint_fast16_t nxt = 0;
    uint_fast16_t m, cur, j;
    std::string pat;
    std::vector<uint_fast16_t> temp;
    ((this->o)).push_back(temp);
    for (unsigned int i = 0; i < ms; i++) {
        pat = patts[i];
        m = pat.size();
        cur = 0;
        j = 0;
        while( j < m && (this->g).find({cur, pat[j]}) != (this->g).end()) {
            cur = (this->g)[{cur, pat[j]}];
            j += 1;
        }
        while (j < m) {
            nxt += 1;
            std::vector<uint_fast16_t> a;
            (this->o).push_back(a);
            (this->g)[{cur, pat[j]}] = nxt;
            cur = nxt;
            j += 1;
        }

        ((this->o)[cur]).push_back(i);
    }
    for (char s : this->ab) {
        if ((this->g).find({0, char(s)}) == (this->g).end()) {
            (this->g)[{0, s}] = 0;
        }
    }
    
    return nxt+1;
}

void Ahocorasick::build_fail(int n) {
    std::queue<uint_fast16_t> Q;
    (this->f).insert((this->f).begin(), n, 0);
    uint_fast16_t cur, nxt, brd;
    for (char s : this->ab) {
        if ((this->g)[{0, char(s)}] != 0) {
            Q.push((this->g)[{0, char(s)}]);
            (this->f)[(this->g)[{0, char(s)}]] = 0;
        }
    }
    while (Q.size() > 0){
        cur = Q.front();
        Q.pop();
        for (char s : this->ab) {
            if ((this->g).find({cur, char(s)}) != (this->g).end()) {
                nxt = (this->g)[{cur, char(s)}];
                Q.push(nxt);
                brd = (this->f)[cur];
                while((this->g).find({cur, char(s)}) == (this->g).end()) {
                    brd = (this->f)[brd];
                }
                (this->f)[nxt] = (this->g)[{brd, char(s)}];
                // for (auto a : this->o)
                // {
                //     for (auto b : a)
                //     {
                //         std::cout << b << ", ";
                //     }
                //     std::cout << " | ";
                // }
                std::cout << std::endl;
                for(auto a : (this->o)[(this->f)[nxt]]) {
                    (this->o)[nxt].push_back(a);
                }
            }
        }
    }
}

std::vector<std::vector<uint_fast16_t> > Ahocorasick::find(std::string text, std::vector<std::string> patts) {
    int n = text.size();
    std::vector<uint_fast16_t> m;
    std::vector<std::vector<uint_fast16_t> > occ;
    for (unsigned int i = 0; i != patts.size(); i++) {
        m.push_back(patts[i].size());
        std::vector<uint_fast16_t> a;
        occ.push_back(a);
    }
    uint_fast16_t cur = 0;
    char a;
    for(int i = 0; i < n; i ++){
        a = text[i];
        while ((this->g).find({cur, char(a)}) == (this->g).end()) {
            cur = (this->f)[cur];
        }
        cur = (this->g)[{cur, char(a)}];
        for (unsigned int j = 0; j != (this->o)[cur].size(); j++) {
            occ[(this->o)[cur][j]].push_back(i - m[(this->o)[cur][j]] + 1);
        }
    }
    return occ;
}