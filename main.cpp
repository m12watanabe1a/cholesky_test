#include <lapacke.h>
#include <cstdio>
#include <array>
#include <random>

const int N = 3;
void print_array(std::array<double, N * N> &arr)
{
  int index = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf(" %.3lf ", arr[i * N + j]);
    }
    printf("\n");
  }
}

void reset_array(const double *const arr, const int *const piv, const int &arr_size, double *const ret)
{
  for (int i = 0; i < arr_size; i++)
  {
    int index_i = piv[i] - 1;
    for (int j = 0; j < arr_size; j++)
    {
      if (i < j)
        continue;
      int index_j = piv[j] - 1;
      ret[i * arr_size + j] = arr[index_i * arr_size + index_j];
    }
  }
  return;
}

void reset_array_test(const double *const arr, const int &arr_size, double *const ret)
{
  for (int i = 0; i < arr_size; i++)
  {
    for (int j = 0; j < arr_size; j++)
    {
      if (i < j)
        continue;
      ret[i * arr_size + j] = 1.0;
    }
  }
  return;
}

int main(int argc, char **argv)
{
  std::array<double, N *N> A = {
      1.0, 0.0, 0.0, //
      0.2, 1.0, 0.0, //
      0.0, 0.0, 1.0};

  std::array<int, N> piv;
  int rank = 0;
  int info = 0;
  double tol = -1.0;

  LAPACKE_dpstrf(LAPACK_ROW_MAJOR, 'L', N, A.data(), N, piv.data(), &rank, tol);

  print_array(A);

  std::array<double, N * N> L;
  reset_array(A.data(), piv.data(), N, L.data());

  print_array(L);

  std::array<double, N *N> test = {0.0};
  std::array<double, N *N> ret = {0.0};
  reset_array_test(test.data(), N, ret.data());
  print_array(ret);
  return 0;
}