#include <iostream>
#include <vector>

#include "SHA512.hpp"
#include "util.hpp"

//round constants
const word SHA512::k[80] = {0x428a2f98d728ae22UL, 0x7137449123ef65cdUL, 0xb5c0fbcfec4d3b2fUL, 0xe9b5dba58189dbbcUL, 0x3956c25bf348b538UL,
                            0x59f111f1b605d019UL, 0x923f82a4af194f9bUL, 0xab1c5ed5da6d8118UL, 0xd807aa98a3030242UL, 0x12835b0145706fbeUL,
                            0x243185be4ee4b28cUL, 0x550c7dc3d5ffb4e2UL, 0x72be5d74f27b896fUL, 0x80deb1fe3b1696b1UL, 0x9bdc06a725c71235UL,
                            0xc19bf174cf692694UL, 0xe49b69c19ef14ad2UL, 0xefbe4786384f25e3UL, 0x0fc19dc68b8cd5b5UL, 0x240ca1cc77ac9c65UL,
                            0x2de92c6f592b0275UL, 0x4a7484aa6ea6e483UL, 0x5cb0a9dcbd41fbd4UL, 0x76f988da831153b5UL, 0x983e5152ee66dfabUL,
                            0xa831c66d2db43210UL, 0xb00327c898fb213fUL, 0xbf597fc7beef0ee4UL, 0xc6e00bf33da88fc2UL, 0xd5a79147930aa725UL,
                            0x06ca6351e003826fUL, 0x142929670a0e6e70UL, 0x27b70a8546d22ffcUL, 0x2e1b21385c26c926UL, 0x4d2c6dfc5ac42aedUL,
                            0x53380d139d95b3dfUL, 0x650a73548baf63deUL, 0x766a0abb3c77b2a8UL, 0x81c2c92e47edaee6UL, 0x92722c851482353bUL,
                            0xa2bfe8a14cf10364UL, 0xa81a664bbc423001UL, 0xc24b8b70d0f89791UL, 0xc76c51a30654be30UL, 0xd192e819d6ef5218UL,
                            0xd69906245565a910UL, 0xf40e35855771202aUL, 0x106aa07032bbd1b8UL, 0x19a4c116b8d2d0c8UL, 0x1e376c085141ab53UL,
                            0x2748774cdf8eeb99UL, 0x34b0bcb5e19b48a8UL, 0x391c0cb3c5c95a63UL, 0x4ed8aa4ae3418acbUL, 0x5b9cca4f7763e373UL,
                            0x682e6ff3d6b2b8a3UL, 0x748f82ee5defb2fcUL, 0x78a5636f43172f60UL, 0x84c87814a1f0ab72UL, 0x8cc702081a6439ecUL,
                            0x90befffa23631e28UL, 0xa4506cebde82bde9UL, 0xbef9a3f7b2c67915UL, 0xc67178f2e372532bUL, 0xca273eceea26619cUL,
                            0xd186b8c721c0c207UL, 0xeada7dd6cde0eb1eUL, 0xf57d4f7fee6ed178UL, 0x06f067aa72176fbaUL, 0x0a637dc5a2c898a6UL,
                            0x113f9804bef90daeUL, 0x1b710b35131c471bUL, 0x28db77f523047d84UL, 0x32caab7b40c72493UL, 0x3c9ebe0a15c9bebcUL,
                            0x431d67c49c100d4cUL, 0x4cc5d4becb3e42b6UL, 0x597f299cfc657e2aUL, 0x5fcb6fab3ad6faecUL, 0x6c44198c4a475817UL};

inline word SHA512::rr(const word num, const word shift) {
  return (num>>shift)|(num<<(64-shift));
}

std::vector<byte> SHA512::hash(const std::vector<byte>& data) {
  const word length = data.size();
  //assert length in bits can fit in uint64
  if(length>=0x2000000000000000UL)
    return std::vector<byte>();
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
  //Debug::printBytes(padding,zeroPadLength+17);printf("\n");
  const word totalLength = length+zeroPadLength+17;
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
    //Debug::printWords(w,16);printf("\n");
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
    //Debug::printWords(h,8);printf("\n");
  }
  //output
  std::vector<byte> output(64);
  for(word i=0; i<64; ++i)
    output[i] = (h[i>>3]>>((7-(i&0x07))<<3))&0xff;
  return output;
}
