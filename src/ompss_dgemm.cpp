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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <nanos6.h>
#include <nanos6/library-mode.h>
#include <nanos6/bootstrap.h>
#include <iostream>
#include "nanos6_helpers.h"
#include "interop_args.h"


void offload_ompss_dgemm(void *void_args) {
  args_dgemm *args = (args_dgemm *)void_args;
  for(int i = 0; i < args->M; ++i) {
    for(int j = 0; j < args->N; ++j) {
      args->C[i * args->LDC + j] *= args->BETA;  
    }   
    for(int k = 0; k < args->K; ++k) {
      auto&& temp = args->ALPHA * args->A[i * args->LDA + k]; 
      for(int j = 0; j < args->N; ++j) {
        args->C[i * args->LDC + j] += temp * args->B[k * args->LDB + j];
      }
    }
  }
}


void interop_ompss_init() {
  char const *error = nanos6_library_mode_init();
  if (error != NULL) {
    fprintf(stderr, "Error initializing Nanos6: %s\n", error);
    exit(0);
  }
}

void interop_ompss_dgemm(cpu_set_t *cpu_mask,
      int M, int N, int K,
        double ALPHA, double *A, int LDA,
                      double *B, int LDB,
        double BETA,  double *C, int LDC) {
  condition_variable_t cond_var = COND_VAR_INIT;
  args_dgemm args;
  args.M = M;
  args.N = N;
  args.K = K;
  args.ALPHA = ALPHA;
  args.A = A;
  args.LDA = LDA;
  args.B = B;
  args.LDB = LDB;
  args.BETA = BETA;
  args.C = C;
  args.LDC = LDC;
  args.res = -1;
  nanos6_spawn_function(offload_ompss_dgemm, &args, condition_variable_callback, &cond_var, "offload");
  wait_condition_variable(&cond_var);
}

void interop_ompss_finalize() {
  nanos6_shutdown();  
}
