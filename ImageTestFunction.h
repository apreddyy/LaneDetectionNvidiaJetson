#ifndef IMAGETESTFUNCTION_H
#define IMAGETESTFUNCTION_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void ImageTestFunction(const emxArray_uint8_T *Binaryimage, double
  Leftpoints[3], double Rightpoints[3]);
extern void ImageTestFunction_free();
extern void ImageTestFunction_init();

#endif
