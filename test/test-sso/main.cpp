#include <cstring>
#include <iostream>

#include "wht_string.h"

/* COMMON TEST SCHEME: 
 * - short string
 * - long string
 * - 1 symbol string
 * - MAX_LOCAL_SIZE - 1 string
 * - MAX_LOCAL_SIZE string
 * - MAX_LOCAL_SIZE + 1 string
 * - empty string
 * - null pointer string
 */

static const char LONG_STRING[]="A VERY LONG STRING BLA_BLA_BLA !!!!! YES!!!";

static_assert(sizeof(LONG_STRING) > wht::string::MAX_LOCAL_SIZE, "");

// NOTE: free should be called.
static char* create_test_string(size_t size);

// white string test
// return values: 0 - success; 1 - error.
static int str_test(const wht::string* ws, bool is_empty, size_t len, 
  const char *cbuff); 

typedef int (*UnitTestProc)();

static int UnitTest01() {
  // default ctor

  wht::string ws;

  return str_test(&ws, true, 0, "");
}

static int UnitTest02() {
  // ctor; short string

  const char short_string[] = "BLA";
  const size_t len = strlen(short_string);
  static_assert(sizeof(short_string) < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws(short_string);

  return str_test(&ws, false, len, short_string);
}


static int UnitTest03() {
  // ctor; long string

  const size_t len = strlen(LONG_STRING);

  wht::string ws(LONG_STRING);

  return str_test(&ws, false, len, LONG_STRING);
}


static int UnitTest04() {
  // ctor; 1 symbol string

  const char c[] = "A";

  wht::string ws(c);

  return str_test(&ws, false, 1, c);
}

static int UnitTest05() {
  // ctor; MAX_LOCAL_SIZE-1

  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

  wht::string ws(c);

  int ret = str_test(&ws, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest06() {
  // ctor; MAX_LOCAL_SIZE

  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string ws(c);

  int ret = str_test(&ws, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest07() { 
  // ctror; MAX_LOCA_SIZE + 1

  const size_t size =  wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string ws(c);

  int ret = str_test(&ws, false, size - 1, c);
  free(c);

  return ret;
}


static int UnitTest08() { 
  // ctor; empty string

  wht::string ws("");

  return str_test(&ws, true, 0, "");
}


static int UnitTest09() { 
  // ctor; nullptr

  wht::string ws(nullptr);

  return str_test(&ws, true, 0, "");
}

static int UnitTest10() {
  // copy ctor; short string

  const char short_string[] = "BLA";
  const size_t size = sizeof(short_string);
  static_assert(size < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws1(short_string);
  wht::string ws2(ws1);

  return str_test(&ws2, false, size - 1, short_string);
} 

static int UnitTest11() {
  // copy ctor; long string

  wht::string ws1(LONG_STRING);
  wht::string ws2(ws1);

  return str_test(&ws2, false, sizeof(LONG_STRING) - 1, LONG_STRING);
}

static int UnitTest12() {
  // copy ctor; 1 symbol string

  const char c[] = "B";

  wht::string ws1(c);
  wht::string ws2(ws1);

  return str_test(&ws2, false, 1, c);
}

static int UnitTest13() {
  // copy ctor; MAX_LOCAL_SIZE - 1

  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(ws1);

  int ret = str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest14() {
  // copy ctor; MAX_LOCAL_SIZE

  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(ws1);

  int ret = str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest15() {
  // copy ctor; MAX_LOCA_SIZE + 1

  const size_t size =  wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(ws1);

  int ret = str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest16() {
  // copy ctor; empty string

  wht::string ws1("");
  wht::string ws2(ws1);  

  wht::string ws3;
  wht::string ws4(ws3);
  
  return str_test(&ws2, true, 0, "") + 
         str_test(&ws4, true, 0, "");
}

static int UnitTest17() {
  // copy ctor; nullptr

  wht::string ws1(nullptr);
  wht::string ws2(ws1);

  return str_test(&ws2, true, 0, "");
}

static int UnitTest18() {
  // move ctor; short string

  const char short_string[] = "BLA";
  const size_t size = sizeof(short_string);
  static_assert(size < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws1(short_string);
  wht::string ws2(std::move(ws1));

  return str_test(&ws2, false, size - 1, short_string);
}

static int UnitTest19() {
  // move ctor; long string

  wht::string ws1(LONG_STRING);
  wht::string ws2(std::move(ws1));

  return str_test(&ws2, false, sizeof(LONG_STRING) - 1, LONG_STRING);
}

static int UnitTest20() {
  // move ctor; 1 symbol string

  const char c[] = "C";
  wht::string ws1(c);
  wht::string ws2(std::move(ws1));

  return str_test(&ws2, false, 1, c);
}

static int UnitTest21() {
  // move ctor; MAX_LOCAL_SIZE - 1

  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(std::move(ws1));

  int ret = str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest22() {
  // move ctor; MAX_LOCAL_SIZE

  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(std::move(ws1));

  int ret = str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest23() {
  // move ctor; MAX_LOCA_SIZE + 1

  const size_t size =  wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(std::move(ws1));

  int ret = str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest24() {
  // move ctor; empty string

  wht::string ws1("");
  wht::string ws2(std::move(ws1));  

  wht::string ws3;
  wht::string ws4(std::move(ws3));
  
  return str_test(&ws2, true, 0, "") + 
         str_test(&ws4, true, 0, "");
}

static int UnitTest25() {
  // move ctor; nullptr

  wht::string ws1(nullptr);
  wht::string ws2(std::move(ws1));

  return str_test(&ws2, true, 0, "");
}

static int UnitTest26() {
  // operator=; short string

  const char short_string[] = "BLA";
  const size_t size = sizeof(short_string);
  static_assert(size < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws1(short_string);
  wht::string ws2("SOME STRING. BLA_BLA_BLA!!!!!!!2");

  ws2 = ws1;

  return str_test(&ws2, false, size - 1, short_string);
}

static int UnitTest27() {
  // operator=; long string

  wht::string ws1(LONG_STRING);
  wht::string ws2("FWEJFKWEJFKWEJWEKJFKLWEJ WDWSDW ssscfscfsdvsdv");
  
  ws2 = ws1;	
  return str_test(&ws2, false, sizeof(LONG_STRING) - 1, LONG_STRING);
}

static int UnitTest28() {
  // operator=; 1 symbol string

  const char c[] = "D";
  wht::string ws1(c);
  wht::string ws2("ZXCVVSSDFEEFEFEFJHDFJWHDJWHDJHWJHJHWJDHWJDHJWHDJW");

  ws2 = ws1;

  return str_test(&ws2, false, 1, c);
}

static int UnitTest29() {
  // operator=; MAX_LOCAL_SIZE - 1

  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");

  ws2 = ws1;

  int ret = str_test(&ws2, false, size - 1, c); 
  free(c);

  return ret;
}

static int UnitTest30() {
  // operator=; MAX_LOCAL_SIZE

  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2("hello");

  ws2 = ws1;

  int ret = str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest31() {
  // operator=; MAX_LOCA_SIZE + 1

  const size_t size = wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2("IIIIIIIIIOOOOOOOOOOPPPPPPPPPPPPZZZZZZZZZZZXXXXXXXXXXXCCV");

  ws2 = ws1;

  int ret = str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest32() {
  // operator=;  empty string

  wht::string ws1("");
  wht::string ws2("hello");  

  ws2 = ws1;

  wht::string ws3;
  wht::string ws4("DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL");

  ws4 = ws3;  

  return str_test(&ws2, true, 0, "") + 
         str_test(&ws4, true, 0, "");
}

static int UnitTest33() {
  // operator=; nullptr

  wht::string ws1(nullptr);
  wht::string ws2("abcd !!!!!d");

  ws2 = ws1;

  return str_test(&ws2, true, 0, "");
}

static int UnitTest34() {
  // operator=; self assign

  const char str[]="hello";
  const size_t size = sizeof(str);

  wht::string ws1(str);
  wht::string &ws2 = ws1;
  
  ws2 = ws1;

  return str_test(&ws1, false, size - 1, str);
}

static int UnitTest35() {
  // move operator=; (short string) = (short string)

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "short";
  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws1(str1);
  wht::string ws2(str2);
  
  ws1 = std::move(ws2);

  return str_test(&ws1, false, sizeof(str2) - 1, str2) + 
         str_test(&ws2, false, sizeof(str1) - 1, str1);
}

static const UnitTestProc UNIT_TESTS[] = {nullptr, 
  UnitTest01, UnitTest02, UnitTest03, UnitTest04, UnitTest05, UnitTest06,
  UnitTest07, UnitTest08, UnitTest09, UnitTest10, UnitTest11, UnitTest12,
  UnitTest13, UnitTest14, UnitTest15, UnitTest16, UnitTest17, UnitTest18,
  UnitTest19, UnitTest20, UnitTest21, UnitTest22, UnitTest23, UnitTest24,
  UnitTest25, UnitTest26, UnitTest27, UnitTest28, UnitTest29, UnitTest30,
  UnitTest31, UnitTest32, UnitTest33, UnitTest34, UnitTest35};

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


static int str_test(const wht::string* ws, bool is_empty, size_t len, 
  const char *cbuff) {

  if (ws->empty() != is_empty) {
    return 1;
  }
  if (ws->length() != len) {
    return 1;
  }
  if (strcmp(ws->data(), cbuff) != 0) {
    return 1;
  }

  return 0;
} 

