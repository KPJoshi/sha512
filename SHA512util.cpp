#include <iostream>

#include "SHA512.hpp"
#include "util.hpp"

int main(int argc, char* argv[]) {
  if(argc!=2) {
    std::cout << "Usage: " << argv[0] << " FILE\n";
    return 0;
  }
  //read file to vector
  //not good for big files
  const byteArray data = readBinaryFileToVector(argv[1]);
  //get and print hash
  const byteArray hash = SHA512::hash(data);
  Debug::printBytes(hash,64);
  std::cout << "  " << argv[1] << std::endl;
  return 0;
}
