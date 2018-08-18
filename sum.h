#ifndef SUM_H
#define SUM_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void sum(const emxArray_uint8_T *x, double y_data[], int y_size[2]);

#endif
