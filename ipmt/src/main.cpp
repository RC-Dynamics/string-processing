#include <iostream>
#include "lz77.h"

int main () {
    LZ77 lz(7,4);
    std::string str = "cbacbacbcacbacbcaac";
    std::cout << "Encoding: " << str << std::endl;

    std::string input = lz.encode(str);
    std::cout << "Encoded: " << input << std::endl;

    std::string output = lz.decode(input);
    std::cout << "Decoded: " << output << std::endl;

    return 0;
}