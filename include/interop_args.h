#ifndef _ARGS_DGEMM_H
#define _ARGS_DGEMM_H

struct args_dgemm {
  int M;
  int N;
  int K;
  double ALPHA;
  double *A;
  int LDA;
  double *B;
  int LDB;
  double BETA;
  double *C;
  int LDC;
  int tile_size;
  int res;
} __attribute__ ((aligned (64)));

#endif