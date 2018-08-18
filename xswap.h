#ifndef XSWAP_H
#define XSWAP_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void b_xswap(double x[1080], int ix0, int iy0);
extern void xswap(int n, emxArray_real_T *x, int ix0, int iy0);

#endif
