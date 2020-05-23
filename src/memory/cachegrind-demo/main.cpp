#include <iostream>

#include "technosphera_timer.h"

#include "matrix.h"

#if defined MATRIX_SUM_BY_COL
#define matrix_sum matrix_sum_by_col
#else
#define matrix_sum matrix_sum_by_row
#endif

int main() {
  std::cout << "run: " << std::endl;
  std::cout << "valgrind --tool=cachegrind your_process" << std::endl;

  srand(time(NULL));

  int** ppmatrix = matrix_generate_default();
  size_t row_count = matrix_get_default_row_count();
  size_t col_count = matrix_get_default_col_count();

  {
    technosphera::Timer t;
    for (size_t i = 0; i < 100; ++i) {
      int sum = matrix_sum(const_cast<const int**>(ppmatrix), row_count, col_count);
      std::cout << "sum[" << i << "]=" << sum << ' ';
    }
    std::cout << std::endl;
  }
  
  matrix_release(&ppmatrix, row_count);
  
  return 0;
}
