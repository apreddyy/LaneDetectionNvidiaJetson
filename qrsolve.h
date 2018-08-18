#ifndef QRSOLVE_H
#define QRSOLVE_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void b_qrsolve(const double A[1080], const double B[360], double Y[3],
                      int *rankR);
extern void qrsolve(const emxArray_real_T *A, const emxArray_real_T *B, double
                    Y[3], int *rankR);

#endif
