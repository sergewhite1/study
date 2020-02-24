#include <ostream>

namespace wht{

class string {
public:
  explicit string(const char* str);
};

std::ostream& operator << (std::ostream& rhs, const wht::string& lhs);

} // namespace wht
