#include <omp.h>
#include <stdio.h>

int main() {
  int N, M;
  N = M = 5;
  int A[N], B[M];

#pragma omp parallel
  {
#pragma omp for schedule(dynamic) nowait order(reproducible : concurrent)
    for (int I = 0; I < N; I++) {
      // printf("I-> %d: %d: %d\n", omp_get_team_num(), omp_get_thread_num(),
      // i);
      A[I] = I;
    }
#pragma omp for order(reproducible : concurrent)
    for (int J = 0; J < M; J++) {
      // printf("J-> %d: %d: %d\n", omp_get_team_num(), omp_get_thread_num(),
      // j);
      B[J] = A[J] * J;
    }
  }
  for (int J = 0; J < N; J++) {
    if (B[J] != A[J] * A[J]) {
      printf("\nDidn't execute in consistent schedules\n");
      return 0;
    }
  }
  printf("\nLoops executed with consistent schedules\n");
  return 0;
}