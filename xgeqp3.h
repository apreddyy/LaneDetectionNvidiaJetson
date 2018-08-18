#ifndef XGEQP3_H
#define XGEQP3_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void b_xgeqp3(double A[1080], double tau[3], int jpvt[3]);
extern void xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int
                   jpvt[3]);

#endif
