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
}

inline void GetInvMat(
    double *const mat,
    const uint32_t &mat_width,
    const uint32_t &mat_height)
{
  const int m = mat_width;
  printf("m: %d\n", m);
  const int n = mat_height;
  printf("n: %d\n", n);

  const int lda = m;
  const int ldb = std::max(m, n);
  const int nrhs = ldb;

  double *b = (double *)malloc(sizeof(double) * ldb * ldb);
  double *s = (double *)malloc(sizeof(double) * std::min(m, n));
  lapack_int rank = 0;
  lapack_int info;
  double rcond = -1.0;

  for (int i = 0; i < ldb; ++i)
  {
    b[i * ldb + i] = 1.0;
  }
  double tmp[0];
  info = LAPACKE_dgelss_work(LAPACK_ROW_MAJOR, n, m, nrhs, mat, lda, b, ldb, s, rcond, &rank, tmp, -1);
  assert(info == 0);
  int lwork = tmp[0];
  double *work = (double *)malloc(sizeof(double) * lwork);
  info = LAPACKE_dgelss_work(LAPACK_ROW_MAJOR, n, m, nrhs, mat, lda, b, ldb, s, rcond, &rank, work, lwork);

  if (mat_width > mat_height)
  {
    for (uint32_t i = 0; i < mat_width; ++i)
    {
      std::memcpy(&mat[i * mat_height], &b[i * ldb], sizeof(double) * mat_height);
    }
  }
  else
  {
    std::memcpy(&mat[0], &b[0], sizeof(double) * mat_width * mat_height);
  }

  free(b);
  free(s);
  free(work);
}

int main(void)
{
  int mat_width = 4;
  int mat_height = 3;
  double mat_orig[mat_width * mat_height] = {
      1, 2, 3, 4,   //
      5, 6, 7, 8,   //
      9, 10, 11, 12 //
  };
  double mat[mat_width * mat_height];
  std::memcpy(mat, mat_orig, sizeof(double)*mat_width*mat_height);
  for(int i = 0; i < mat_height; ++i)
  {
    for(int j = 0; j < mat_width; ++j)
    {
      printf("%.1lf ", mat[i*mat_width + j]);
    }
    printf("\n");
  }

  GetInvMat(mat, mat_width, mat_height);
  for (int i = 0; i < mat_width; ++i)
  {
    for (int j = 0; j < mat_height; ++j)
    {
      int idx = i * mat_height + j;
      std::cout << mat[idx] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::memcpy(mat, mat_orig, sizeof(double)*mat_width*mat_height);
  for(int i = 0; i < mat_height; ++i)
  {
    for(int j = 0; j < mat_width; ++j)
    {
      printf("%.1lf ", mat[i*mat_width + j]);
    }
    printf("\n");
  }
  GetInvMat(mat, mat_width, mat_height);
  for (int i = 0; i < mat_width; ++i)
  {
    for (int j = 0; j < mat_height; ++j)
    {
      int idx = i * mat_height + j;
      std::cout << mat[idx] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
