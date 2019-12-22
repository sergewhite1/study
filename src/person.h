#ifndef PERSON_H_
#define PERSON_H

#include <string>

class Person {
public:
  Person(const std::string& firstname, const std::string &lastname);

  std::string firstname() const;
  std::string lastname() const;
  void save() const;
  
  friend std::ostream& operator<<(std::ostream &stream, const Person &person);

private:
  std::string firstname_;
  std::string lastname_;
};

#endif
