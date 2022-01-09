#ifndef BELOFF_UNIT_TEST_H_
#define BELOFF_UNIT_TEST_H_

#include <string.h>

#define BUT_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define BUT_FUNCTION __FUNCTION__

int but_run();

typedef int (*but_test_proc_t)(const char** filename, const char** testname);

void but_add_test(but_test_proc_t test_proc);

#endif // ! BELOFF_UNIT_TEST_H_
