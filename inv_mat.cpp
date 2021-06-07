#include <lapacke.h>
#include <cstdio>
#include <array>
#include <random>
#include <iostream>

#include <stdio.h>
#include <cassert>

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
}

int main(void)
{
  const int m = 3;
  const int n = 3;
  const int lda = m;
  const int ldb = std::max(m, n);
  const int nrhs = ldb;

  double *a = (double *)malloc(sizeof(double) * lda * n);
  double *b = (double *)malloc(sizeof(double) * ldb * ldb);
  double *s = (double *)malloc(sizeof(double) * std::min(m, n));
  lapack_int rank, info;
  double rcond = -1.0;

  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  a[3] = 4;
  a[4] = 5;
  a[5] = 6;
  a[6] = 7;
  a[7] = 8;
  a[8] = 9;

  for (int i = 0; i < ldb; ++i)
  {
    b[i * ldb + i] = 1.0;
  }

  for (int i = 0; i < ldb; ++i)
  {
    for (int j = 0; j < ldb; ++j)
    {
      int idx = i * ldb + j;
      std::cout << b[idx] << " ";
    }
    std::cout << std::endl;
  }

  info = LAPACKE_dgelss(LAPACK_ROW_MAJOR, m, n, nrhs, a, lda, b, ldb, s, rcond, &rank);
  assert(info == 0);
  if (info == 0)
  {
    printf("rank:\t%d\n", rank);
    for (int i = 0; i < ldb; ++i)
    {
      for (int j = 0; j < ldb; ++j)
      {
        printf("%lf\t", b[i * ldb + j]);
      }
      printf("\n");
    }
  }
  delete a;
  delete b;
  delete s;
  return EXIT_SUCCESS;
}