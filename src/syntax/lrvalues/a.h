#ifndef A_H_
#define A_H_

#include <iostream>
#include <memory>

class A {
public:
  // Default methods

  A();                             // 1. default ctor
  ~A();                            // 2. dtor
  A(const A&);                     // 3. copy ctor
  A& operator=(const A&) = delete; // 4. assign operator

  A(A&&) noexcept;                 // 5. move ctor
  A& operator=(A&&);               // 6. move assign operator

  // In move ctor we write noexcept for vector::push_back function. 
  // In case size == capacity move ctor will use becuase it's noexcept
  // Otherwise simple copy ctor will be used.

  explicit A(const char* str);

  const char* data() const {
    return data_.get();
  }

  void setData(const char* str);

private:
  std::unique_ptr<char[]> data_;
  size_t len_ = 0;

  void init(const char* str);

  friend std::ostream& operator<<(std::ostream& os, const A& aObj);
};

#endif // ! A_H_

