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

#ifndef XITAO_TILED_GEMM_H
#define XITAO_TILED_GEMM_H
#include "xitao.h"
#include "ompss_dgemm.h"
#include <sched.h>
class xitao_tiled_gemm : public AssemblyTask 
{
	int M; 
	int N; 
	int K; 
  double ALPHA; 
  double *subA;
  int ldA;
  double *subB; 
  int ldB; 
  double BETA;  
  double *subC; 
  int ldC;
public:
	xitao_tiled_gemm(int _M, int _N, int _K,
        double _ALPHA, double *_A, int _LDA,
                       double *_B, int _LDB,
        double _BETA,  double *_C, int _LDC);
	void execute(int thread);
	void cleanup(); 
};

#endif
