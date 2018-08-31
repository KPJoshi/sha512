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
  //read files to vectors
  //not good for big files
  const std::vector<byte> key  = readBinaryFileToVector(argv[1]);
  const std::vector<byte> data = readBinaryFileToVector(argv[2]);
  //get and print hmac
  const std::vector<byte> hmac = HMAC::hmac(key,data,SHA512::hash,128,64);
  Debug::printBytes(hmac,64);
  std::cout << "  " << argv[2] << std::endl;
  return 0;
}
