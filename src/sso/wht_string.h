#include <ostream>

namespace wht {

class string {
public:
	string();
  explicit string(const char* str);
  string(const string&);
  string(string&&);
  string& operator=(const string&);
  string& operator=(string&&);
  ~string();

  bool empty() const;
  size_t length() const;
  const char* data() const;
  const char* c_str() const;
  void clear();

private:
#ifdef WHT_STRING_TESTING
public:
#endif
  static const size_t MAX_LOCAL_SIZE = 32;

private:
	char *data_;  
  size_t length_ = 0;
	char local_[MAX_LOCAL_SIZE];
};

std::ostream& operator << (std::ostream& lhs, const wht::string& rhs);

} // namespace wht
