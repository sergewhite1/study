#include <algorithm>
#include <cstring>
#include <memory>
#include <iostream>

class MyString {
public:
  explicit MyString(const char* s) {
    std::cout << "MyString::MyString(const char* s). this = " << this << " s = " << s << std::endl;
    len_ = strlen(s);
    data_ = std::make_unique<char[]>(len_ + 1);
    memcpy(data_.get(), s, len_ + 1);
  }

  ~MyString() {
    std::cout << "MyString::~MyString() this = " << this << std::endl;
  }

  MyString(const MyString& myString) {
    std::cout << "MyString::MyString(const MyString& myString) this = " << this << " &myString = " << &myString
              << " c_str() = " << myString.c_str() << std::endl;
    data_ = std::make_unique<char[]>(myString.len_ + 1);
    memcpy(data_.get(), myString.data_.get(), myString.len_ + 1);
    len_ = myString.len_;
  }

  MyString(MyString&& myString) {
    std::cout << "MyString::MyString(MyString&& myString) this = " << this << " &myString = " << &myString;
    std::swap(data_, myString.data_);
    std::swap(len_, myString.len_);
  }

  MyString& operator=(const MyString&) = delete;
  MyString& operator=(MyString&&) = delete;

  const char* c_str() const {
    return data_.get();
  }

  size_t len() const {
    return len_;
  }

  void append(const char* s) {
    size_t s_len = strlen(s);
    size_t new_len = len_ + s_len;
    auto new_data = std::make_unique<char[]>(new_len + 1);
    memcpy(new_data.get(), data_.get(), len_);
    memcpy(&new_data.get()[len_], s, s_len + 1);
    data_ = std::move(new_data);
    len_ = new_len;
  }

private:
  std::unique_ptr<char[]> data_ = nullptr;
  size_t len_ = 0;
};

//static void f(MyString s) {
//  std::cout << "void f(MyString s) s = " << s.c_str() << std::endl;
//}

static void f(const MyString& s) {
  std::cout << "void f(const MyString& s). s = " << s.c_str() << std::endl;
}

static void f(MyString&& s) {
  std::cout << "void f(MyString&& s). s = " << s.c_str() << std::endl;
  s.append("AFTER &&");
}

static void h(std::string&& s) {
  std::cout << "void h(std::string&& s) s = " << s << std::endl;
  s += "AAAAA";
  std::cout << "s=" << s << std::endl;
}

int main() {
  MyString s("hello");
  std::cout << s.c_str() << std::endl;

  //f(s);
  f(std::move(s));

  std::cout << "s = " << s.c_str() << std::endl;

  std::string s1 = "My name is ";
  std::string s2 = "W";
  h(s1 + s2);
}
