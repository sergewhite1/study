#include "wht_string.h"

#include <cstring>

namespace wht {

string::string() {
  memset(&data_, 0 , sizeof(data_));
}

string::string(const char* str) {
  memset(&data_, 0, sizeof(data_));
  size_t len =  str == nullptr ? 0 : strlen(str);
  if (len) {
    if (len + 1 <= MAX_LOCAL_SIZE) {
     strncpy(data_.short_string_.data_, str, len + 1);
     data_.short_string_.length_ = static_cast<unsigned char>(len);
    } else {
      data_.long_string_.data_ = new char[len + 1];
      strncpy(data_.long_string_.data_, str, len + 1);
      data_.long_string_.length_ = len;
      data_.short_string_.length_ = 0xFF;
    }
  }
}

string::string(const string& obj) {
  if (obj.is_local()) {
    data_ = obj.data_;
  } else {
    data_.long_string_.data_ = new char[obj.length() + 1];
    strncpy(data_.long_string_.data_, obj.data_.long_string_.data_, 
      obj.length() + 1);
    data_.long_string_.length_ = obj.length();
    data_.short_string_.length_ = 0xFF;
  }
}

string::string(string&& obj) {
 std::swap(data_, obj.data_);
}

string& string::operator=(const string& obj) {
  if (this == &obj) {
    return *this;
  }

  clear();

  if(obj.is_local()) {
    data_ = obj.data_;
  } else {
    data_.long_string_.data_ = new char[obj.length() + 1];
    strncpy(data_.long_string_.data_, obj.data_.long_string_.data_, 
      obj.length() + 1);
    data_.long_string_.length_ = obj.length();
    data_.short_string_.length_ = 0xFF;
  }

  return *this;
}

string& string::operator=(string&& obj) {
  if (this == &obj) {
  	return *this;
  }
  
  std::swap(data_, obj.data_);

  return *this;
}

string::~string() {
  clear();
}

bool string::empty() const {
  return length() == 0;
}

size_t string::length() const {
  return is_local() ? data_.short_string_.length_ : data_.long_string_.length_;
}

const char* string::data() const {
  return is_local() ? data_.short_string_.data_ : data_.long_string_.data_;
}

const char* string::c_str() const {
  return data();
}

void string::clear() {
  if (is_local()) {
   *data_.short_string_.data_ = '\0';
  } else {
    delete []data_.long_string_.data_;
    data_.long_string_.data_ = nullptr;
    data_.long_string_.length_ = 0;
  }

  data_.short_string_.length_ = 0;
}

bool string::is_local() const {
  return data_.short_string_.length_ != 0xFF;
}

std::ostream& operator << (std::ostream& lhs, const wht::string& rhs) {
  lhs << rhs.data();
  return lhs;
}

} // namespace wht
