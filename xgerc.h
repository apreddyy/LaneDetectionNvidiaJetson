#ifndef XGERC_H
#define XGERC_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void b_xgerc(int m, int n, double alpha1, int ix0, const double y[3],
                    double A[1080], int ia0);
extern void xgerc(int m, int n, double alpha1, int ix0, const double y[3],
                  emxArray_real_T *A, int ia0, int lda);

#endif
