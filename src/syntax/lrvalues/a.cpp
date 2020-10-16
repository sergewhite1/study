#include "a.h"

#include <cstring>
#include <iostream>

A::A() {
  std::cout << "A default ctor this = " << this << std::endl;
}

A::A(const A& aObj) {
  std::cout << "A copy ctor this = " << this << " aObj = " << aObj << std::endl;
  init(aObj.data());
}

A::A(A&& aObj) noexcept {
  std::cout << "A move ctor this = " << this << " aObj = " << aObj << std::endl;
  data_ = std::move(aObj.data_);
  std::swap(len_, aObj.len_);
}

A::~A() {
  std::cout << "A dtor this = " << this 
  << " data = " << *this  << " len = " << len_ << std::endl;
}

A& A::operator=(A&& aObj) {
  std::cout << "A move assign operator this = " << this << " &aObj = " << &aObj << " aObj" << aObj << std::endl;

  if (this == &aObj) {
    return *this;
  }

  std::swap(data_, aObj.data_);
  std::swap(len_, aObj.len_);

  return *this;
}

A::A(const char* str) {
  std::cout << "A ctor const char* this = " << this << " str = " << str << std::endl;
  init(str);
}

void A::setData(const char* str) {
  std::cout << "A::setData(const char* str). this = " << this << " str = " << str << std::endl;
  init(str);
}

std::ostream& operator<<(std::ostream& os, const A& aObj) {
  const char* ptr = aObj.data();
  os << (ptr ? ptr : "(empty)");
  return os;
}

void A::init(const char* str) {
  size_t len = strlen(str);
  data_.reset(new char[len+1]);
  strcpy(data_.get(), str);
  len_ = len;
}
