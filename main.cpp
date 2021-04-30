#include <lapacke.h>
#include <cstdio>
#include <array>
#include <random>

const int N = 2;
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

void reset_array(std::array<double, N * N> &arr, std::array<int, N> &piv, std::array<double, N * N> &ret)
{
  for (int i = 0; i < N; i++)
  {
    int index_i = piv[i] - 1;
    for (int j = 0; j < N; j++)
    {
      int index_j = piv[j] - 1;
      ret[i * N + j] = arr[index_i * N + index_j];
    }
  }
  return;
}

int main(int argc, char **argv)
{
  std::array<double, N *N> A = {
      1.0, 0.2, //
      0.0, 1.0};

  std::array<int, N> piv;
  int rank = 0;
  int info = 0;
  double tol = -1.0;

  std::array<double, 2 * N> work;
  LAPACKE_dpstrf(LAPACK_ROW_MAJOR, 'U', N, A.data(), N, piv.data(), &rank, tol);

  print_array(A);

  std::array<double, N * N> L;
  reset_array(A, piv, L);
  print_array(L);

  int n = 1000;
  std::array<double, N> mu = {3.0, 2.0};
  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());

  std::normal_distribution<double> dist(0.0, 1.0);
  for( int i = 0; i < n; i++)
  {
    double v1 = dist(engine);
    double v2 = dist(engine);

    


  }

  return 0;
}