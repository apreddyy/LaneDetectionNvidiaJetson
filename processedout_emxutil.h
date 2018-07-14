/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * processedout_emxutil.h
 *
 * Code generation for function 'processedout_emxutil'
 *
 */

#ifndef PROCESSEDOUT_EMXUTIL_H
#define PROCESSEDOUT_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

/* Function Declarations */
extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int
  oldNumel);
extern void emxEnsureCapacity_boolean_T1(emxArray_boolean_T *emxArray, int
  oldNumel);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T1(emxArray_real_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_uint8_T(emxArray_uint8_T *emxArray, int oldNumel);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int
  b_numDimensions);
extern void emxInit_boolean_T1(emxArray_boolean_T **pEmxArray, int
  b_numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int b_numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int b_numDimensions);
extern void emxInit_real_T1(emxArray_real_T **pEmxArray, int b_numDimensions);
extern void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int b_numDimensions);

#endif

/* End of code generation (processedout_emxutil.h) */
