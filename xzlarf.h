#ifndef XZLARF_H
#define XZLARF_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void b_xzlarf(int m, int n, int iv0, double tau, double C[1080], int ic0,
                     double work[3]);
extern void xzlarf(int m, int n, int iv0, double tau, emxArray_real_T *C, int
                   ic0, int ldc, double work[3]);

#endif
