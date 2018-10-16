#include "ahocorasick.h"


Ahocorasick::Ahocorasick()
{
    for (unsigned int i = 0; i < AB_SIZE; i++)
    {
        this->ab += char(i);
    }
}

void Ahocorasick::build_fsm(std::vector<std::string> patts)  {
    uint_fast16_t n = this->build_goto(patts);
    this->build_fail(patts, n);
}

uint_fast16_t Ahocorasick::build_goto(std::vector<std::string> patts) {
    unsigned int ms = patts.size();
    uint_fast16_t nxt = 0;
    uint_fast16_t m, cur, j;
    std::string pat;
    for(int i = 0; i < ms; i++) {
        pat = patts[i];
        m = pat.size();
        cur = 0;
        j = 0;
        while( j < m && (this->g).find(std::make_pair(cur, pat[j])) != (this->g).end) {
            cur = (this->g)[std::make_pair(cur, pat[j])];
            j += 1;
        }
        while (j < m) {
            nxt += 1;
            std::vector<uint_fast16_t> a;
            (this->o).push_back(a);
            (this->g)[std::make_pair(cur, pat[j])] = nxt;
            cur = nxt;
            j += 1;
        }
        ((this->o)[cur]).push_back(i);
    }
    for (char &s : this->ab) {
        if ((this->g).find(std::make_pair(0, char(s))) == (this->g).end) {
            (this->g)[{0, s}] = 0;
        }
    }
    return nxt;
}

void Ahocorasick::build_fail(std::vector<std::string> patts, int n) {
    std::queue<uint_fast16_t> Q;
    (this->f).insert((this->f).begin(), n, 0);
    uint_fast16_t cur, nxt, brd;
    for (char &s : this->ab) {
        if ((this->g)[std::make_pair(0, char(s))] != 0) {
            Q.push((this->g)[std::make_pair(0, char(s))]);
            (this->f)[(this->g)[std::make_pair(0, char(s))]] = 0;
        }
    }
    while (Q.size() > 0) {
        cur = Q.front();
        Q.pop();
        for (char &s : this->ab){
            if ((this->g)[std::make_pair(cur, char(s))] != (this->g).end) {
                nxt = (this->g)[std::make_pair(cur, char(s))];
                Q.push(nxt);
                brd = (this->f)[cur];
                while((this->g)[std::make_pair(cur, char(s))] == (this->g).end) {
                    brd = (this->f)[brd];
                }
                (this->f)[nxt] = (this->g)[std::make_pair(brd, char(s))];
                std::copy((this->o)[nxt].begin(), (this->o)[nxt].end(), std::back_inserter((this->o)[(this->f)[nxt]]));
            }
        }
    }
}

std::vector<std::vector<uint_fast16_t>> Ahocorasick::find(std::string text, std::vector<std::string> patts) {
    int n = text.size();
    std::vector<uint_fast16_t> m;
    std::vector<std::vector<uint_fast16_t>> occ;
    for (int i = 0; i != patts.size(); i++) {
        m.push_back(patts[i].size());
        std::vector<uint_fast16_t> a;
        occ.push_back(a);
    }
    uint_fast16_t cur = 0;
    char a;
    for(int i = 0; i < n; i ++){
        a = text[i];
        while ((this->g)[std::make_pair(cur, char(a))] == (this->g).end) {
        cur = (this->f)[cur];
        }
        cur = (this->g)[std::make_pair(cur, char(a))];
        for (int j = 0; j != (this->o)[cur].size(); j++) {
            occ[(this->o)[cur][j]].push_back(i - m[(this->o)[cur][j]] + 1);
        }
    }
    return occ;
}