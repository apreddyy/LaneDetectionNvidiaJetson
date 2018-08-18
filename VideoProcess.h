#ifndef VIDEOPROCESS_H
#define VIDEOPROCESS_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void VideoProcess(const emxArray_uint8_T *Binaryimage, const double left
  [3], const double right[3], double Leftpoints[3], double Rightpoints[3]);

#endif
