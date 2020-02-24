#include "wht_string.h"

namespace wht {

string::string(const char* str) {
  //TODO: wht::string ctor
}

std::ostream& operator << (std::ostream& rhs, const wht::string& lhs) {
  //TODO:  std::ostream& operator << (std::ostream& rhs, const wht::string& lhs)
  rhs << "AAAA!!!";
  return rhs;
}

} // namespace wht
