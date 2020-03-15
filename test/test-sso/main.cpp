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

static int UnitTest001() {
  // default ctor

  wht::string ws;

  return str_test(&ws, true, 0, "");
}

// return value: 0 - success; otherwise - error;
static int move_assign_test(const char* str1, const char* str2);

static int UnitTest002() {
  // ctor; short string

  const char short_string[] = "BLA";
  const size_t len = strlen(short_string);
  static_assert(sizeof(short_string) < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws(short_string);

  return str_test(&ws, false, len, short_string);
}


static int UnitTest003() {
  // ctor; long string

  const size_t len = strlen(LONG_STRING);

  wht::string ws(LONG_STRING);

  return str_test(&ws, false, len, LONG_STRING);
}


static int UnitTest004() {
  // ctor; 1 symbol string

  const char c[] = "A";

  wht::string ws(c);

  return str_test(&ws, false, 1, c);
}

static int UnitTest005() {
  // ctor; MAX_LOCAL_SIZE-1

  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

  wht::string ws(c);

  int ret = str_test(&ws, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest006() {
  // ctor; MAX_LOCAL_SIZE

  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string ws(c);

  int ret = str_test(&ws, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest007() { 
  // ctror; MAX_LOCA_SIZE + 1

  const size_t size =  wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string ws(c);

  int ret = str_test(&ws, false, size - 1, c);
  free(c);

  return ret;
}


static int UnitTest008() { 
  // ctor; empty string

  wht::string ws("");

  return str_test(&ws, true, 0, "");
}


static int UnitTest009() { 
  // ctor; nullptr

  wht::string ws(nullptr);

  return str_test(&ws, true, 0, "");
}

static int UnitTest010() {
  // copy ctor; short string

  const char short_string[] = "BLA";
  const size_t size = sizeof(short_string);
  static_assert(size < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws1(short_string);
  wht::string ws2(ws1);

  return str_test(&ws1, false, size - 1, short_string) +
         str_test(&ws2, false, size - 1, short_string);
} 

static int UnitTest011() {
  // copy ctor; long string

  wht::string ws1(LONG_STRING);
  wht::string ws2(ws1);

  return str_test(&ws1, false, sizeof(LONG_STRING) - 1, LONG_STRING) +
         str_test(&ws2, false, sizeof(LONG_STRING) - 1, LONG_STRING);
}

static int UnitTest012() {
  // copy ctor; 1 symbol string

  const char c[] = "B";

  wht::string ws1(c);
  wht::string ws2(ws1);

  return  str_test(&ws1, false, 1, c) +
          str_test(&ws2, false, 1, c);
}

static int UnitTest013() {
  // copy ctor; MAX_LOCAL_SIZE - 1

  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(ws1);

  int ret = str_test(&ws1, false, size - 1, c) + 
            str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest014() {
  // copy ctor; MAX_LOCAL_SIZE

  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(ws1);

  int ret = str_test(&ws1, false, size - 1, c) +
            str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest015() {
  // copy ctor; MAX_LOCA_SIZE + 1

  const size_t size =  wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(ws1);

  int ret = str_test(&ws1, false, size - 1, c) +
            str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest016() {
  // copy ctor; empty string

  wht::string ws1("");
  wht::string ws2(ws1);  

  wht::string ws3;
  wht::string ws4(ws3);
  
  return str_test(&ws2, true, 0, "") + 
         str_test(&ws4, true, 0, "");
}

static int UnitTest017() {
  // copy ctor; nullptr

  wht::string ws1(nullptr);
  wht::string ws2(ws1);

  return str_test(&ws1, true, 0, "") +
         str_test(&ws2, true, 0, "");
}

static int UnitTest018() {
  // move ctor; short string

  const char short_string[] = "BLA";
  const size_t size = sizeof(short_string);
  static_assert(size < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws1(short_string);
  wht::string ws2(std::move(ws1));

  return str_test(&ws1, true, 0, "") +
         str_test(&ws2, false, size - 1, short_string);
}

static int UnitTest019() {
  // move ctor; long string

  wht::string ws1(LONG_STRING);
  wht::string ws2(std::move(ws1));

  return str_test(&ws1, true, 0, "") +
         str_test(&ws2, false, sizeof(LONG_STRING) - 1, LONG_STRING);
}

static int UnitTest020() {
  // move ctor; 1 symbol string

  const char c[] = "C";
  wht::string ws1(c);
  wht::string ws2(std::move(ws1));

  return str_test(&ws1, true, 0, "") +
         str_test(&ws2, false, 1, c);
}

static int UnitTest021() {
  // move ctor; MAX_LOCAL_SIZE - 1

  const size_t size = wht::string::MAX_LOCAL_SIZE - 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(std::move(ws1));

  int ret = str_test(&ws1, true, 0, "") +
            str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest022() {
  // move ctor; MAX_LOCAL_SIZE

  const size_t size =  wht::string::MAX_LOCAL_SIZE;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(std::move(ws1));

  int ret = str_test(&ws1, true, 0, "") +
            str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest023() {
  // move ctor; MAX_LOCA_SIZE + 1

  const size_t size =  wht::string::MAX_LOCAL_SIZE + 1;
  char *c = create_test_string(size);

  wht::string ws1(c);
  wht::string ws2(std::move(ws1));

  int ret = str_test(&ws1, true, 0, "") +
            str_test(&ws2, false, size - 1, c);
  free(c);

  return ret;
}

static int UnitTest024() {
  // move ctor; empty string

  wht::string ws1("");
  wht::string ws2(std::move(ws1));  

  wht::string ws3;
  wht::string ws4(std::move(ws3));
  
  return str_test(&ws2, true, 0, "") + 
         str_test(&ws4, true, 0, "");
}

static int UnitTest025() {
  // move ctor; nullptr

  wht::string ws1(nullptr);
  wht::string ws2(std::move(ws1));

  return str_test(&ws1, true, 0, "") +
         str_test(&ws2, true, 0, "");
}

static int UnitTest026() {
  // operator=; short string

  const char short_string[] = "BLA";
  const size_t size = sizeof(short_string);
  static_assert(size < wht::string::MAX_LOCAL_SIZE, "");

  wht::string ws1(short_string);
  wht::string ws2("SOME STRING. BLA_BLA_BLA!!!!!!!2");

  ws2 = ws1;

  return str_test(&ws2, false, size - 1, short_string);
}

static int UnitTest027() {
  // operator=; long string

  wht::string ws1(LONG_STRING);
  wht::string ws2("FWEJFKWEJFKWEJWEKJFKLWEJ WDWSDW ssscfscfsdvsdv");
  
  ws2 = ws1;	
  return str_test(&ws2, false, sizeof(LONG_STRING) - 1, LONG_STRING);
}

static int UnitTest028() {
  // operator=; 1 symbol string

  const char c[] = "D";
  wht::string ws1(c);
  wht::string ws2("ZXCVVSSDFEEFEFEFJHDFJWHDJWHDJHWJHJHWJDHWJDHJWHDJW");

  ws2 = ws1;

  return str_test(&ws2, false, 1, c);
}

static int UnitTest029() {
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

static int UnitTest030() {
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

static int UnitTest031() {
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

static int UnitTest032() {
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

static int UnitTest033() {
  // operator=; nullptr

  wht::string ws1(nullptr);
  wht::string ws2("abcd !!!!!d");

  ws2 = ws1;

  return str_test(&ws2, true, 0, "");
}

static int UnitTest034() {
  // operator=; self assign

  const char str[]="hello";
  const size_t size = sizeof(str);

  wht::string ws1(str);
  wht::string &ws2 = ws1;
  
  ws2 = ws1;

  return str_test(&ws1, false, size - 1, str);
}

static int UnitTest035() {
  // move operator=; (short string) = (short string)

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "short";
  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest036() {
  // move operator=; (short string) = (long string)

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  const char *str2 = LONG_STRING;
  size_t str2_size = strlen(str2) + 1;
  assert(str2_size > wht::string::MAX_LOCAL_SIZE);

  return move_assign_test(str1, str2);
}

static int UnitTest037() {
  // move operator=; (short string) = (1 symbol string)

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "F";

  return move_assign_test(str1, str2);
}

static int UnitTest038() {
  // move operator=; (short string) = (MAX_LOCAL_SIZE - 1 string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest039() {
  // move operator=; (short string) = (MAX_LOCAL_SIZE string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest040() {
  // move operator=; (short string) = (MAX_LOCAL_SIZE + 1 string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest041() {
  // move operator=; (short string) = (empty string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, "");
}

static int UnitTest042() {
  // move operator=; (short string) = (empty string) 

  const char str1[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, nullptr);
}

static int UnitTest043() {
  // move operator=; (long string) = (short string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "hello";
  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest044() {
  // move operator=; (long string) = (long string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "helloDWHJKWHDJQWHDJQWHDJQWHDJQWHDQWJDHDHWEUDHWEUDHWEUQDHUDH";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest045() {
  // move operator=; (long string) = (1 symbol string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  const char str2[] = "H";

  return move_assign_test(str1, str2);
}

static int UnitTest046() {
  // move operator=; (long string) = (MAX_LOCAL_SIZE - 1 string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str2);
  return ret;
}

static int UnitTest047() {
  // move operator=; (long string) = (MAX_LOCAL_SIZE string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str2);
  return ret;
}

static int UnitTest048() {
  // move operator=; (long string) = (MAX_LOCAL_SIZE + 1 string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str2);
  return ret;
}

static int UnitTest049() {
  // move operator=; (long string) = (empty string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, "");
}

static int UnitTest050() {
  // move operator=; (long string) = (nullptr string) 

  const char str1[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str1) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, nullptr);
}

static int UnitTest051() {
  // move operator=; (1 symbol string) = (short string)

  const char str1[] = "K";

  const char str2[] = "hello";
  static_assert(sizeof(str1) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest052() {
  // move operator=; (1 symbol string) = (long string)

  const char str1[] = "K";

  const char str2[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest053() {
  // move operator=; (1 symbol string) = (MAX_LOCAL_SIZE - 1 string)

  const char str1[] = "K";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest054() {
  // move operator=; (1 symbol string) = (MAX_LOCAL_SIZE string)

  const char str1[] = "K";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest055() {
  // move operator=; (1 symbol string) = (MAX_LOCAL_SIZE + 1 string)

  const char str1[] = "K";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest056() {
  // move operator=; (1 symbol string) = (empty string)

  const char str1[] = "K";

  return move_assign_test(str1, "");
}

static int UnitTest057() {
  // move operator=; (1 symbol string) = (nullptr string)

  const char str1[] = "K";

  return move_assign_test(str1, nullptr);
}

static int UnitTest058() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (short string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char str2[] = "hello";
  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest059() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (long string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char str2[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest060() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (1 symbol string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char str2[] = "A";

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest061() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (MAX_LOCAL_SIZE - 1 string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest062() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (MAX_LOCAL_SIZE  string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE );

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest063() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (MAX_LOCAL_SIZE + 1 string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest064() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (empty string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char str2[] = "";

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest065() {
  // move operator=; (MAX_LOCAL_SIZE - 1 string) = (nullptr string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  const char *str2 = nullptr;

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest066() {
  // move operator=; (MAX_LOCAL_SIZE  string) = (short string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  const char str2[] = "hello";

  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest067() {
  // move operator=; (MAX_LOCAL_SIZE  string) = (long string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  const char str2[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest068() {
  // move operator=; (MAX_LOCAL_SIZE  string) = (1 symbol string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  const char str2[] = "D";

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest069() {
  // move operator=; (MAX_LOCAL_SIZE  string) = (MAX_LOCAL_SIZE - 1 string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest070() {
  // move operator=; (MAX_LOCAL_SIZE  string) = (MAX_LOCAL_SIZE  string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest071() {
  // move operator=; (MAX_LOCAL_SIZE  string) = (MAX_LOCAL_SIZE + 1 string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest072() {
  // move operator=; (MAX_LOCAL_SIZE  string) = (empty string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  const char str2[] = "";

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest073() {
  // move operator=; (MAX_LOCAL_SIZE  string) = (nullptr string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  char *str2 = nullptr;

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest074() {
  // move operator=; (MAX_LOCAL_SIZE + 1 string) = (short string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  const char str2[] = "hello";

  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest075() {
  // move operator=; (MAX_LOCAL_SIZE + 1 string) = (long string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  const char str2[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest076() {
  // move operator=; (MAX_LOCAL_SIZE + 1 string) = (1 symbol string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  const char str2[] = "D";

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest077() {
  // move operator=; (MAX_LOCAL_SIZE + 1 string) = (MAX_LOCAL_SIZE - 1 string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest078() {
  // move operator=; (MAX_LOCAL_SIZE + 1 string) = (MAX_LOCAL_SIZE  string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest079() {
  // move operator=; (MAX_LOCAL_SIZE + 1 string) = (MAX_LOCAL_SIZE + 1 string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str1);
  free(str2);

  return ret;
}

static int UnitTest080() {
  // move operator=; (MAX_LOCAL_SIZE + 1 string) = (empty string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  const char str2[] = "";

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest081() {
  // move operator=; (MAX_LOCAL_SIZE + 1 string) = (nullptr string)
  char *str1 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  char *str2 = nullptr;

  int ret = move_assign_test(str1, str2);
  free(str1);

  return ret;
}

static int UnitTest082() {
  // move operator=; (empty string) = (short string)
  const char str1[] = "";

  const char str2[] = "hello";
  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest083() {
  // move operator=; (empty string) = (long string)
  const char str1[] = "";

  const char str2[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest084() {
  // move operator=; (empty string) = (1 symbol string)
  const char str1[] = "";

  const char str2[] = "D";

  return move_assign_test(str1, str2);
}

static int UnitTest085() {
  // move operator=; (empty string) = (MAX_LOCAL_SIZE - 1 string)
  const char str1[] = "";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest086() {
  // move operator=; (empty string) = (MAX_LOCAL_SIZE  string)
  const char str1[] = "";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest087() {
  // move operator=; (empty string) = (MAX_LOCAL_SIZE + 1 string)
  const char str1[] = "";

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest088() {
  // move operator=; (empty string) = (empty string)
  const char str1[] = "";

  const char str2[] = "";

  return move_assign_test(str1, str2);
}

static int UnitTest089() {
  // move operator=; (empty string) = (nullptr string)
  const char str1[] = "";

  const char *str2 = nullptr;

  return move_assign_test(str1, str2);
}

static int UnitTest090() {
  // move operator=; (nullptr string) = (short string)
  const char *str1 = nullptr;

  const char str2[] = "hello";
  static_assert(sizeof(str2) < wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest091() {
  // move operator=; (nullptr string) = (long string)
  const char *str1 = nullptr;

  const char str2[] = "DHJFHDJHFJDHFJDHFJKHJFKLAKL:DKLASDKLSDKLSKLDKLSKDLSKDLSKDL";
  static_assert(sizeof(str2) > wht::string::MAX_LOCAL_SIZE, "");

  return move_assign_test(str1, str2);
}

static int UnitTest092() {
  // move operator=; (nullptr string) = (1 symbol string)
  const char *str1 = nullptr;

  const char str2[] = "D";

  return move_assign_test(str1, str2);
}

static int UnitTest093() {
  // move operator=; (nullptr string) = (MAX_LOCAL_SIZE - 1 string)
  const char *str1 = nullptr;

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE - 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest094() {
  // move operator=; (nullptr string) = (MAX_LOCAL_SIZE  string)
  const char *str1 = nullptr;

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest095() {
  // move operator=; (nullptr string) = (MAX_LOCAL_SIZE + 1 string)
  const char *str1 = nullptr;

  char *str2 = create_test_string(wht::string::MAX_LOCAL_SIZE + 1);

  int ret = move_assign_test(str1, str2);
  free(str2);

  return ret;
}

static int UnitTest096() {
  // move operator=; (nullptr string) = (empty string)
  const char *str1 = nullptr;

  const char str2[] = "";

  return move_assign_test(str1, str2);
}

static int UnitTest097() {
  // move operator=; (nullptr string) = (nullptr string)
  const char *str1 = nullptr;

  const char *str2 = nullptr;

  return move_assign_test(str1, str2);
}

static const UnitTestProc UNIT_TESTS[] = {nullptr, 
  UnitTest001, UnitTest002, UnitTest003, UnitTest004, UnitTest005, UnitTest006,
  UnitTest007, UnitTest008, UnitTest009, UnitTest010, UnitTest011, UnitTest012,
  UnitTest013, UnitTest014, UnitTest015, UnitTest016, UnitTest017, UnitTest018,
  UnitTest019, UnitTest020, UnitTest021, UnitTest022, UnitTest023, UnitTest024,
  UnitTest025, UnitTest026, UnitTest027, UnitTest028, UnitTest029, UnitTest030,
  UnitTest031, UnitTest032, UnitTest033, UnitTest034, UnitTest035, UnitTest036,
  UnitTest037, UnitTest038, UnitTest039, UnitTest040, UnitTest041, UnitTest042,
  UnitTest043, UnitTest044, UnitTest045, UnitTest046, UnitTest047, UnitTest048,
  UnitTest049, UnitTest050, UnitTest051, UnitTest052, UnitTest053, UnitTest054,
  UnitTest055, UnitTest056, UnitTest057, UnitTest058, UnitTest059, UnitTest060,
  UnitTest061, UnitTest062, UnitTest063, UnitTest064, UnitTest065, UnitTest066,
  UnitTest067, UnitTest068, UnitTest069, UnitTest070, UnitTest071, UnitTest072,
  UnitTest073, UnitTest074, UnitTest075, UnitTest076, UnitTest077, UnitTest078,
  UnitTest079, UnitTest080, UnitTest081, UnitTest082, UnitTest083, UnitTest084,
  UnitTest085, UnitTest086, UnitTest087, UnitTest088, UnitTest089, UnitTest090,
  UnitTest091, UnitTest092, UnitTest093, UnitTest094, UnitTest095, UnitTest096,
  UnitTest097};

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
