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

#include "interop.h"
#include "xitao_dgemm.h"
#include "ompss_dgemm.h"
#include "interop_args.h"

void interop_init() {
  interop_xitao_init();
  interop_ompss_init();
}

void interop_start(void* args) { 
  args_dgemm* interop_args = (args_dgemm*) args;
 
  interop_xitao_dgemm(interop_args->M,    interop_args->N,   interop_args->K,   interop_args->ALPHA, 
                      interop_args->A,    interop_args->LDA, interop_args->B,   interop_args->LDB, 
                      interop_args->BETA, interop_args->C,   interop_args->LDC, interop_args->tile_size);
}

void interop_finalize() {
  interop_xitao_finalize();
  interop_ompss_finalize();
}
