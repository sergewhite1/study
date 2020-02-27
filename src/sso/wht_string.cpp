#include "wht_string.h"

namespace wht {

string::string() {
}

string::string(const char* str) {
  //TODO: wht::string ctor
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

bool string::empty() const {
	return empty_;
}


size_t string::length() const {
	//TODO: wht::string::length
	return 0;
}

const char* string::data() const {
	//TODO: wht::string::data
	return nullptr;
}

const char* string::c_str() const {
	//TODO: wht::string::c_str
}

std::ostream& operator << (std::ostream& rhs, const wht::string& lhs) {
  //TODO:  std::ostream& operator << (std::ostream& rhs, const wht::string& lhs)
  rhs << "AAAA!!!";
  return rhs;
}

} // namespace wht
