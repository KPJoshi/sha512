#include <fstream>
#include <iostream>

#include "typedefs.hpp"
#include "SHA512.hpp"

int main(int argc, char* argv[]) {
  if(argc!=2) {
    std::cout << "Usage: " << argv[0] << " FILE\n";
    return 0;
  }
  //read file
  //not good for big files
  std::ifstream ifs(argv[1], std::ios::binary|std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();
  unsigned long dataLen = pos;
  byte* data = new byte[dataLen];
  ifs.seekg(0, std::ios::beg);
  ifs.read((char*)data,dataLen);
  ifs.close();
  //get and print hash
  byte* hash = SHA512::hash(data,dataLen);
  SHA512::printBytes(hash,64);
  std::cout << "  " << argv[1] << std::endl;
  delete[] data;
  delete[] hash;
  return 0;
}
