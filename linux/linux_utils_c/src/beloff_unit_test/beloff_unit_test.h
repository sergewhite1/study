#ifndef BELOFF_UNIT_TEST_H_
#define BELOFF_UNIT_TEST_H_

#include <string.h>

#define BUT_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define BUT_FUNCTION __FUNCTION__

#define CHECK_EQUAL_UL(actual_res, expected_res) \
  if (actual_res != expected_res) \
  { \
    printf("File: %s Line: %d %s != %s %s = %zu %s = %zu\n" \
           ,__FILE__       \
           ,__LINE__       \
           ,#actual_res    \
           ,#expected_res  \
           ,#actual_res    \
           ,actual_res     \
           ,#expected_res  \
           ,expected_res   \
           ); \
              \
    return 1; \
  }

#define CHECK_PTR_IS_NULL(ptr) \
  if (ptr != NULL) \
  { \
    printf("File: %s Line: %d %s actual result=%p expected result=NULL\n" \
           ,__FILE__     \
           ,__LINE__     \
           ,#ptr         \
           ,ptr          \
           );            \
                         \
    return 1;            \
  }

#define CHECK_STR_IS_NULL(str) \
  if (str != NULL) \
  { \
    printf("File: %s Line: %d %s actual result=%s expected result=NULL\n" \
           ,__FILE__    \
           ,__LINE__    \
           ,#str        \
           ,str         \
           );           \
                        \
    return 1;           \
  }


int but_run();

typedef int (*but_test_proc_t)(const char** filename, const char** testname);

void but_add_test(but_test_proc_t test_proc);

#endif // ! BELOFF_UNIT_TEST_H_
