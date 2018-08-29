#include <iostream>

#include "typedefs.hpp"
#include "SHA512.hpp"

inline word SHA512::rr(const word num, const word shift) {
  return (num>>shift)|(num<<(64-shift));
}

byte* SHA512::hash(const byte* data, const word length) {
  //assert length in bits can fit in uint64
  if(length>=0x2000000000000000UL)
    return nullptr;
  //initial hash values
  word h[8] = {0x6a09e667f3bcc908UL, 0xbb67ae8584caa73bUL, 0x3c6ef372fe94f82bUL, 0xa54ff53a5f1d36f1UL,
               0x510e527fade682d1UL, 0x9b05688c2b3e6c1fUL, 0x1f83d9abfb41bd6bUL, 0x5be0cd19137e2179UL};
  //word array; no need to initialize
  word w[80];
  //create padding: need 1 byte for the '1' bit at start, 16 bytes for size, rest should be 0
  word zeroPadLength;
  if((length&0x7f) <= 111)
    zeroPadLength = 111-(length&0x7f);
  else
    zeroPadLength = 239-(length&0x7f); //1 extra chunk required
  byte padding[zeroPadLength+17];
  padding[0] = 0x80;
  for(word i=1; i<=zeroPadLength+8; ++i) //assume top 8 bytes of size are also 0
    padding[i] = 0;
  word lengthInBits = length<<3;
  for(word i=0; i<8; ++i)
    padding[zeroPadLength+16-i] = (lengthInBits>>(i<<3))&0xff;
  //printf("%lu\n",zeroPadLength+17);
  //printBytes(padding,zeroPadLength+17);printf("\n");
  word totalLength = length+zeroPadLength+17;
  //main loop
  word offset=0;
  while(offset<totalLength) {
    //zero first 16 words in preparation of data copy
    for(word i=0; i<16; ++i)
      w[i] = 0;
    //copy data to word array
    for(word i=0; i<128; ++i) {
      word shift = (7-(i&0x07))<<3;
      word dataByte = (offset<length) ? data[offset] : padding[offset-length];
      //printf("%02lu %02lx %lu\n",shift,dataByte,offset);
      w[i>>3] |= dataByte<<shift;
      ++offset;
    }
    //printWords(w,16);printf("\n");
    //extend data in word array
    for(word i=16; i<80; ++i) {
      word s0 = rr(w[i-15],1)^rr(w[i-15],8)^(w[i-15]>>7);
      word s1 = rr(w[i-2],19)^rr(w[i-2],61)^(w[i-2]>>6);
      w[i] = w[i-16] + s0 + w[i-7] + s1;
    }
    //initialize working variables
    word l[8];
    for(word i=0; i<8; ++i)
      l[i] = h[i];
    //compression loop
    for(word i=0; i<80; ++i) {
      word S1 = rr(l[4],14)^rr(l[4],18)^rr(l[4],41);
      word ch = (l[4]&l[5])^((~l[4])&l[6]);
      word temp1 = l[7]+S1+ch+k[i]+w[i];
      word S0 = rr(l[0],28)^rr(l[0],34)^rr(l[0],39);
      word maj = (l[0]&l[1])^(l[0]&l[2])^(l[1]&l[2]);
      word temp2 = S0+maj;
      l[7] = l[6];
      l[6] = l[5];
      l[5] = l[4];
      l[4] = l[3]+temp1;
      l[3] = l[2];
      l[2] = l[1];
      l[1] = l[0];
      l[0] = temp1+temp2;
    }
    //add compressed chunk to hash
    for(word i=0; i<8; ++i)
      h[i] += l[i];
    //printWords(h,8);printf("\n");
  }
  //output
  byte* output = new byte[64];
  for(word i=0; i<64; ++i)
    output[i] = (h[i>>3]>>((7-(i&0x07))<<3))&0xff;
  return output;
}

void SHA512::printBytes(byte* list, word length) {
  for(int i=0; i<length; ++i)
    printf("%02x",list[i]);
}

void SHA512::printWords(word* list, word length) {
  for(int i=0; i<length; ++i)
    printf("%016lx\n",list[i]);
}
