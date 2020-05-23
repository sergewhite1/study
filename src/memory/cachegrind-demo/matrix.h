#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstring>

int**  matrix_generate_default();
size_t matrix_get_default_row_count();
size_t matrix_get_default_col_count();
int    matrix_sum_by_row(const int** ppmatrix, size_t row_count, size_t col_count);
int    matrix_sum_by_col(const int** ppmatrix, size_t row_count, size_t col_count);
void   matrix_release(int*** pppmatrix, size_t row_count);

#endif
