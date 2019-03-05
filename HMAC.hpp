#ifndef HMAC_HPP
#define HMAC_HPP

#include <vector>

#include "util.hpp"

namespace HMAC {

  std::vector<byte> hmac(std::vector<byte> key, const std::vector<byte>& message, HashFunc hash, word blockSize, word outputSize);

};

#endif //HMAC_HPP
