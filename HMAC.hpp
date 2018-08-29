#include <vector>

#include "util.hpp"

namespace HMAC {

  std::vector<byte> hmac(std::vector<byte> key,
                         const std::vector<byte>& message,
                         std::vector<byte> (*hash)(const std::vector<byte>&),
                         word blockSize, word outputSize);

};
