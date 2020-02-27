#include <ostream>

namespace wht{

class string {
public:
	string();
  explicit string(const char* str);
  string(const string&);
  string(string&&);
  string& operator=(const string&);
  string& operator=(string&&);

  bool empty() const;
  size_t length() const;
  const char* data() const;
  const char* c_str() const;

private:
	bool empty_ = true;
};

std::ostream& operator << (std::ostream& rhs, const wht::string& lhs);

} // namespace wht
