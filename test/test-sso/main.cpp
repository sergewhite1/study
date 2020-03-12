#include <cassert>
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

static inline size_t strlen_test(const char* str) {
  return str == nullptr ? 0 : strlen(str);
}

// white string test
// return value: 0 - success; 1 - error.
static int str_test(const wht::string* ws, bool is_empty, size_t len, 
  const char *cbuff); 

typedef int (*UnitTestProc)();

static int UnitTest01() {
  // default ctor

  wht::string ws;

  return str_test(&ws, true, 0, "");
}

// return value: 0 - success; otherwise - error;
static int move_assign_test(const char* str1, const char* str2);

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

  return move_assign_test(str1, str2);
}

static int UnitTest36() {
  // move operator=; (short string) = (long string)

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  const char *str2 = LONG_STRING;
  size_t str2_size = strlen(str2) + 1;
  assert(str2_size > wht::string::MAX_LOCAL_SIZE);

  return move_assign_test(str1, str2);
}

static int UnitTest37() {
  // move operator=; (short string) = (1 symbol string)

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "F";

  return move_assign_test(str1, str2);
}

static int UnitTest38() {
  // move operator=; (short string) = (MAX_LOCAL_SIZE - 1 string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest39() {
  // move operator=; (short string) = (MAX_LOCAL_SIZE string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest40() {
  // move operator=; (short string) = (MAX_LOCAL_SIZE + 1 string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest41() {
  // move operator=; (short string) = (empty string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, "");
}

static int UnitTest42() {
  // move operator=; (short string) = (empty string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, nullptr);
}

static int UnitTest43() {
  // move operator=; (long string) = (short string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "hello";
  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest44() {
  // move operator=; (long string) = (long string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "helloDWHJKWHDJQWHDJQWHDJQWHDJQWHDQWJDHDHWEUDHWEUDHWEUQDHUDH";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest45() {
  // move operator=; (long string) = (1 symbol string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "H";

  return move_assign_test(str1, str2);
}

static int UnitTest46() {
  // move operator=; (long string) = (MAX_LOCAL_SIZE - 1 string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str2);
  return ret;
}

static int UnitTest47() {
  // move operator=; (long string) = (MAX_LOCAL_SIZE string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str2);
  return ret;
}

static int UnitTest48() {
  // move operator=; (long string) = (MAX_LOCAL_SIZE + 1 string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str2);
  return ret;
}

static int UnitTest49() {
  // move operator=; (long string) = (empty string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, "");
}

static int UnitTest50() {
  // move operator=; (long string) = (nullptr string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, nullptr);
}

static int UnitTest51() {
  // move operator=; (1 symbol string) = (short string)

  const char str1[] = "K";

  const char str2[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest52() {
  // move operator=; (1 symbol string) = (long string)

  const char str1[] = "K";

  const char str2[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest53() {
  // move operator=; (1 symbol string) = (MAX_LOCAL_SIZE - 1 string)

  const char str1[] = "K";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest54() {
  // move operator=; (1 symbol string) = (MAX_LOCAL_SIZE string)

  const char str1[] = "K";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest55() {
  // move operator=; (1 symbol string) = (MAX_LOCAL_SIZE + 1 string)

  const char str1[] = "K";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest56() {
  // move operator=; (1 symbol string) = (empty string)

  const char str1[] = "K";

  return move_assign_test(str1, "");
}

static int UnitTest57() {
  // move operator=; (1 symbol string) = (nullptr string)

  const char str1[] = "K";

  return move_assign_test(str1, nullptr);
}

static int UnitTest58() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (short string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char str2[] = "hello";
  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest59() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (long string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char str2[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest60() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (1 symbol string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char str2[] = "A";

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest61() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (MAX_LOCAL_SIZE - 1 string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest62() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (MAX_LOCAL_SIZE  string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE );

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest63() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (MAX_LOCAL_SIZE + 1 string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest64() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (empty string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char str2[] = "";

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest65() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (nullptr string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char *str2 = nullptr;

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static const UnitTestProc UNIT_TESTS[] = {nullptr, 
  UnitTest01, UnitTest02, UnitTest03, UnitTest04, UnitTest05, UnitTest06,
  UnitTest07, UnitTest08, UnitTest09, UnitTest10, UnitTest11, UnitTest12,
  UnitTest13, UnitTest14, UnitTest15, UnitTest16, UnitTest17, UnitTest18,
  UnitTest19, UnitTest20, UnitTest21, UnitTest22, UnitTest23, UnitTest24,
  UnitTest25, UnitTest26, UnitTest27, UnitTest28, UnitTest29, UnitTest30,
  UnitTest31, UnitTest32, UnitTest33, UnitTest34, UnitTest35, UnitTest36,
  UnitTest37, UnitTest38, UnitTest39, UnitTest40, UnitTest41, UnitTest42,
  UnitTest43, UnitTest44, UnitTest45, UnitTest46, UnitTest47, UnitTest48,
  UnitTest49, UnitTest50, UnitTest51, UnitTest52, UnitTest53, UnitTest54,
  UnitTest55, UnitTest56, UnitTest57, UnitTest58, UnitTest59, UnitTest60,
  UnitTest61, UnitTest62, UnitTest63, UnitTest64, UnitTest65};

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

  if (cbuff) {
    if (strcmp(ws->data(), cbuff) != 0) {
      return 1;
    }
  } else {
    if (strcmp(ws->data(), "") != 0) {
      return 1;
    }
  }

  return 0;
} 

static int move_assign_test(const char* str1, const char* str2) {
  size_t str1_len = strlen_test(str1);
  size_t str2_len = strlen_test(str2);

  wht::string ws1(str1);
  wht::string ws2(str2);
  
  ws1 = std::move(ws2);

  return str_test(&ws1, str2_len == 0, str2_len, str2) +
         str_test(&ws2, str1_len == 0, str1_len, str1);
}
