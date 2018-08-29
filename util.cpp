#include <iostream>
#include <vector>

#include "util.hpp"

void Debug::printBytes(const std::vector<byte>& list, const word length) {
  for(int i=0; i<length; ++i)
    printf("%02x",list[i]);
}

void Debug::printWords(const std::vector<word>& list, const word length) {
  for(int i=0; i<length; ++i)
    printf("%016lx\n",list[i]);
}
