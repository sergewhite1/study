#include <ostream>

namespace wht{

class string {
public:
	string();
  explicit string(const char* str);
  bool empty() const;

private:
	bool empty_ = true;
};

std::ostream& operator << (std::ostream& rhs, const wht::string& lhs);

} // namespace wht
