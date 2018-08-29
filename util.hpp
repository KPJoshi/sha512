#include <cstdint>
#include <vector>

typedef uint8_t byte;
typedef uint64_t word;

namespace Debug {

  void printWords(const std::vector<word>& list, const word length);

  void printBytes(const std::vector<byte>& list, const word length);

}
