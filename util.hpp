#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>
#include <vector>

typedef uint8_t byte;
typedef uint64_t word;

typedef std::vector<byte> (*HashFunc)(const std::vector<byte>&);

namespace Debug {

  void printWords(const std::vector<word>& list, const word length);

  void printBytes(const std::vector<byte>& list, const word length);

}

std::vector<byte> readBinaryFileToVector(const char* fileName);

#endif //UTIL_HPP
