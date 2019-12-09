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
