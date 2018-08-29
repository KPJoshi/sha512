#include <cstring>
#include <fstream>
#include <iostream>

#include "HMAC.hpp"
#include "SHA512.hpp"
#include "util.hpp"

int main(int argc, char* argv[]) {
  if(argc!=3) {
    std::cout << "Usage: " << argv[0] << " KEY FILE\n";
    return 0;
  }
  //read file
  //not good for big files
  std::ifstream ifs(argv[2], std::ios::binary|std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();
  std::size_t dataLen = static_cast<std::size_t>(pos);
  std::vector<byte> data(dataLen);
  ifs.seekg(0, std::ios::beg);
  ifs.read(reinterpret_cast<char*>(&data.front()),dataLen);
  ifs.close();
  //get and print hash
  std::vector<byte> key;
  key.assign(argv[1],argv[1]+strlen(argv[1]));
  std::vector<byte> hash = HMAC::hmac(key,data,SHA512::hash,128,64);
  Debug::printBytes(hash,64);
  std::cout << "  " << argv[2] << std::endl;
  return 0;
}
