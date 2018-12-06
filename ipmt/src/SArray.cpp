#include "SArray.h"

SArray::SArray(){
}

void SArray::init(char *txt){
    this->txt = txt;
    n = (int)strlen(txt);
    l = (int)ceil(log2(n));
    this->build_hash();    
    this->build_prefix();
    this->sa_invert();

    #if DEBUG_SARRAY
    std::cout << "SA: ";
    for(int i = 0; i < n; ++i) {
        std::cout << this->SArr[i] << " ";
    }
    std::cout << std::endl;
    #endif

    this->lr_lcp();


    #if DEBUG_SARRAY
    std::cout << "Llcp: ";
    for(int i = 0; i < n; ++i) {
        std::cout << this->Llcp[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Rlcp: ";
    for(int i = 0; i < n; ++i) {
        std::cout << this->Rlcp[i] << " ";
    }
    std::cout << std::endl;
    #endif
    
}

int SArray::search(char *pat, bool print){
    int lft = this->succ2(pat);
    int rgt = this->pred2(pat);
    #if DEBUG_SARRAY
    std::cout << lft << " " << rgt << std::endl;
    #endif
    if(lft > rgt)
        return 0;
    else{
        if (print)
        {
            this->print_lines(lft, rgt);
        }
        return rgt - lft + 1;
    }

}

int SArray::succ2(char* pat){
    int m = strlen(pat);
    int L = this->lcp_bf(pat, this->txt + this->SArr[0]);
    int R = this->lcp_bf(pat, this->txt + this->SArr[this->n - 1]);
    if(R < m && this->txt[this->SArr[n-1] + R] < pat[R]) // lt_m
        return n;
    else if(L == m || this->txt[this->SArr[0] + L] > pat[L]) // leq_m
        return 0;
    else {
        int left = 0;
        int right = this->n -1;
        while(right - left > 1){
            int H = -1;
            int h = (left+right)/2;
            // #ifdef DEBUG_SARRAY
            // std::cout << "l= " << left << "  suf_l: " << this->txt[this->SArr[left]] << std::endl;
            // std::cout << "h= " << h << "  suf_h: " << this->txt[this->SArr[h]] << std::endl;
            // std::cout << "r= " << right << "  suf_r: " << this->txt[this->SArr[right]] << std::endl;
            // #endif

            if(L >= R){
                if(this->Llcp[h] > L){
                    left = h;
                }
                else if (this->Llcp[h] < L){
                    right = h;
                    R = this->Llcp[h];
                }
                else {
                    H = L + this->lcp_bf(pat + L, this->txt + this->SArr[h] + L);
                    if(H < m && H < (this->n - this->SArr[h]) && this->txt[this->SArr[h] + H] < pat[H]){
                        left = h;
                        L = H;
                    } else {
                        right = h;
                        R = H;
                    }
                }
            } else {
                if(this->Rlcp[h] > R){
                    right = h;
                } else if(this->Rlcp[h] < R){
                    left = h;
                    L = this->Rlcp[h];
                } else {
                    H = R + this->lcp_bf(pat + R, txt + this->SArr[h] + R);
                    if(H < m && H < (this->n - this->SArr[h]) && this->txt[this->SArr[h]+H] < pat[H]){
                        left = h;
                        L = H;
                    } else {
                        right = h;
                        R = H;
                    }
                }
            }
        }
        return right;
    }
}

int SArray::pred2(char* pat){
    int m = strlen(pat);
    int L = this->lcp_bf(pat, this->txt + this->SArr[0]);
    int R = this->lcp_bf(pat, this->txt + this->SArr[this->n - 1]);
    if(R == m || this->txt[this->SArr[n-1] + R] < pat[R]){ // lt_m
        return n - 1;
    }
    else if(L < m && this->txt[this->SArr[0] + L] > pat[L]){  // leq_m
        return -1;
    }
    else {
        int left = 0;
        int right = this->n -1;
        while(right - left > 1){
            int H = -1;
            int h = (left+right)/2;
            
            // #ifdef DEBUG_SARRAY
            // std::cout << "l= " << left << "  suf_l: " << this->txt[this->SArr[left]] << std::endl;
            // std::cout << "h= " << h << "  suf_h: " << this->txt[this->SArr[h]] << std::endl;
            // std::cout << "r= " << right << "  suf_r: " << this->txt[this->SArr[right]] << std::endl;
            // #endif

            if(L >= R){
                if(this->Llcp[h] > L){
                    left = h;
                }
                else if (this->Llcp[h] < L){
                    right = h;
                    R = this->Llcp[h];
                }
                else {
                    H = L + this->lcp_bf(pat + L, this->txt + this->SArr[h] + L);
                    if(H < m && H < (this->n - this->SArr[h]) && this->txt[this->SArr[h] + H] > pat[H]){
                        right = h;
                        R = H;
                    } else {
                        left = h;
                        L = H;
                    }
                }
            } else {
                if(this->Rlcp[h] > R){
                    right = h;
                } else if(this->Rlcp[h] < R){
                    left = h;
                    L = this->Rlcp[h];
                } else {
                    H = R + this->lcp_bf(pat + R, txt + this->SArr[h] + R);
                    if(H < m && H < (this->n - this->SArr[h]) && this->txt[this->SArr[h]+H] > pat[H]){
                        right = h;
                        R = H;
                    } else {
                        left = h;
                        L = H;
                    }
                }
            }
        }
        return left;
    }
}

void SArray::build_prefix(){
    this->P.assign(l + 1, std::vector<int>(n, -1));
    for(int i = 0; i < this->n; i++) {
      unsigned char ch = txt[i];
      this->P[0][i] = this->hash[ch];
    }
    for(int k = 1; k < l+1; k++){
        int j = pow(2, k-1);
        std::vector<std::tuple<int, int, int> > V;
        for(int i = 0; i < n; i++) {
            if(i + j >= n)
                V.push_back({this->P[k - 1][i], -1, i});
            else
                V.push_back({this->P[k - 1][i], this->P[k - 1][i + j], i});
        }
        std::sort(V.begin(), V.end());
        int r = 0;
        this->P[k][std::get<2>(V[0])] = r;
        for(int i = 1; i < n; i++) {
            if(std::get<0>(V[i]) != std::get<0>(V[i - 1]) || std::get<1>(V[i]) != std::get<1>(V[i - 1])) {
                r += 1;
            }
            this->P[k][std::get<2>(V[i])] = r;
        }
        #if DEBUG_SARRAY
        std::cout << "Pk: ";
        for(int i = 0; i < n; i++) {
            std::cout << this->P[k][i] << " ";
        }
        std::cout << std::endl;
        #endif
    }   
}

void SArray::sa_invert() {
    this->SArr.assign(n, -1);
    for(int i = 0; i < n; ++i) {
      this->SArr[this->P[this->l][i]] = i;
      
    }
}

void SArray::lr_lcp() {
    Llcp.assign(this->n, 0);
    Rlcp.assign(this->n, 0);
    fill_lrlcp(0, this->n - 1);
}

void SArray::fill_lrlcp(int left, int right) {
    if(right - left > 1) {
      int h = (left + right)/2;
      Llcp[h] = lcp_p(SArr[left], SArr[h]);
      Rlcp[h] = lcp_p(SArr[right], SArr[h]);
      fill_lrlcp(left, h);
      fill_lrlcp(h, right);
    }
}

int SArray::lcp_bf(char* X, char* Y){
    int m = strlen(X);
    int n = strlen(Y);
    int i = 0;
    while (i < m && i < n && X[i]==Y[i])
        i+=1;
    return i;
}

int SArray::lcp_p(int i, int j) {
    #if DEBUG_SARRAY
    // std::cout << "computing lcp i= " << i <<  " j= "  << j << std::endl;
    #endif
    int lcp = 0;
    if(i == j)
      return (n - i);
    else {
        for(int k = this->l; k >= 0; k--) {
            if(i > this->n || j > this->n)
                break;
            if(P[k][i] == P[k][j]) {
                lcp += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
    }
    return lcp;
  }


void SArray::build_hash() {
  std::vector<int> count(256, 0);
  for (int i = 0; i < n; ++i) {
    unsigned char ch = txt[i];
    count[ch] = 1;
  }
  for (int i = 1; i < 256; ++i) {
    count[i] += count[i - 1];
  }
  for (int i = 0; i < n; ++i) {
    unsigned char ch = txt[i];
    this->hash[ch] = count[ch] - 1;
  }
}

void SArray::print_lines(int lft, int rgt){
    for (int i = lft; i <= rgt; i++)
    {
        int match_start = this->SArr[i];
        int line_start = match_start;

        while (line_start > 0)
        {
            if (this->txt[line_start] == '\n')
            {
                line_start++;
                break;
            }
            line_start--;
        }
        int line_end = match_start;
        while (line_end < this->n)
        {
            if (this->txt[line_end] == '\n')
            {
                line_end--;
                break;
            }
            line_end++;
        }
        std::string line(this->txt + line_start, this->txt + line_end + 1);
        printf("%s\n", line.c_str());
    }
}

#if DEBUG_SARRAY
char text[200] = "hello world hell llo";
char patt[100] = "hello";
int main(){
    // scanf(" %s", text);
    SArray suffixArray(text);
    // scanf(" %s", patt);
    int idx = suffixArray.search(patt);
    std::cout << "Found: " << idx << std::endl;

}
#endif