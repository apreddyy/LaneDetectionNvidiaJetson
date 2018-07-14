/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * processedout_emxAPI.h
 *
 * Code generation for function 'processedout_emxAPI'
 *
 */

#ifndef PROCESSEDOUT_EMXAPI_H
#define PROCESSEDOUT_EMXAPI_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

/* Function Declarations */
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

/* End of code generation (processedout_emxAPI.h) */
