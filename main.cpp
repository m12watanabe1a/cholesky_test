#include <lapacke.h>
#include <cstdio>
#include <array>

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

int main(int argc, char **argv)
{
  std::array<double, N *N> A = {
      1.0, 0.2, 0.0, //
      0.0, 1.0, 0.0,
      0.0, 0.0, 1.0};

  print_array(A);

  std::array<int, N> piv;
  int rank = 0;
  int info = 0;
  double tol = 1.0e-5;
  std::array<double, 2 * N> work;
  LAPACKE_dpstrf(LAPACK_ROW_MAJOR,'U', N, A.data(), N, piv.data(), &rank, tol);

  printf("%d\n", info);
  print_array(A);

  for(int i =0; i < N; i++)
  {
    printf("%d\n", piv[i]);
  }

  return 0;
}