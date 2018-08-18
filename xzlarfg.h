#ifndef XZLARFG_H
#define XZLARFG_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern double b_xzlarfg(int n, double *alpha1, double x[1080], int ix0);
extern double xzlarfg(int n, double *alpha1, emxArray_real_T *x, int ix0);

#endif
