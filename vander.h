#ifndef VANDER_H
#define VANDER_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void b_vander(const double v[360], double A[1080]);
extern void vander(const emxArray_real_T *v, emxArray_real_T *A);

#endif
