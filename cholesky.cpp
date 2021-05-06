#include <lapacke.h>
#include <cstdio>
#include <random>
#include <array>
#include <cassert>
#include <iostream>

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

int main(void)
{
  const int arr_rank = 2;
  const int arr_size = arr_rank * arr_rank;

  std::array<double, arr_size> cov =
      {
          1.0, 0.0, //
          0.2, 1.0  //
      };
  std::array<int, arr_rank> piv;
  int rank = 0;
  double tol = -1.0;
  int info = LAPACKE_dpstrf(LAPACK_ROW_MAJOR, 'L', arr_rank, cov.data(), arr_rank, piv.data(), &rank, tol);
  assert(info == 0);

  int n = 1000;
  std::array<double, arr_rank> mu = {3.0, 2.0};
  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());

  std::normal_distribution<double> dist(0.0, 1.0);
  for (int i = 0; i < n; i++)
  {
    double v1 = dist(engine);
    double v2 = dist(engine);
    std::cout << v1 << " " << v2 << std::endl;
  }
  return EXIT_SUCCESS;
}