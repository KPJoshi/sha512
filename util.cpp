#include <fstream>
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

std::vector<byte> readBinaryFileToVector(const char* fileName) {
  std::ifstream ifs(fileName, std::ios::binary|std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();
  const std::size_t dataLen = static_cast<std::size_t>(pos);
  std::vector<byte> data(dataLen);
  ifs.seekg(0, std::ios::beg);
  ifs.read(reinterpret_cast<char*>(&data.front()),dataLen);
  //not necessary, just being thorough
  ifs.close();
  return data;
}
