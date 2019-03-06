#include "PBKDF2.hpp"
#include "util.hpp"

byteArray PBKDF2::pbkdf2(HMACFunc hmac, word hmacLen, const byteArray& password, byteArray salt, word iterations, word outputSize) {
  byteArray output();
  output.reserve(outputSize);
  for(word i=0; output.size()<outputSize; ++i) {
    byteArray block();
    //construct first message from salt and block number
    for(word j=0; j<4; ++j)
      salt.push_back((i>>(24-(j<<3)))&0xff);
    byteArray unit();
    unit = hmac(password,salt);
    block = unit;
    for(word j=1; j<iterations; ++j) {
      unit = hmac(password,unit);
      for(word k=0; k<hmacLen; ++k)
        block[k] ^= unit[k];
    }
    output.insert(output.end(),block.begin(),block.end());
  }
  output.resize(outputSize);
  return output;
}
