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