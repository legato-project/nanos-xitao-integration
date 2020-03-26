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

#include "xitao_dgemm.h"
#include "xitao.h"
#include "xitao_tiled_gemm.h"

void interop_xitao_init() {
  gotao_init(); 
}

void interop_xitao_dgemm(int M, int N, int K,
        double ALPHA, double *A, int LDA,
                      double *B, int LDB,
        double BETA,  double *C, int LDC, int tile_size) {
  assert(M % tile_size == 0);
  assert(N % tile_size == 0);
  for(int m = 0; m < M; m += tile_size) {
    for(int n = 0; n < N; n += tile_size) { 
        xitao_tiled_gemm* tiled_tao = 
           new xitao_tiled_gemm(
            tile_size, tile_size, K, 
            ALPHA, A + m * LDA, LDA, B + n, LDB, 
            BETA , C + m * LDC + n, LDC);              
            gotao_push(tiled_tao, (n * m) % gotao_nthreads);
    }
  }
  gotao_start();
}


void interop_xitao_finalize(){
  gotao_fini();
}

