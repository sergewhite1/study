#include "person.h"

#include <iostream>

Person:: Person(const std::string& firstname, const std::string &lastname)
  : firstname_(firstname),
    lastname_(lastname) {}

std::string Person::firstname() const {
  return firstname_;
}

std::string Person::lastname() const {
  return lastname_;
}

void Person::save() const {
  std::cout << "Save of " << *this << std::endl;
}
 
  
std::ostream& operator<<(std::ostream &stream, const Person &person) {
  stream << person.firstname() << ' ' << person.lastname();
  return stream;
}
