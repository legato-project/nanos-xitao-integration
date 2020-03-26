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

#ifndef XITAO_DGEMM_H
#define XITAO_DGEMM_H
#include "ompss_dgemm.h"
#include <assert.h> 

void interop_xitao_init();
void interop_xitao_dgemm(int M, int N, int K,
        double ALPHA, double *A, int LDA,
                      double *B, int LDB,
        double BETA,  double *C, int LDC, int tile_size);
void interop_xitao_finalize();
#endif
