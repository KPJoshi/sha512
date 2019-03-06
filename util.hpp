#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>
#include <vector>

typedef uint8_t byte;
typedef uint64_t word;

typedef std::vector<byte> byteArray;

typedef byteArray (*HashFunc)(const byteArray&);

typedef byteArray (*HMACFunc)(const byteArray&, const byteArray&);

namespace Debug {

  void printWords(const std::vector<word>& list, const word length);

  void printBytes(const byteArray& list, const word length);

}

byteArray readBinaryFileToVector(const char* fileName);

#endif //UTIL_HPP
