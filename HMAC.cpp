#include <vector>

#include "HMAC.hpp"
#include "util.hpp"

std::vector<byte> HMAC::hmac(std::vector<byte> key, const std::vector<byte>& message, HashFunc hash, word blockSize, word outputSize) {
  //if key too long: hash it
  if(key.size() > blockSize)
    key = hash(key);
  if(key.size() < blockSize)
    key.resize(blockSize,0);
  //Debug::printBytes(key,key.size());printf("\n");
  std::vector<byte> opad(key);
  std::vector<byte> ipad(key);
  for(word i=0; i<blockSize; ++i) {
    opad[i] ^= 0x5c;
    ipad[i] ^= 0x36;
  }
  //Debug::printBytes(ipad,ipad.size());printf("\n");
  //Debug::printBytes(opad,opad.size());printf("\n");
  ipad.reserve(blockSize+message.size());
  ipad.insert(ipad.end(),message.begin(),message.end());
  //Debug::printBytes(ipad,ipad.size());printf("\n");
  const std::vector<byte> innerHash = hash(ipad);
  //Debug::printBytes(innerHash,innerHash.size());printf("\n");
  opad.reserve(blockSize+outputSize);
  opad.insert(opad.end(),innerHash.begin(),innerHash.end());
  //Debug::printBytes(opad,opad.size());printf("\n");
  return hash(opad);
}
