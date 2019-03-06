#include <iostream>
#include <string>

#include "HMAC.hpp"
#include "PBKDF2.hpp"
#include "SHA512.hpp"
#include "util.hpp"

byteArray HMAC_SHA512(const byteArray& key, const byteArray& data) {
  return HMAC::hmac(key,data,SHA512::hash,128,64);
}

int main(int argc, char* argv[]) {
  if(argc!=5) {
    std::cout << "Usage: " << argv[0] << " PASSWORD SALT ITERATIONS OUTPUTLENGTH\n";
    return 0;
  }
  //read files to vectors
  //not good for big files
  const byteArray password  = readBinaryFileToVector(argv[1]);
  const byteArray salt = readBinaryFileToVector(argv[2]);
  //read other arguments
  const word iterations = std::stoul(argv[3]);
  const word outputLength = std::stoul(argv[4]);
  //derive key and print
  const byteArray key = PBKDF2::pbkdf2(HMAC_SHA512,64,password,salt,iterations,outputLength);
  Debug::printBytes(key,outputLength);
  std::cout << std::endl;
  return 0;
}
