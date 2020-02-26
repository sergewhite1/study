#include "wht_string.h"

namespace wht {

string::string() {
}

string::string(const char* str) {
  //TODO: wht::string ctor
}

bool string::empty() const {
	return empty_;
}

std::ostream& operator << (std::ostream& rhs, const wht::string& lhs) {
  //TODO:  std::ostream& operator << (std::ostream& rhs, const wht::string& lhs)
  rhs << "AAAA!!!";
  return rhs;
}

} // namespace wht
