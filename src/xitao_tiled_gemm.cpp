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

#include "xitao_tiled_gemm.h"
xitao_tiled_gemm::xitao_tiled_gemm(int _M, int _N, int _K,
        double _ALPHA, double *_A, int _LDA,
                       double *_B, int _LDB,
        double _BETA,  double *_C, int _LDC) : 
		  M(_M), N(_N), K(_K),
		  ALPHA(_ALPHA), subA(_A), ldA(_LDA), subB(_B),
		  ldB(_LDB), BETA(_BETA), subC(_C), ldC(_LDC), AssemblyTask(1) { }


void xitao_tiled_gemm::execute(int thread) {
   cpu_set_t cpu_mask; 
    CPU_ZERO(&cpu_mask);
    for(int i = leader; i < width; i++) {
      CPU_SET(i, &cpu_mask);
    } 
    if(thread == leader) interop_ompss_dgemm(&cpu_mask,
                         M, N, K, ALPHA, subA, ldA, subB, ldB, BETA, subC, ldC);	       
}

void xitao_tiled_gemm::cleanup() { }

