#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>

static void listing1();
static void listing2();
static void listing3();
static void listing4();
static void listing5();
static void listing6();
static void listing7();
static void listing8();
static void listing9();
static void listing10();
static void listing11();
static void listing12();
static void listing13();
static void listing14();
static void listing15();
static void listing16();
static void listing17();
static void listing18();
static void listing19();
static void listing20();
static void listing21();
static void listing22();
static void listing23();
static void listing24(); 

// PRINT_ELEMENTS()
// prints optional string optstr,
// after it prints all elements of collection coll
// in all string, delimited by spaces
template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string optstr="") {
  std::cout << optstr;
  for (const auto & elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
}

static void print(const int& elem) {
  std::cout << elem << ' ';
}

static int square(int value) {
  return value * value;
}

// unary predicat whch return true if number is prime
bool isPrime(int number) {
  number = abs(number);

  if (number == 0 || number == 1) {
    return false;
  }

  int divisor;
  for (divisor = number / 2; number % divisor != 0; --divisor);

  return divisor == 1;
}

class Person {
public:
  Person(const std::string& firstname, const std::string &lastname)
  : firstname_(firstname),
    lastname_(lastname) {}

  std::string firstname() const {return firstname_;}
  std::string lastname() const {return lastname_;}

private:
  std::string firstname_;
  std::string lastname_;
};

std::ostream& operator<<(std::ostream &stream, const Person &person) {
  stream << person.firstname() << ' ' << person.lastname();
  return stream;
}

static bool personSortCriterion(const Person &p1, const Person &p2) {
  return p1.lastname() < p2.lastname() || (
    (p1.lastname() == p2.lastname()) && (p1.firstname() < p2.firstname())
    );
}

static void add10(int& elem) {
  elem +=10;
}

template<int value>
static void add(int& elem) {
  elem += value;
}

// functional object add value during init
class AddValue {
public:
  AddValue(int value): value_(value) {}
  void operator()(int& elem) {
    elem += value_;
  }

private:
  int value_ = 0;
};

int main() {
  std::cout << "STL iterators demo" << std::endl;

  //listing1();
  //listing2();
  //listing3();
  //listing4();
  //listing5();
  //listing6();
  //listing7();
  //listing8();
  //listing9();
  //listing10();
  //listing11();
  //listing12();
  //listing13();
  //listing14();
  //listing15();
  //listing16();
  //listing17();
  //listing18();
  //listing19();
  //listing20();
  //listing21();
  //listing22();
  //listing23();
  listing24();

  return 0;
}

static void listing1() {
  std::vector<int> v;
  std::vector<int>::iterator itr;
  int i;

  for (i = 0; i < 5; ++i) {
    v.push_back(i);
  }

  std::cout << "Input array: ";
  itr = v.begin();
  while (itr != v.end()) {
    std::cout << *itr++ << " ";
  }
  std::cout << std::endl;
  int * p = &*v.begin();
  std::cout << "Address: " << p << std::endl;

  // * p = 222;
  // std::cout << "Input array2: ";
  // itr = v.begin();
  // while (itr != v.end()) {
  //   std::cout << *itr++ << " ";
  // }
  // std::cout << std::endl;

  itr = v.begin();
  itr += 2; // reference to the 2nd element

  // create insert iterator referenced to the elem 2
  std::insert_iterator<std::vector<int>> i_itr(v, itr);

  // insert
  *i_itr++ = 100;
  *i_itr++ = 200;

  // Init memory reallocate
  // for (i = 0; i < 100; ++i) {
  //  *i_itr++ = i * 10;
  // }

  std::cout << "Array after insert: ";
  itr = v.begin();
  while (itr != v.end()) {
    std::cout << *itr++ << " ";
  }
  std::cout << std::endl;
  p = &*v.begin();
  std::cout << "Address: " << p << std::endl;
}

static void listing2() {
  std::istream_iterator<char> in_it(std::cin);
  do {
    std::cout << *in_it++;
  } while (*in_it != '.');
  std::cout << std::endl;
}

static void listing3() {
  std::ostream_iterator<char> out_it(std::cout);

  *out_it++ = 'X';
  *out_it++ = 'Y';
  *out_it++ = ' ';

  char str[] = "Iterators is powerful tool.\n";
  char *p = str;
  while (*p) *out_it++ = *p++;

  std::ostream_iterator<double> out_double_it(std::cout);
  *out_double_it++ = 187.23;
  *out_double_it++ = -102.7;

  std::cout << std::endl;
}

static void listing4() {
  std::list<char> coll;

  for (char c = 'a'; c <= 'z'; ++c) {
    coll.push_back(c);
  }

  std::list<char>::const_iterator pos;
  for(pos = coll.begin(); pos != coll.end(); ++pos) {
    std::cout << *pos << ' ';
  }
  std::cout << std::endl;
}

static void listing5() {
  typedef std::set<int, std::greater<int>> IntSet;
  IntSet coll;
  coll.insert({3, 1, 5, 4, 1, 6, 2});

  IntSet::const_iterator pos;
  for (pos = coll.begin(); pos != coll.end(); ++pos) {
    std::cout << *pos << ' ';
  }
  std::cout << std::endl;
}

static void listing6() {
  std::unordered_set<int> coll;
  //std::unordered_multiset<int> coll;

  coll.insert({ 1, 3, 5, 7, 11, 13, 17, 19, 23, 27, 1});

  for (const auto & elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  coll.insert(25);

  for (const auto & elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
}

static void listing7() {
  std::vector<int> coll = {2, 5, 4, 1, 6, 3};
  auto minpos = std::min_element(coll.cbegin(), coll.cend());
  std::cout << "min: " << *minpos << std::endl;
  auto maxpos = std::max_element(coll.cbegin(), coll.cend());
  std::cout << "max: " << *maxpos << std::endl;

  std::sort(coll.begin(), coll.end());

  auto pos3 = std::find(coll.begin(), coll.end(), 3);
  std::reverse(pos3, coll.end());

  for (const auto & elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
}

static void listing8() {
  std::list<int> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::vector<int> coll2;
  coll2.resize(coll1.size());
  std::copy(coll1.cbegin(), coll1.cend(), coll2.begin());

  std::deque<int> coll3(coll1.size());
  std::copy(coll1.cbegin(), coll1.cend(), coll3.begin());
}

static void listing9() {
  std::list<int> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::vector<int> coll2;
  std::copy(coll1.cbegin(), coll1.cend(), std::back_inserter(coll2));

  std::deque<int> coll3;
  std::copy(coll1.cbegin(), coll1.cend(), std::front_inserter(coll3));

  std::set<int> coll4;
  std::copy(coll1.cbegin(), coll1.cend(), std::inserter(coll4, coll4.cbegin()));
}

static void listing10() {
  std::vector<std::string> coll;
  std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), std::back_inserter(coll));
  std::sort(coll.begin(), coll.end());
  std::unique_copy(coll.cbegin(), coll.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
}

static void listing11() {
  std::vector<int> v1 = {10, 20, 30, 40, 50, 60, 70};
  std::vector<int> v2(v1.size());
  std::copy(v1.cbegin(), v1.cend(), v2.begin());
  for (const auto & elem : v2) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
}

static void listing12() {
  std::cout << "6.5.3 Reverse Iterators" << std::endl;
  std::vector<int> coll;
  for (int i = 1; i <=9; ++i) {
    coll.push_back(i);
  }

  // print to screen all elements in reverse order
  std::copy(
    coll.crbegin(), coll.crend(),               // source
    std::ostream_iterator<int>(std::cout, " ")  // destination
  );
  std::cout << std::endl;
}

static void listing13() {
  std::cout << "6.6 User generic fucntion" << std::endl;
  std::list<int> coll = {1, 2, 3, 4, 5, 6, 7};
  PRINT_ELEMENTS(coll, "All elements: ");
}

static void listing14() {
  std::cout << "6.7.1 Remove Erase Of Elements." << std::endl;

  std::list<int> coll;

  // insert elements from 6 to 1 and from 1 to 6
  for(int i = 1; i <= 6; ++i) {
    coll.push_front(i);
    coll.push_back(i);
  }

  // print all elements
  std::cout << "pre:   ";
  std::copy(
    coll.cbegin(), coll.cend(),                 // source
    std::ostream_iterator<int>(std::cout, " ")  // destination
  );
  std::cout << std::endl;

  std::list<int>::iterator end = std::remove(
    coll.begin(), coll.end(), // range
    3                         // value
  );

  // print result elements
  std::cout << "post:  ";
  std::copy(
    coll.begin(), end,                          // source
    std::ostream_iterator<int>(std::cout, " ")  // destination
  );
  std::cout << std::endl;

  std::cout << "number of removed elements: " << std::distance(end, coll.end())
            << std::endl;

  coll.erase(end, coll.end());

  // print final collection
  std::cout << "final: ";
  std::copy(
    coll.cbegin(), coll.cend(),                          // source
    std::ostream_iterator<int>(std::cout, " ")  // destination
  );
  std::cout << std::endl;
}


static void listing15() {
  std::cout << "6.7.2 Work with associated and unordered containers" << std::endl;

  // unordered set with elements from 1 to 9
  std::set<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // print all elements of collection
  std::copy(
    coll.cbegin(), coll.cend(),                // source
    std::ostream_iterator<int>(std::cout, " ") // destination
  );
  std::cout << std::endl;

  // Erase all elemnets value 3
  // algorithm remove does not work
  // instead we use function member erase

  int num = coll.erase(3);
  std::cout << "number of erased elememts: " << num << std::endl;

  std::copy(
    coll.cbegin(), coll.cend(),                // source
    std::ostream_iterator<int>(std::cout, " ") // destination
  );
  std::cout << std::endl;
}


static void listing16() {
  std::cout << "6.7.3 Algorithms and Member Functions." << std::endl;

  std::list<int> coll;
  // insert elements from 6 to 1 and from 1 to 6
  for (int i = 1; i <= 6; ++i) {
    coll.push_front(i);
    coll.push_back(i);
  }
  PRINT_ELEMENTS(coll, "before: ");

  // remove all elements with value 3 (low performance)
  coll.erase(
    std::remove(coll.begin(), coll.end(), 3),
    coll.end()
  );

  // remove all elements with value 4 (high performace)
  coll.remove(4);

  PRINT_ELEMENTS(coll, "after:  ");
}

static void listing17() {
  std::cout << "6.8.1 Use functions as algorithm argument (std::for_each)" << std::endl;

  std::vector<int> coll;

  // insert elemms from 1 to 9
  for (int i = 1; i <= 9; ++i) {
    coll.push_back(i);
  }

  // print to screen all elems
  std::for_each(
    coll.cbegin(), coll.cend(),
    print
  );
  std::cout << std::endl;
}

static void listing18() {
  std::cout << "6.8.1 Use functions as algorithm argument (std::transform)" << std::endl;

  std::set<int> coll1;
  std::vector<int> coll2;

  // insert elems from 1 to 9 to coll1
  for(int i = 1; i <= 9; ++i) {
    coll1.insert(i);
  }
  PRINT_ELEMENTS(coll1, "inited:  ");

  // coll1 -> coll2
  // square every value
 
  std::transform(
    coll1.cbegin(), coll1.cend(),
    std::back_inserter(coll2),
    square
  );
  PRINT_ELEMENTS(coll2, "squared: ");
}

static void listing19() {
  std::cout << "6.8.2 Predicats. Unary" << std::endl;

  std::list<int> coll;

  // insert elements from 24 to 30
  for (int i = 24; i <= 30; ++i) {
    coll.push_back(i);
  }

  // find prime number
  auto pos = std::find_if(
    coll.cbegin(), coll.cend(),
    isPrime
  );
  if (pos != coll.cend()) {
    // found
    std::cout << *pos << " - is prime number" << std::endl;
  } else {
    // not found
    std::cout << "prime number not fond" << std::endl;
  }
}

static void listing20() {
  std::cout << "6.8.2 Predicats. Binary." << std::endl;

  std::deque<Person> coll;

  coll.push_back(Person("Serge", "Beloff"));
  coll.push_back(Person("Antonio", "Vivaldi"));
  coll.push_back(Person("Jean", "Fourier"));


  PRINT_ELEMENTS(coll, "unsorted container: ");

  std::sort(
    coll.begin(), coll.end(),
    personSortCriterion
  );

  PRINT_ELEMENTS(coll, "sorted container:   ");
}

static void listing21() {
  std::cout << "6.10.1-1 Function Object Definition. For each add 10" << std::endl;

  std::vector<int> coll;
  for (int i = 1; i <= 9; ++i) {
    coll.push_back(i);
  }
  PRINT_ELEMENTS(coll, "init:  ");

  std::for_each(coll.begin(), coll.end(), add10);
  PRINT_ELEMENTS(coll, "add10: ");
}

static void listing22() {
  std::cout << "6.10.1-2 Function Object Definition. "
    "Add different values we know at compile time" << std::endl;

  std::vector<int> coll;
  for (int i = 1; i <= 9; ++i) {
    coll.push_back(i);
  }
  PRINT_ELEMENTS(coll, "init:    ");

  std::for_each(coll.begin(), coll.end(), add<10>);
  PRINT_ELEMENTS(coll, "add<10>: ");
}

static void listing23() {
  std::cout << "6.10.1-3 Function Object Definition. "
    "Add different values we know in run time" << std::endl;
 
  std::list<int> coll;
  for (int i = 1; i <= 9; ++i) {
    coll.push_back(i);
  }
  PRINT_ELEMENTS(coll, "init:         ");

  std::for_each(coll.begin(), coll.end(), AddValue(10));
  PRINT_ELEMENTS(coll, "AddValue(10): ");
}

static void listing24() {
  std::cout << "6.10.2 Standard Functional Objects" << std::endl;

  std::deque<int> coll = { 1, 2, 3, 5, 7, 11, 13, 17, 19 };
  PRINT_ELEMENTS(coll, "init:        ");

  // change sign of all elements in collection to another
  std::transform(
    coll.cbegin(), coll.cend(), // source
    coll.begin(),               // destination
    std::negate<int>()          // operation
  );
  PRINT_ELEMENTS(coll, "change sign: ");

  // square all elements in coll
  std::transform(
    coll.cbegin(), coll.cend(), // the 1st sourse
    coll.cbegin(),              // the 2nd source
    coll.begin(),               // destination
    std::multiplies<int>()      // operation
  );
  PRINT_ELEMENTS(coll, "square:     ");
}
