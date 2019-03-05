#ifndef PBKDF2_HPP
#define PBKDF2_HPP

#include <vector>

#include "util.hpp"

namespace PBKDF2 {

  std::vector<byte> pbkdf2(HMACFunc hmac, std::vector<byte> password, std::vector<byte> salt, word iterations, word outputSize);

};

#endif //PBKDF2_HPP
