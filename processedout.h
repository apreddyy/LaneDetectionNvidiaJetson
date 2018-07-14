/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * processedout.h
 *
 * Code generation for function 'processedout'
 *
 */

#ifndef PROCESSEDOUT_H
#define PROCESSEDOUT_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

/* Variable Declarations */
extern double counter;
extern double left_fit[3];
extern double right_fit[3];
extern double last_left[3];
extern double last_right[3];
extern omp_nest_lock_t emlrtNestLockGlobal;

/* Function Declarations */
extern void processedout(const emxArray_uint8_T *Binaryimage, double PointsA[720],
  double PointsB[720], int *AlertSide, double center_data[], int center_size[1],
  double *left_curvature, double *right_curveature);
extern void processedout_initialize();
extern void processedout_terminate();

#endif

/* End of code generation (processedout.h) */
