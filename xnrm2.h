#ifndef XNRM2_H
#define XNRM2_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern double b_xnrm2(const double x[1080], int ix0);
extern double c_xnrm2(int n, const double x[1080], int ix0);
extern double xnrm2(int n, const emxArray_real_T *x, int ix0);

#endif
