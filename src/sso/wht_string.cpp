#include "wht_string.h"

#include <cstring>

namespace wht {

string::string() {
  *local_ = '\0';
  data_ = local_;
}

string::string(const char* str) {
  *local_ = '\0';
  data_ = local_;
  size_t len =  str == nullptr ? 0 : strlen(str);
  if (len) {
    if (len + 1 > MAX_LOCAL_SIZE) {
      data_ = new char[len + 1];
    }
    strncpy(data_, str, len + 1);
    length_ = len;
  }
}

string::string(const string& obj) {
  data_ = local_;
  memcpy(local_, obj.local_, sizeof(local_));
  if (obj.length() + 1 > MAX_LOCAL_SIZE) {
  	data_ = new char [obj.length() + 1];
    strcpy(data_, obj.data());
  }
  length_ = obj.length();
}

string::string(string&& obj) {
  *local_ = '\0';
  data_ = local_;

  // swap local data
  char temp[MAX_LOCAL_SIZE];
  memcpy(temp, local_, sizeof(temp));
  memcpy(local_, obj.local_, sizeof(local_));
  memcpy(obj.local_, temp, sizeof(obj.local_));

  std::swap(length_, obj.length_);

  if (length_ + 1 > MAX_LOCAL_SIZE) {
    data_ = obj.data_;
    obj.data_ = obj.local_;
  }
}

string& string::operator=(const string& obj) {
  if (this == &obj) {
  	return *this;
  }
  clear();
  memcpy(local_, obj.local_, sizeof(local_));
  if (obj.length() + 1 > MAX_LOCAL_SIZE) {
  	data_ = new char[obj.length() + 1];
  	strcpy(data_, obj.data());
  }
  length_ = obj.length();
  return *this;
}

string& string::operator=(string&& obj) {
  if (this == &obj) {
  	return *this;
  }

  std::swap(data_, obj.data_);
  std::swap(length_, obj.length_);

  char temp[MAX_LOCAL_SIZE];
  memcpy(temp, local_, sizeof(temp));
  memcpy(local_, obj.local_, sizeof(local_));
  memcpy(obj.local_, temp, sizeof(obj.local_));

  if (length_ + 1 <= MAX_LOCAL_SIZE) {
  	data_ = local_;
  }
  if (obj.length_ + 1 <= MAX_LOCAL_SIZE) {
    obj.data_ = obj.local_;
  }

  return *this;
}

string::~string() {
  clear();
}

bool string::empty() const {
  return length() == 0;
}

size_t string::length() const {
  return length_;
}

const char* string::data() const {
  return data_;
}

const char* string::c_str() const {
  return data();
}

void string::clear() {
  if (data_ != local_) {
  	delete []data_;
  }
  data_ = local_;
  *local_ = '\0';
  length_ = 0;
}

std::ostream& operator << (std::ostream& lhs, const wht::string& rhs) {
  lhs << rhs.data();
  return lhs;
}

} // namespace wht
