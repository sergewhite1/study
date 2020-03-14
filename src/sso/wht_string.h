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
  static const size_t MAX_LOCAL_SIZE = 31;
  
private:
  union {
    struct {
      char *data_;  
      size_t length_;
    } long_string_;
    struct {
      char data_[MAX_LOCAL_SIZE];

      // for short string 0..MAX_LOCAL_SIZE - 1
      // for long string 0xFF
      unsigned char length_;
    } short_string_;
  } data_;
  static_assert(sizeof(data_.short_string_) > sizeof(data_.long_string_));

  void assign(const string& obj);
  bool is_local() const;
};

std::ostream& operator << (std::ostream& lhs, const wht::string& rhs);

} // namespace wht
