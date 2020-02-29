#include <cstring>
#include <iostream>

#include "wht_string.h"

static const char LONG_STRING[]="A VERY LONG STRING BLA_BLA_BLA !!!!! YES!!!";

static_assert(sizeof(LONG_STRING) > wht::string::MAX_LOCAL_SIZE, "");

// NOTE: free should be called.
static char* create_test_string(size_t size);

typedef int (*UnitTestProc)();

static int UnitTest1() {
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

static int UnitTest2() {
	// ctor; short string
	const char short_string[] = "BLA";
  const size_t len = strlen(short_string);
  static_assert(sizeof(short_string) < wht::string::MAX_LOCAL_SIZE, "");
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


static int UnitTest3() {
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

static int UnitTest4() {
	// ctor MAX_LOCAL_SIZE-1
  int ret = 1;
  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

	wht::string s(c);
  do {
		if (s.empty() == true) {
			break;
		}
		if (s.length() != size - 1) {
			break;
		}
		if (strcmp(s.data(), c) != 0) {
			break;
		}
		ret = 0;
  } while(false);

	return ret;
}

static int UnitTest5() {
  // ctor MAX_LOCAL_SIZE
  int ret = 1;
  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string s(c);
  do {
		if (s.empty() == true) {
			break;
		}
		if (s.length() != size - 1) {
			break;
		}
		if (strcmp(s.data(), c) != 0) {
			break;
		}
		ret = 0;
  } while (false);

	free(c);
	return ret;
}

static int UnitTest6() { 
	// ctror MAX_LOCA_SIZE + 1
	int ret = 1;
  const size_t size =  wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string s(c);
  do {
		if (s.empty() == true) {
			break;
		}
		if (s.length() != size - 1) {
			break;
		}
		if (strcmp(s.data(), c) != 0) {
			break;
		}
		ret = 0;
  } while (false);

	free(c);
	return ret;
}


static int UnitTest7() { 
	// ctor empty string
	wht::string s("");

  if (s.empty() == false) {
		return 1;
	}
	if (s.length() != 0) {
		return 1;
	} 
	if (*(s.data()) != '\0') {
		return 1;
	}

	return 0;
}


static int UnitTest8() { 
	// ctor nullptr
	wht::string s(nullptr);

  if (s.empty() == false)  {
		return 1;
  }
  if (s.length() != 0) {
		return 1;
	}
	if (*(s.data()) != '\0') {
		return 1;
	}

	return 0;
}

static int UnitTest9() {
	// copy ctor; short string
  const char short_string[] = "BLA";
  const size_t size = sizeof(short_string);
  static_assert(size < wht::string::MAX_LOCAL_SIZE, "");

	wht::string s1(short_string);
  wht::string s2(s1);
  if (s2.empty() == true) {
		return 1;
	}
	if (s2.length() != size - 1) {
		return 1;
	}
  if (strcmp(s2.data(), short_string) != 0){
		return 1;
  }

	return 0;
} 

static int UnitTest10() {
	// copy ctor: long string
  wht::string s1(LONG_STRING);
  wht::string s2(s1);

  if (s2.empty() == true) {
		return 1;
	}
	if (s2.length() != sizeof(LONG_STRING) - 1) {
		return 1;
	}
  if (strcmp(s2.data(), LONG_STRING) != 0){
		return 1;
  }
 
	return 0;
}

static int UnitTest11() {
	// copy ctor: MAX_LOCAL_SIZE - 1
  int ret = 1;
  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

	wht::string s1(c);
  wht::string s2(s1);
  do {
		if (s2.empty() == true) {
			break;
		}
		if (s2.length() != size - 1) {
			break;
		}
		if (strcmp(s2.data(), c) != 0) {
			break;
		}
		ret = 0;
  } while(false);

	return ret;
}

static int UnitTest12() {
	// copy ctor: MAX_LOCAL_SIZE
  int ret = 1;
  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string s1(c);
	wht::string s2(s1);
  do {
		if (s2.empty() == true) {
			break;
		}
		if (s2.length() != size - 1) {
			break;
		}
		if (strcmp(s2.data(), c) != 0) {
			break;
		}
		ret = 0;
  } while (false);

	free(c);
	return ret;
}

static int UnitTest13() {
	// copy ctor: MAX_LOCA_SIZE + 1
	int ret = 1;
  const size_t size =  wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string s1(c);
	wht::string s2(s1);
  do {
		if (s2.empty() == true) {
			break;
		}
		if (s2.length() != size - 1) {
			break;
		}
		if (strcmp(s2.data(), c) != 0) {
			break;
		}
		ret = 0;
  } while (false);

	free(c);
	return ret;
}

static int UnitTest14() {
	// copy ctor: empty string
	wht::string s1("");
  wht::string s2(s1);  

  if (s2.empty() == false) {
		return 1;
	}
	if (s2.length() != 0) {
		return 1;
	} 
	if (*(s2.data()) != '\0') {
		return 1;
	}

  wht::string s3;
  wht::string s4(s3);
  
  if (s4.empty() == false) {
		return 1;
	}
	if (s4.length() != 0) {
		return 1;
	} 
	if (*(s4.data()) != '\0') {
		return 1;
	}

	return 0;
}

static int UnitTest15() {
	// copy ctor: nullptr
	wht::string s1(nullptr);
	wht::string s2(s1);

  if (s2.empty() == false)  {
		return 1;
  }
  if (s2.length() != 0) {
		return 1;
	}
	if (*(s2.data()) != '\0') {
		return 1;
	}

	return 0;
}

static const UnitTestProc UNIT_TESTS[] = {nullptr, UnitTest1, UnitTest2, UnitTest3,
	UnitTest4, UnitTest5, UnitTest6, UnitTest7, UnitTest8, UnitTest9, UnitTest10,
  UnitTest11, UnitTest12, UnitTest13, UnitTest14, UnitTest15};

int main(int argc, const char* argv[]) {
	std::cout << "test-sso"	<< std::endl;
  std::cout << "sizeof(LONG_STRING)=" << sizeof(LONG_STRING) << std::endl;

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

static char* create_test_string(size_t size) {
	char *ret = reinterpret_cast<char*>(malloc(size));
  for(size_t i = 0; i <= size - 2; ++i) {
    ret[i] = 'A' + static_cast<char>(i);
	}
  ret[size - 1] = '\0';
	return ret;
}
