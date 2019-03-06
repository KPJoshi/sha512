#ifndef PBKDF2_HPP
#define PBKDF2_HPP

#include <vector>

#include "util.hpp"

namespace PBKDF2 {

  byteArray pbkdf2(HMACFunc hmac, word hmacLen, const byteArray& password, byteArray salt, word iterations, word outputSize);

};

#endif //PBKDF2_HPP
