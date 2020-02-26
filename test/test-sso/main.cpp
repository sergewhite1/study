#include <iostream>

#include "wht_string.h"

typedef int (*UnitTestProc)();

static int UnitTest0() {
	// Empty string after constructor
	// std::cout << "Unit Test0" << std::endl;
	wht::string s1;
	if (s1.empty() == false) {
		return 1;
	}

	wht::string s2("");
	if (s2.empty() == false) {
		return 1;
	}

	return 0;
}

static const UnitTestProc UNIT_TESTS[] = {UnitTest0};

int main(int argc, const char* argv[]) {
	std::cout << "test-sso"	<< std::endl;

  //std::cout << "argc= " << argc << std::endl;

  //std::cout << "argc= " << argc << std::endl;
  //for (int i = 0; i < argc; ++i) {
	//	std::cout << "argv[" << i << "]= " << argv[i] << std::endl;
	//}

  wht::string s2("");
	if (argc < 2) {
		std::cout << "Error! No test case number in command line arg!";
		return 1;
	}

  return UNIT_TESTS[atoi(argv[1])]();
}
