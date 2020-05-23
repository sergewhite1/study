#include "matrix.h"

#include <cstdlib>

static size_t DEFAULT_ROW_COUNT = 1000;
static size_t DEFAULT_COL_COUNT = 1000;

int**  matrix_generate_default() {
  int** ret = nullptr;
  ret = new int* [DEFAULT_ROW_COUNT];
  memset(ret, 0, DEFAULT_ROW_COUNT * sizeof(ret[0]));
  for (size_t i = 0; i < DEFAULT_ROW_COUNT; ++i) {
    ret[i] = new int [DEFAULT_COL_COUNT];
  }

  // initialize with random values in range [0..99]
  for (size_t i = 0; i < DEFAULT_ROW_COUNT; ++i) {
    for (size_t j = 0; j < DEFAULT_COL_COUNT; ++j) {
      ret[i][j] = rand() % 100;
    }
  }

  return ret;
}

size_t matrix_get_default_row_count() {
  return DEFAULT_ROW_COUNT;
}

size_t matrix_get_default_col_count() {
  return DEFAULT_COL_COUNT;
}

int    matrix_sum_by_row(const int** ppmatrix, size_t row_count, size_t col_count) {
  int ret = 0;
  for (size_t i = 0; i < row_count; ++i) {
    for (size_t j = 0; j < col_count; ++j) {
      ret += ppmatrix[i][j];
    }
  }
  return ret;
}

int    matrix_sum_by_col(const int** ppmatrix, size_t row_count, size_t col_count) {
  int ret = 0;
  for (size_t j = 0; j < col_count; ++j) {
    for (size_t i = 0; i < row_count; ++i) {
      ret += ppmatrix[i][j];
    }
  }
  return ret;
}

void   matrix_release(int*** pppmatrix, size_t row_count) {
  int **ppmatrix;
  if (pppmatrix && (ppmatrix = *pppmatrix)) {
    for (size_t i = 0; i < row_count; ++i) {
      delete [] ppmatrix[i];
    }
    delete [] ppmatrix;
    ppmatrix = nullptr;
  }
}

