/**********************************************************************************************/
/*  This program is free software; you can redistribute it and/or modify                      */
/*  it under the terms of the GNU General Public License as published by                      */
/*  the Free Software Foundation; either version 2 of the License, or                         */
/*  (at your option) any later version.                                                       */
/*                                                                                            */
/*  This program is distributed in the hope that it will be useful,                           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of                            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                             */
/*  GNU General Public License for more details.                                              */
/*                                                                                            */
/*  You should have received a copy of the GNU General Public License                         */
/*  along with this program; if not, write to the Free Software                               */
/*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA            */
/**********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <float.h>
#include <omp.h>
#include <cmath>

#if CHECK_RESULT
#include <cblas.h>
#endif

#include "interop.h"
#include "interop_args.h"

// Number of multiplications in GEMM
#define FMULS_GEMM(m_, n_, k_) ((m_) * (n_) * (k_))
// Number of additions in GEMM
#define FADDS_GEMM(m_, n_, k_) ((m_) * (n_) * (k_))
// Flops in DGEMM 
#define FLOPS_DGEMM(m_, n_, k_) ( FMULS_GEMM((double)(m_), (double)(n_), \
  (double)(k_)) + FADDS_GEMM((double)(m_), (double)(n_), (double)(k_)) )

int main( int argc, char const *argv[])
{
  const int tile_size = 32;  

  if(argc < 4 || argc > 4)
  {     
    fprintf(stderr, "Usage: ./nanos_xitao M N K\n" );
    return -1;
  }

  // Local variables
  int i, j;
  int m, n, k;
  double alpha; 
  double beta;
  double abs_error;
  double c2;
  double *A;
  double *B;
  double *C;
  double *C_test;
  struct timeval start, end;
  double flops;
  double time_ddss;
    double time_ref;
  double flops_ddss;
  double flops_ref;
  int ret;

  m = atoi( argv[1] );
  n = atoi( argv[2] );
  k = atoi( argv[3] );

  // Set seed 
  srand(time(NULL));


  // Checking inputs
  if ( m < 0 )
  {
    fprintf(stderr, "Illegal value of M, M must be >= 0\n");
    return -1;
  }
  if ( n < 0 )
  {
    fprintf(stderr, "Illegal value of N, N must be >= 0\n");
    return -1;
  }
  if ( k < 0 )
  {
    fprintf(stderr, "Illegal value of K, K must be >= 0\n");
    return -1;
  }

  // Matrices allocation
  A = ( double * ) malloc( sizeof( double ) * m * k );
  B = ( double * ) malloc( sizeof( double ) * k * n );
  C = ( double * ) malloc( sizeof( double ) * m * n );
#ifdef CHECK_RESULT
  C_test = ( double * ) malloc( sizeof( double ) * m * n );
#endif

  // Alpha and beta initialization
  alpha = ( double ) rand() / (double) rand() + DBL_MIN;
  beta  = ( double ) rand() / (double) rand() + DBL_MIN;
 
  // Matrix A, B, C and C_test initialization
  for ( i = 0; i < m; i++ )
  {
    for ( j = 0; j < k; j++ )
    {
      A[ i * k + j ] = ( double ) rand() / (double) rand() 
                + DBL_MIN;
    }
  }
  
  for ( i = 0; i < k; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      B[ i * n + j ] = ( double ) rand() / (double) rand() 
                + DBL_MIN;
    }
  }
  
  for ( i = 0; i < m; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      C[ i * n + j ] = 0.0;
#ifdef CHECK_RESULT
      C_test[ i * n + j ] = 0.0;
#endif
    }
  }

  
  interop_init();
   
  // // DGEMM FLOPS
  flops = FLOPS_DGEMM( m, n, k ); 

  gettimeofday( &start, NULL );

  args_dgemm interop_params = {m, n, k, alpha, A, k, B, n, beta, C, n, tile_size };

  interop_start((void*) &interop_params);
  
  interop_finalize();
  
  gettimeofday( &end, NULL ); 
      
  
  // FLOPS achieved by the ddss_dgemm routine
  time_ddss = (double) ((end.tv_sec * 1e6 + end.tv_usec)
                                        - (start.tv_sec * 1e6 + start.tv_usec));
  flops_ddss = flops / (double) (time_ddss / 1e6);

  fprintf(stdout, "Interop time = %lf us\n", time_ddss);

  fprintf(stdout, "Interop DGEMM GFLOPS = %1.2f\n", flops_ddss / 1e9 );

#ifdef CHECK_RESULT
  gettimeofday( &start, NULL );

  cblas_dgemm( CblasRowMajor,
        CblasNoTrans, CblasNoTrans,
        m, n, k,
        alpha, A, k,
        B, n,
        beta, C_test, n );
  gettimeofday( &end, NULL );
  
  // FLOPS achieved by the (reference) routine
  time_ref = (double) ((end.tv_sec * 1e6 + end.tv_usec)
                                        - (start.tv_sec * 1e6 + start.tv_usec));
  flops_ref = flops / (double) (time_ref / 1e6);
  
  // Error computation

  c2 = 0.0;
  for ( i = 0; i < m; i++ )
  {
    for ( j = 0; j < n; j++ )
    { 
      double diff = C[ i * n + j ] - C_test[ i * n + j ];     
      abs_error += diff * diff;
      c2 += C[ i * n + j ] * C[ i * n + j ];
    }
  }

  fprintf(stdout, "L2. error = %2.3e\n", sqrt(abs_error / c2)); 
  fprintf(stdout, "REF. DGEMM time = %lf us\n", time_ref);
  fprintf(stdout, "REF. DGEMM GFLOPS = %1.2f\n", flops_ref / 1e9 );
#endif
  
  return 0;

}
