#ifndef PROCESSEDOUT_H
#define PROCESSEDOUT_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void processedout(const emxArray_uint8_T *Binaryimage, double PointsA[720],
  double PointsB[720], double *AlertSide, double center_data[], int center_size
  [1], double *left_curvature, double *right_curveature);

#endif
