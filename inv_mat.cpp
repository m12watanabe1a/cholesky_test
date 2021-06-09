#include <lapack.h>
#include <lapacke.h>
#include <cstdio>
#include <array>
#include <random>
#include <iostream>

#include <stdio.h>
#include <cassert>
#include <cstring>

void print_array(const int m, const int n, double *arr)
{
  int index = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      printf(" %.3lf ", arr[i * m + j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(void)
{
  lapack_int m = 3;
  lapack_int n = 3;

  double a_orig[m * n] = {
      1, 2, 3, //
      4, 5, 6, //
      7, 8, 9, //
  };

  lapack_int lda = m;
  lapack_int ldb = std::max(m, n);
  lapack_int nrhs = ldb;
  double *a = (double *)malloc(size_t(sizeof(double) * m * n));
  double *b = (double *)malloc(size_t(sizeof(double) * ldb * ldb));
  double *s = (double *)malloc(size_t(sizeof(double) * std::min(m, n)));
  lapack_int rank = 0;
  lapack_int info;
  double rcond = -1.0;

  std::memcpy(a, a_orig, size_t(sizeof(double) * m * n));
  for (int i = 0; i < ldb; ++i)
  {
    b[i * ldb + i] = 1.0;
  }

  print_array(m, n, a);
  info = LAPACKE_dgelss(LAPACK_ROW_MAJOR, m, n, nrhs, a, lda, b, ldb, s, rcond, &rank);
  assert(info == 0);
  print_array(m, n, a);

  std::memcpy(a, a_orig, size_t(sizeof(double) * m * n));
  print_array(m, n, a);
  for (int i = 0; i < ldb; ++i)
  {
    b[i * ldb + i] = 1.0;
  }
  info = LAPACKE_dgelss(LAPACK_ROW_MAJOR, m, n, nrhs, a, lda, b, ldb, s, rcond, &rank);
  assert(info == 0);
  print_array(m, n, a);
  free(a);
  free(b);
  free(s);
  return EXIT_SUCCESS;
}
