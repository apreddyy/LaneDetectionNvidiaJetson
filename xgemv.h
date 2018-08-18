#ifndef XGEMV_H
#define XGEMV_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void b_xgemv(int m, int n, const double A[1080], int ia0, const double x
                    [1080], int ix0, double y[3]);
extern void xgemv(int m, int n, const emxArray_real_T *A, int ia0, int lda,
                  const emxArray_real_T *x, int ix0, double y[3]);

#endif
