#include "lz77.h"

LZ77::LZ77()
{
    for (unsigned int i = 0; i < AB_SIZE_LZ77; i++)
    {
        this->ab += char(i);
    }
}

std::vector<unsigned int> LZ77::find(std::string text, std::string pat)
{
    
}