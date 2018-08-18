#ifndef POLYFIT_H
#define POLYFIT_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void b_polyfit(const double x[360], const double y[360], double p[3]);
extern void polyfit(const emxArray_real_T *x, const emxArray_real_T *y, double
                    p[3]);

#endif
