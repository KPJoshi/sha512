#ifndef HMAC_HPP
#define HMAC_HPP

#include "util.hpp"

namespace HMAC {

  byteArray hmac(byteArray key, const byteArray& message, HashFunc hash, word blockSize, word outputSize);

};

#endif //HMAC_HPP
