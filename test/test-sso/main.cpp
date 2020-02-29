#include <cstring>
#include <iostream>

#include "wht_string.h"

// See this variable in wht::string class
static const size_t MAX_LOCAL_SIZE = 32;
static const char LONG_STRING[]="A VERY LONG STRING BLA_BLA_BLA !!!!! YES!!!";

static_assert(sizeof(LONG_STRING) > MAX_LOCAL_SIZE);

typedef int (*UnitTestProc)();

static int UnitTest0() {
	// default ctor
	wht::string s;
	if (s.empty() == false) {
		return 1;
	}

	if (s.length() != 0) {
		return 1;
	}

	if (strcmp(s.data(), "") != 0) {
		return 1;
	} 

	return 0;
}

static int UnitTest1() {
	// ctor; short string
	const char short_string[] = "BLA";
  const size_t len = strlen(short_string);
	static_assert(sizeof(short_string) < MAX_LOCAL_SIZE);
	wht::string s(short_string);
	if (s.empty() == true) {
		return 1;
	}
	if (s.length() != len) {
		return 1;
	}
	if (strcmp(s.data(), short_string) != 0) {
		return 1;
	}

	return 0;
}


static int UnitTest2() {
	// ctor; long string
	const size_t len = strlen(LONG_STRING);
	wht::string s(LONG_STRING);
	if (s.empty() == true) {
		return 1;
	}
	if (s.length() != len) {
		return 1;
	}
	if (strcmp(s.data(), LONG_STRING) != 0) {
		return 1;
	}
	return 0;
}

static const UnitTestProc UNIT_TESTS[] = {UnitTest0, UnitTest1, UnitTest2};

int main(int argc, const char* argv[]) {
	std::cout << "test-sso"	<< std::endl;
	std::cout << "sizeof(LONG_STRING)" << sizeof(LONG_STRING) << std::endl;

  //std::cout << "argc= " << argc << std::endl;

  //std::cout << "argc= " << argc << std::endl;
  //for (int i = 0; i < argc; ++i) {
	//	std::cout << "argv[" << i << "]= " << argv[i] << std::endl;
	//}

	if (argc < 2) {
		std::cout << "Error! No test case number in command line arg!";
		return 1;
	}

  return UNIT_TESTS[atoi(argv[1])]();
}
