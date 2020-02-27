#include "wht_string.h"

#include <cstring>

namespace wht {

string::string() {
	*local_ = '\0';
  data_ = local_;
}

string::string(const char* str) {
  size_t len = strlen(str);
  if (len == 0) {
    *local_ = '\0';
    data_ = local_;
  } else {
    if (len + 1 >= MAX_LOCAL_SIZE) {
      data_ = new char[len + 1];
    }
    strncpy(data_, str, len + 1);
    length_ = len;
  }
}

string::string(const string& obj) {
	//TODO: wht::string copy ctor
}

string::string(string&& obj) {
	//TODO: wht::string move ctor
}

string& string::operator=(const string& obj) {
	//TODO: wht::string operator=
	return *this;
}

string& string::operator=(string&& obj) {
	//TODO: wht::string move operator=
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
		data_ = local_;
   *local_ = '\0';
	}
}

std::ostream& operator << (std::ostream& lhs, const wht::string& rhs) {
  lhs << rhs.data();
  return lhs;
}

} // namespace wht
