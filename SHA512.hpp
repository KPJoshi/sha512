#ifndef SHA512_HPP
#define SHA512_HPP

#include <vector>

#include "util.hpp"

class SHA512 {

  //round constants
  static const word k[80];

  static inline word rr(const word num, const word shift);

public:

  static std::vector<byte> hash(const std::vector<byte>& data);

};

#endif //SHA512_HPP
