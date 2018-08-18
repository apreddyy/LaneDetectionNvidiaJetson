#ifndef PROCESSEDOUT_EMXAPI_H
#define PROCESSEDOUT_EMXAPI_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern emxArray_uint8_T *emxCreateND_uint8_T(int b_numDimensions, int *b_size);
extern emxArray_uint8_T *emxCreateWrapperND_uint8_T(unsigned char *b_data, int
  b_numDimensions, int *b_size);
extern emxArray_uint8_T *emxCreateWrapper_uint8_T(unsigned char *b_data, int
  rows, int cols);
extern emxArray_uint8_T *emxCreate_uint8_T(int rows, int cols);
extern void emxDestroyArray_uint8_T(emxArray_uint8_T *emxArray);
extern void emxInitArray_uint8_T(emxArray_uint8_T **pEmxArray, int
  b_numDimensions);

#endif
