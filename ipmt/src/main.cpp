#include <iostream>
#include "lz77.h"

int main () {
    LZ77 lz(7,4);
    std::string str = "cbacbacbcacbacbcaac";
    // lz.set_buffer_size(512, 128);
    // lz.set_buffer_size(511, 127);
    // lz.set_buffer_size(255, 127);
    // lz.set_buffer_size(256, 128);
    // lz.set_buffer_size(65535, 255);
    // lz.set_buffer_size(65535, 511);
    // lz.set_buffer_size(65535, 4095);
    // std::cout << "Encoding: " << str << std::endl;

    std::string input = lz.encode(str);
    // std::cout << "Encoded: " << input << std::endl;

    std::string output = lz.decode(input);
    // std::cout << "Decoded: " << output << std::endl;

    return 0;
}