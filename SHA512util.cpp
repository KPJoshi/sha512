#include <fstream>
#include <iostream>

#include "SHA512.hpp"
#include "util.hpp"

int main(int argc, char* argv[]) {
  if(argc!=2) {
    std::cout << "Usage: " << argv[0] << " FILE\n";
    return 0;
  }
  //read file
  //not good for big files
  std::ifstream ifs(argv[1], std::ios::binary|std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();
  std::size_t dataLen = static_cast<std::size_t>(pos);
  std::vector<byte> data(dataLen);
  ifs.seekg(0, std::ios::beg);
  ifs.read(reinterpret_cast<char*>(&data.front()),dataLen);
  ifs.close();
  //get and print hash
  std::vector<byte> hash = SHA512::hash(data);
  Debug::printBytes(hash,64);
  std::cout << "  " << argv[1] << std::endl;
  return 0;
}
