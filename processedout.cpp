/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * processedout.cpp
 *
 * Code generation for function 'processedout'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include <string.h>
#include <cmath>
#include <math.h>
#include <float.h>
#include "processedout.h"
#include "processedout_emxutil.h"

/* Type Definitions */
typedef struct {
  bool Neighborhood[9];
  int ImageSize[2];
  double InteriorStart[2];
  int InteriorEnd[2];
  int ImageNeighborLinearOffsets[5];
  double Padding;
  double PadValue;
  bool ProcessBorder;
  double NeighborhoodCenter;
  int NeighborLinearIndices[5];
  int NeighborSubscriptOffsets[10];
} c_images_internal_coder_Neighbo;

/* Named Constants */
#define b_counter                      (120.0)

/* Variable Definitions */
double counter;
double left_fit[3];
double right_fit[3];
double last_left[3];
double last_right[3];
static emxArray_real_T *Leftxout;
static bool Leftxout_not_empty;
static emxArray_real_T *Leftyout;
static bool Leftyout_not_empty;
static emxArray_real_T *Rightxout;
static bool Rightxout_not_empty;
static emxArray_real_T *Rightyout;
static bool Rightyout_not_empty;
omp_nest_lock_t emlrtNestLockGlobal;

/* Function Declarations */
static void ImageTestFunction(const emxArray_uint8_T *Binaryimage, double
  Leftpoints[3], double Rightpoints[3]);
static void ImageTestFunction_free();
static void ImageTestFunction_init();
static void LSQFromQR(const emxArray_real_T *A, const double tau_data[], const
                      int jpvt[3], emxArray_real_T *B, int rankA, double Y[3]);
static void VideoProcess(const emxArray_uint8_T *Binaryimage, const double left
  [3], const double right[3], double Leftpoints[3], double Rightpoints[3]);
static int b_ilazlc(int m, int n, const double A[1080], int ia0);
static void b_polyfit(const double x[360], const double y[360], double p[3]);
static void b_qrsolve(const double A[1080], const double B[360], double Y[3],
                      int *rankR);
static int b_rankFromQR(const double A[1080]);
static void b_sqrt(double *x);
static void b_vander(const double v[360], double A[1080]);
static void b_xgemv(int m, int n, const double A[1080], int ia0, const double x
                    [1080], int ix0, double y[3]);
static void b_xgeqp3(double A[1080], double tau[3], int jpvt[3]);
static void b_xgerc(int m, int n, double alpha1, int ix0, const double y[3],
                    double A[1080], int ia0);
static double b_xnrm2(const double x[1080], int ix0);
static void b_xswap(double x[1080], int ix0, int iy0);
static void b_xzlarf(int m, int n, int iv0, double tau, double C[1080], int ic0,
                     double work[3]);
static double b_xzlarfg(int n, double *alpha1, double x[1080], int ix0);
static void bwareaopen(const emxArray_uint8_T *varargin_1, emxArray_boolean_T
  *BW2);
static void bwlabel(const emxArray_boolean_T *varargin_1, emxArray_real_T *L,
                    double *numComponents);
static double c_xnrm2(int n, const double x[1080], int ix0);
static int div_s32(int numerator, int denominator);
static int ilazlc(int m, int n, const emxArray_real_T *A, int ia0, int lda);
static bool isrow(const emxArray_boolean_T *x);
static int ixamax(int n, const double x[3], int ix0);
static double mean(const emxArray_real_T *x);
static void morphopAlgo(const emxArray_boolean_T *A, emxArray_boolean_T *B);
static void polyfit(const emxArray_real_T *x, const emxArray_real_T *y, double
                    p[3]);
static void power(const emxArray_real_T *a, emxArray_real_T *y);
static void qrsolve(const emxArray_real_T *A, const emxArray_real_T *B, double
                    Y[3], int *rankR);
static int rankFromQR(const emxArray_real_T *A);
static double rt_hypotd_snf(double u0, double u1);
static double rt_powd_snf(double u0, double u1);
static double rt_remd_snf(double u0, double u1);
static void sum(const emxArray_uint8_T *x, double y_data[], int y_size[2]);
static void vander(const emxArray_real_T *v, emxArray_real_T *A);
static void xgemv(int m, int n, const emxArray_real_T *A, int ia0, int lda,
                  const emxArray_real_T *x, int ix0, double y[3]);
static void xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int
                   jpvt[3]);
static void xgerc(int m, int n, double alpha1, int ix0, const double y[3],
                  emxArray_real_T *A, int ia0, int lda);
static double xnrm2(int n, const emxArray_real_T *x, int ix0);
static void xswap(int n, emxArray_real_T *x, int ix0, int iy0);
static void xzlarf(int m, int n, int iv0, double tau, emxArray_real_T *C, int
                   ic0, int ldc, double work[3]);
static double xzlarfg(int n, double *alpha1, emxArray_real_T *x, int ix0);

/* Function Definitions */
static void ImageTestFunction(const emxArray_uint8_T *Binaryimage, double
  Leftpoints[3], double Rightpoints[3])
{
  int nx;
  emxArray_int32_T *j;
  emxArray_int32_T *ii;
  int idx;
  int i1;
  int b_ii;
  emxArray_int32_T *nonzeroy;
  int jj;
  bool exitg1;
  int loop_ub;
  bool guard1 = false;
  emxArray_int32_T *nonzerox;
  emxArray_uint8_T *b_Binaryimage;
  double histI_data[640];
  int histI_size[2];
  double midpoint;
  double varargin_1_data[640];
  double rightcurrent;
  double leftcurrent;
  emxArray_int32_T *good_left_inds;
  emxArray_int32_T *good_right_inds;
  emxArray_int32_T *leftx;
  emxArray_int32_T *lefty;
  emxArray_int32_T *righty;
  emxArray_boolean_T *x;
  emxArray_real_T *b_nonzerox;
  int windows;
  int win_y_high;
  nx = Binaryimage->size[0] * Binaryimage->size[1];
  emxInit_int32_T(&j, 1);
  emxInit_int32_T(&ii, 1);
  if (nx == 0) {
    i1 = ii->size[0];
    ii->size[0] = 0;
    emxEnsureCapacity_int32_T(ii, i1);
    i1 = j->size[0];
    j->size[0] = 0;
    emxEnsureCapacity_int32_T(j, i1);
  } else {
    idx = 0;
    i1 = ii->size[0];
    ii->size[0] = nx;
    emxEnsureCapacity_int32_T(ii, i1);
    i1 = j->size[0];
    j->size[0] = nx;
    emxEnsureCapacity_int32_T(j, i1);
    b_ii = 1;
    jj = 1;
    exitg1 = false;
    while ((!exitg1) && (jj <= Binaryimage->size[1])) {
      guard1 = false;
      if (Binaryimage->data[(b_ii + Binaryimage->size[0] * (jj - 1)) - 1] != 0)
      {
        idx++;
        ii->data[idx - 1] = b_ii;
        j->data[idx - 1] = jj;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        b_ii++;
        if (b_ii > Binaryimage->size[0]) {
          b_ii = 1;
          jj++;
        }
      }
    }

    if (nx == 1) {
      if (idx == 0) {
        i1 = ii->size[0];
        ii->size[0] = 0;
        emxEnsureCapacity_int32_T(ii, i1);
        i1 = j->size[0];
        j->size[0] = 0;
        emxEnsureCapacity_int32_T(j, i1);
      }
    } else {
      i1 = ii->size[0];
      if (1 > idx) {
        ii->size[0] = 0;
      } else {
        ii->size[0] = idx;
      }

      emxEnsureCapacity_int32_T(ii, i1);
      i1 = j->size[0];
      if (1 > idx) {
        j->size[0] = 0;
      } else {
        j->size[0] = idx;
      }

      emxEnsureCapacity_int32_T(j, i1);
    }
  }

  emxInit_int32_T(&nonzeroy, 1);
  i1 = nonzeroy->size[0];
  nonzeroy->size[0] = ii->size[0];
  emxEnsureCapacity_int32_T(nonzeroy, i1);
  loop_ub = ii->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    nonzeroy->data[i1] = ii->data[i1];
  }

  emxInit_int32_T(&nonzerox, 1);
  i1 = nonzerox->size[0];
  nonzerox->size[0] = j->size[0];
  emxEnsureCapacity_int32_T(nonzerox, i1);
  loop_ub = j->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    nonzerox->data[i1] = j->data[i1];
  }

  emxFree_int32_T(&j);
  emxInit_uint8_T(&b_Binaryimage, 2);
  loop_ub = Binaryimage->size[1];
  i1 = b_Binaryimage->size[0] * b_Binaryimage->size[1];
  b_Binaryimage->size[0] = 181;
  b_Binaryimage->size[1] = loop_ub;
  emxEnsureCapacity_uint8_T(b_Binaryimage, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    for (nx = 0; nx < 181; nx++) {
      b_Binaryimage->data[nx + b_Binaryimage->size[0] * i1] = Binaryimage->data
        [(nx + Binaryimage->size[0] * i1) + 179];
    }
  }

  sum(b_Binaryimage, histI_data, histI_size);
  midpoint = (double)histI_size[1] / 2.0;
  emxFree_uint8_T(&b_Binaryimage);
  if (50.0 > midpoint) {
    i1 = 1;
    nx = 1;
  } else {
    i1 = 50;
    nx = (int)midpoint + 1;
  }

  loop_ub = nx - i1;
  for (jj = 0; jj < loop_ub; jj++) {
    varargin_1_data[jj] = histI_data[(i1 + jj) - 1];
  }

  jj = (nx - i1) - 1;
  if (nx - i1 <= 2) {
    if (nx - i1 == 1) {
      idx = 1;
    } else if ((histI_data[i1 - 1] < histI_data[i1]) || (rtIsNaN(histI_data[i1 -
      1]) && (!rtIsNaN(histI_data[i1])))) {
      idx = 2;
    } else {
      idx = 1;
    }
  } else {
    if (!rtIsNaN(histI_data[i1 - 1])) {
      idx = 1;
    } else {
      idx = 0;
      b_ii = 2;
      exitg1 = false;
      while ((!exitg1) && (b_ii <= nx - i1)) {
        if (!rtIsNaN(varargin_1_data[b_ii - 1])) {
          idx = b_ii;
          exitg1 = true;
        } else {
          b_ii++;
        }
      }
    }

    if (idx == 0) {
      idx = 1;
    } else {
      rightcurrent = histI_data[(i1 + idx) - 2];
      for (b_ii = idx; b_ii < jj + 1; b_ii++) {
        if (rightcurrent < varargin_1_data[b_ii]) {
          rightcurrent = varargin_1_data[b_ii];
          idx = b_ii + 1;
        }
      }
    }
  }

  loop_ub = -(int)midpoint;
  for (i1 = 0; i1 <= loop_ub + 640; i1++) {
    varargin_1_data[i1] = histI_data[((int)midpoint + i1) - 1];
  }

  if (!rtIsNaN(histI_data[(int)midpoint - 1])) {
    jj = 1;
  } else {
    jj = 0;
    b_ii = 2;
    exitg1 = false;
    while ((!exitg1) && (b_ii <= 641 - (int)midpoint)) {
      if (!rtIsNaN(varargin_1_data[b_ii - 1])) {
        jj = b_ii;
        exitg1 = true;
      } else {
        b_ii++;
      }
    }
  }

  if (jj == 0) {
    jj = 1;
  } else {
    rightcurrent = histI_data[((int)midpoint + jj) - 2];
    for (b_ii = jj + 1; b_ii <= 641 - (int)midpoint; b_ii++) {
      if (rightcurrent < histI_data[((int)midpoint + b_ii) - 2]) {
        rightcurrent = histI_data[((int)midpoint + b_ii) - 2];
        jj = b_ii;
      }
    }
  }

  leftcurrent = (double)idx + 50.0;
  rightcurrent = (double)jj + midpoint;
  emxInit_int32_T(&good_left_inds, 1);
  emxInit_int32_T(&good_right_inds, 1);
  emxInit_int32_T(&leftx, 1);
  emxInit_int32_T(&lefty, 1);
  emxInit_int32_T(&righty, 1);
  emxInit_boolean_T1(&x, 1);
  emxInit_real_T(&b_nonzerox, 1);
  for (windows = 0; windows < 9; windows++) {
    jj = 360 - (windows + 2) * 40;
    win_y_high = 360 - (1 + windows) * 40;
    i1 = x->size[0];
    x->size[0] = nonzeroy->size[0];
    emxEnsureCapacity_boolean_T1(x, i1);
    loop_ub = nonzeroy->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      x->data[i1] = ((nonzeroy->data[i1] >= jj) && (nonzeroy->data[i1] <
        win_y_high) && (nonzerox->data[i1] >= leftcurrent - 60.0) &&
                     (nonzerox->data[i1] < leftcurrent + 60.0));
    }

    nx = x->size[0];
    idx = 0;
    i1 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity_int32_T(ii, i1);
    b_ii = 1;
    exitg1 = false;
    while ((!exitg1) && (b_ii <= nx)) {
      if (x->data[b_ii - 1]) {
        idx++;
        ii->data[idx - 1] = b_ii;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          b_ii++;
        }
      } else {
        b_ii++;
      }
    }

    if (x->size[0] == 1) {
      if (idx == 0) {
        i1 = ii->size[0];
        ii->size[0] = 0;
        emxEnsureCapacity_int32_T(ii, i1);
      }
    } else {
      i1 = ii->size[0];
      if (1 > idx) {
        ii->size[0] = 0;
      } else {
        ii->size[0] = idx;
      }

      emxEnsureCapacity_int32_T(ii, i1);
    }

    i1 = good_left_inds->size[0];
    good_left_inds->size[0] = ii->size[0];
    emxEnsureCapacity_int32_T(good_left_inds, i1);
    loop_ub = ii->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      good_left_inds->data[i1] = ii->data[i1];
    }

    i1 = x->size[0];
    x->size[0] = nonzeroy->size[0];
    emxEnsureCapacity_boolean_T1(x, i1);
    loop_ub = nonzeroy->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      x->data[i1] = ((nonzeroy->data[i1] >= jj) && (nonzeroy->data[i1] <
        win_y_high) && (nonzerox->data[i1] >= rightcurrent - 60.0) &&
                     (nonzerox->data[i1] < rightcurrent + 60.0));
    }

    nx = x->size[0];
    idx = 0;
    i1 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity_int32_T(ii, i1);
    b_ii = 1;
    exitg1 = false;
    while ((!exitg1) && (b_ii <= nx)) {
      if (x->data[b_ii - 1]) {
        idx++;
        ii->data[idx - 1] = b_ii;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          b_ii++;
        }
      } else {
        b_ii++;
      }
    }

    if (x->size[0] == 1) {
      if (idx == 0) {
        i1 = ii->size[0];
        ii->size[0] = 0;
        emxEnsureCapacity_int32_T(ii, i1);
      }
    } else {
      i1 = ii->size[0];
      if (1 > idx) {
        ii->size[0] = 0;
      } else {
        ii->size[0] = idx;
      }

      emxEnsureCapacity_int32_T(ii, i1);
    }

    i1 = good_right_inds->size[0];
    good_right_inds->size[0] = ii->size[0];
    emxEnsureCapacity_int32_T(good_right_inds, i1);
    loop_ub = ii->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      good_right_inds->data[i1] = ii->data[i1];
    }

    if (good_left_inds->size[0] > 50) {
      i1 = b_nonzerox->size[0];
      b_nonzerox->size[0] = good_left_inds->size[0];
      emxEnsureCapacity_real_T1(b_nonzerox, i1);
      loop_ub = good_left_inds->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_nonzerox->data[i1] = nonzerox->data[good_left_inds->data[i1] - 1];
      }

      leftcurrent = mean(b_nonzerox);
    }

    if (good_right_inds->size[0] > 50) {
      i1 = b_nonzerox->size[0];
      b_nonzerox->size[0] = good_right_inds->size[0];
      emxEnsureCapacity_real_T1(b_nonzerox, i1);
      loop_ub = good_right_inds->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_nonzerox->data[i1] = nonzerox->data[good_right_inds->data[i1] - 1];
      }

      rightcurrent = mean(b_nonzerox);
    }

    i1 = leftx->size[0];
    leftx->size[0] = good_left_inds->size[0];
    emxEnsureCapacity_int32_T(leftx, i1);
    loop_ub = good_left_inds->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      leftx->data[i1] = nonzerox->data[good_left_inds->data[i1] - 1];
    }

    i1 = lefty->size[0];
    lefty->size[0] = good_left_inds->size[0];
    emxEnsureCapacity_int32_T(lefty, i1);
    loop_ub = good_left_inds->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      lefty->data[i1] = nonzeroy->data[good_left_inds->data[i1] - 1];
    }

    i1 = good_left_inds->size[0];
    good_left_inds->size[0] = good_right_inds->size[0];
    emxEnsureCapacity_int32_T(good_left_inds, i1);
    loop_ub = good_right_inds->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      good_left_inds->data[i1] = nonzerox->data[good_right_inds->data[i1] - 1];
    }

    i1 = righty->size[0];
    righty->size[0] = good_right_inds->size[0];
    emxEnsureCapacity_int32_T(righty, i1);
    loop_ub = good_right_inds->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      righty->data[i1] = nonzeroy->data[good_right_inds->data[i1] - 1];
    }

    if ((!Leftxout_not_empty) && (!Leftyout_not_empty) && (!Rightxout_not_empty)
        && (!Rightyout_not_empty)) {
      i1 = Leftxout->size[0];
      Leftxout->size[0] = leftx->size[0];
      emxEnsureCapacity_real_T1(Leftxout, i1);
      loop_ub = leftx->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        Leftxout->data[i1] = leftx->data[i1];
      }

      Leftxout_not_empty = !(Leftxout->size[0] == 0);
      i1 = Leftyout->size[0];
      Leftyout->size[0] = lefty->size[0];
      emxEnsureCapacity_real_T1(Leftyout, i1);
      loop_ub = lefty->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        Leftyout->data[i1] = lefty->data[i1];
      }

      Leftyout_not_empty = !(Leftyout->size[0] == 0);
      i1 = Rightxout->size[0];
      Rightxout->size[0] = good_left_inds->size[0];
      emxEnsureCapacity_real_T1(Rightxout, i1);
      loop_ub = good_left_inds->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        Rightxout->data[i1] = good_left_inds->data[i1];
      }

      Rightxout_not_empty = !(Rightxout->size[0] == 0);
      i1 = Rightyout->size[0];
      Rightyout->size[0] = righty->size[0];
      emxEnsureCapacity_real_T1(Rightyout, i1);
      loop_ub = righty->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        Rightyout->data[i1] = righty->data[i1];
      }

      Rightyout_not_empty = !(Rightyout->size[0] == 0);
    } else {
      b_ii = Leftxout->size[0];
      i1 = b_nonzerox->size[0];
      b_nonzerox->size[0] = leftx->size[0];
      emxEnsureCapacity_real_T1(b_nonzerox, i1);
      loop_ub = leftx->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_nonzerox->data[i1] = leftx->data[i1];
      }

      jj = b_nonzerox->size[0];
      i1 = Leftxout->size[0];
      Leftxout->size[0] = b_ii + jj;
      emxEnsureCapacity_real_T1(Leftxout, i1);
      loop_ub = leftx->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        Leftxout->data[b_ii + i1] = leftx->data[i1];
      }

      Leftxout_not_empty = !(Leftxout->size[0] == 0);
      b_ii = Leftyout->size[0];
      i1 = b_nonzerox->size[0];
      b_nonzerox->size[0] = lefty->size[0];
      emxEnsureCapacity_real_T1(b_nonzerox, i1);
      loop_ub = lefty->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_nonzerox->data[i1] = lefty->data[i1];
      }

      jj = b_nonzerox->size[0];
      i1 = Leftyout->size[0];
      Leftyout->size[0] = b_ii + jj;
      emxEnsureCapacity_real_T1(Leftyout, i1);
      loop_ub = lefty->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        Leftyout->data[b_ii + i1] = lefty->data[i1];
      }

      Leftyout_not_empty = !(Leftyout->size[0] == 0);
      b_ii = Rightxout->size[0];
      i1 = b_nonzerox->size[0];
      b_nonzerox->size[0] = good_left_inds->size[0];
      emxEnsureCapacity_real_T1(b_nonzerox, i1);
      loop_ub = good_left_inds->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_nonzerox->data[i1] = good_left_inds->data[i1];
      }

      jj = b_nonzerox->size[0];
      i1 = Rightxout->size[0];
      Rightxout->size[0] = b_ii + jj;
      emxEnsureCapacity_real_T1(Rightxout, i1);
      loop_ub = good_left_inds->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        Rightxout->data[b_ii + i1] = good_left_inds->data[i1];
      }

      Rightxout_not_empty = !(Rightxout->size[0] == 0);
      b_ii = Rightyout->size[0];
      i1 = b_nonzerox->size[0];
      b_nonzerox->size[0] = righty->size[0];
      emxEnsureCapacity_real_T1(b_nonzerox, i1);
      loop_ub = righty->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_nonzerox->data[i1] = righty->data[i1];
      }

      jj = b_nonzerox->size[0];
      i1 = Rightyout->size[0];
      Rightyout->size[0] = b_ii + jj;
      emxEnsureCapacity_real_T1(Rightyout, i1);
      loop_ub = righty->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        Rightyout->data[b_ii + i1] = righty->data[i1];
      }

      Rightyout_not_empty = !(Rightyout->size[0] == 0);
    }
  }

  emxFree_real_T(&b_nonzerox);
  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_int32_T(&nonzerox);
  emxFree_int32_T(&nonzeroy);
  emxFree_int32_T(&righty);
  emxFree_int32_T(&lefty);
  emxFree_int32_T(&leftx);
  emxFree_int32_T(&good_right_inds);
  emxFree_int32_T(&good_left_inds);
  polyfit(Leftyout, Leftxout, Leftpoints);
  polyfit(Rightyout, Rightxout, Rightpoints);
}

static void ImageTestFunction_free()
{
  emxFree_real_T(&Leftxout);
  emxFree_real_T(&Leftyout);
  emxFree_real_T(&Rightxout);
  emxFree_real_T(&Rightyout);
}

static void ImageTestFunction_init()
{
  emxInit_real_T(&Rightyout, 1);
  emxInit_real_T(&Rightxout, 1);
  emxInit_real_T(&Leftyout, 1);
  emxInit_real_T(&Leftxout, 1);
  Rightyout_not_empty = false;
  Rightxout_not_empty = false;
  Leftyout_not_empty = false;
  Leftxout_not_empty = false;
}

static void LSQFromQR(const emxArray_real_T *A, const double tau_data[], const
                      int jpvt[3], emxArray_real_T *B, int rankA, double Y[3])
{
  int i;
  int m;
  int mn;
  int j;
  double wj;
  for (i = 0; i < 3; i++) {
    Y[i] = 0.0;
  }

  m = A->size[0];
  mn = A->size[0];
  if (!(mn < 3)) {
    mn = 3;
  }

  for (j = 0; j < mn; j++) {
    if (tau_data[j] != 0.0) {
      wj = B->data[j];
      for (i = j + 1; i < m; i++) {
        wj += A->data[i + A->size[0] * j] * B->data[i];
      }

      wj *= tau_data[j];
      if (wj != 0.0) {
        B->data[j] -= wj;
        for (i = j + 1; i < m; i++) {
          B->data[i] -= A->data[i + A->size[0] * j] * wj;
        }
      }
    }
  }

  for (i = 0; i < rankA; i++) {
    Y[jpvt[i] - 1] = B->data[i];
  }

  for (j = rankA - 1; j + 1 > 0; j--) {
    Y[jpvt[j] - 1] /= A->data[j + A->size[0] * j];
    for (i = 0; i < j; i++) {
      Y[jpvt[i] - 1] -= Y[jpvt[j] - 1] * A->data[i + A->size[0] * j];
    }
  }
}

static void VideoProcess(const emxArray_uint8_T *Binaryimage, const double left
  [3], const double right[3], double Leftpoints[3], double Rightpoints[3])
{
  int jj;
  int nx;
  emxArray_int32_T *i;
  emxArray_int32_T *j;
  int idx;
  int ii;
  emxArray_real_T *nonzeroy;
  bool exitg1;
  bool guard1 = false;
  emxArray_int32_T *nonzerox;
  emxArray_boolean_T *r1;
  emxArray_real_T *b_nonzeroy;
  emxArray_boolean_T *r2;
  emxArray_boolean_T *r3;
  emxArray_boolean_T *r4;
  emxArray_real_T *b_nonzerox;
  emxArray_int32_T *r5;
  emxArray_int32_T *r6;
  for (jj = 0; jj < 3; jj++) {
    Leftpoints[jj] = rtNaN;
    Rightpoints[jj] = rtNaN;
  }

  nx = Binaryimage->size[0] * Binaryimage->size[1];
  emxInit_int32_T(&i, 1);
  emxInit_int32_T(&j, 1);
  if (nx == 0) {
    jj = i->size[0];
    i->size[0] = 0;
    emxEnsureCapacity_int32_T(i, jj);
    jj = j->size[0];
    j->size[0] = 0;
    emxEnsureCapacity_int32_T(j, jj);
  } else {
    idx = 0;
    jj = i->size[0];
    i->size[0] = nx;
    emxEnsureCapacity_int32_T(i, jj);
    jj = j->size[0];
    j->size[0] = nx;
    emxEnsureCapacity_int32_T(j, jj);
    ii = 1;
    jj = 1;
    exitg1 = false;
    while ((!exitg1) && (jj <= Binaryimage->size[1])) {
      guard1 = false;
      if (Binaryimage->data[(ii + Binaryimage->size[0] * (jj - 1)) - 1] != 0) {
        idx++;
        i->data[idx - 1] = ii;
        j->data[idx - 1] = jj;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        ii++;
        if (ii > Binaryimage->size[0]) {
          ii = 1;
          jj++;
        }
      }
    }

    if (nx == 1) {
      if (idx == 0) {
        jj = i->size[0];
        i->size[0] = 0;
        emxEnsureCapacity_int32_T(i, jj);
        jj = j->size[0];
        j->size[0] = 0;
        emxEnsureCapacity_int32_T(j, jj);
      }
    } else {
      jj = i->size[0];
      if (1 > idx) {
        i->size[0] = 0;
      } else {
        i->size[0] = idx;
      }

      emxEnsureCapacity_int32_T(i, jj);
      jj = j->size[0];
      if (1 > idx) {
        j->size[0] = 0;
      } else {
        j->size[0] = idx;
      }

      emxEnsureCapacity_int32_T(j, jj);
    }
  }

  emxInit_real_T(&nonzeroy, 1);
  jj = nonzeroy->size[0];
  nonzeroy->size[0] = i->size[0];
  emxEnsureCapacity_real_T1(nonzeroy, jj);
  ii = i->size[0];
  for (jj = 0; jj < ii; jj++) {
    nonzeroy->data[jj] = i->data[jj];
  }

  emxFree_int32_T(&i);
  emxInit_int32_T(&nonzerox, 1);
  jj = nonzerox->size[0];
  nonzerox->size[0] = j->size[0];
  emxEnsureCapacity_int32_T(nonzerox, jj);
  ii = j->size[0];
  for (jj = 0; jj < ii; jj++) {
    nonzerox->data[jj] = j->data[jj];
  }

  emxFree_int32_T(&j);
  emxInit_boolean_T1(&r1, 1);
  emxInit_real_T(&b_nonzeroy, 1);
  power(nonzeroy, b_nonzeroy);
  jj = r1->size[0];
  r1->size[0] = nonzerox->size[0];
  emxEnsureCapacity_boolean_T1(r1, jj);
  ii = nonzerox->size[0];
  for (jj = 0; jj < ii; jj++) {
    r1->data[jj] = (nonzerox->data[jj] > ((left[0] * b_nonzeroy->data[jj] +
      left[1] * nonzeroy->data[jj]) + left[2]) - 25.0);
  }

  emxInit_boolean_T1(&r2, 1);
  power(nonzeroy, b_nonzeroy);
  jj = r2->size[0];
  r2->size[0] = nonzerox->size[0];
  emxEnsureCapacity_boolean_T1(r2, jj);
  ii = nonzerox->size[0];
  for (jj = 0; jj < ii; jj++) {
    r2->data[jj] = (nonzerox->data[jj] < ((left[0] * b_nonzeroy->data[jj] +
      left[1] * nonzeroy->data[jj]) + left[2]) + 25.0);
  }

  emxInit_boolean_T1(&r3, 1);
  power(nonzeroy, b_nonzeroy);
  jj = r3->size[0];
  r3->size[0] = nonzerox->size[0];
  emxEnsureCapacity_boolean_T1(r3, jj);
  ii = nonzerox->size[0];
  for (jj = 0; jj < ii; jj++) {
    r3->data[jj] = (nonzerox->data[jj] > ((right[0] * b_nonzeroy->data[jj] +
      right[1] * nonzeroy->data[jj]) + right[2]) - 25.0);
  }

  emxInit_boolean_T1(&r4, 1);
  power(nonzeroy, b_nonzeroy);
  jj = r4->size[0];
  r4->size[0] = nonzerox->size[0];
  emxEnsureCapacity_boolean_T1(r4, jj);
  ii = nonzerox->size[0];
  for (jj = 0; jj < ii; jj++) {
    r4->data[jj] = (nonzerox->data[jj] < ((right[0] * b_nonzeroy->data[jj] +
      right[1] * nonzeroy->data[jj]) + right[2]) + 25.0);
  }

  nx = r1->size[0];
  ii = 0;
  for (jj = 0; jj < nx; jj++) {
    if (r1->data[jj] && r2->data[jj]) {
      ii++;
    }
  }

  emxInit_real_T(&b_nonzerox, 1);
  if (ii != 0) {
    nx = r1->size[0] - 1;
    ii = 0;
    for (jj = 0; jj <= nx; jj++) {
      if (r1->data[jj] && r2->data[jj]) {
        ii++;
      }
    }

    emxInit_int32_T(&r5, 1);
    jj = r5->size[0];
    r5->size[0] = ii;
    emxEnsureCapacity_int32_T(r5, jj);
    ii = 0;
    for (jj = 0; jj <= nx; jj++) {
      if (r1->data[jj] && r2->data[jj]) {
        r5->data[ii] = jj + 1;
        ii++;
      }
    }

    jj = b_nonzeroy->size[0];
    b_nonzeroy->size[0] = r5->size[0];
    emxEnsureCapacity_real_T1(b_nonzeroy, jj);
    ii = r5->size[0];
    for (jj = 0; jj < ii; jj++) {
      b_nonzeroy->data[jj] = nonzeroy->data[r5->data[jj] - 1];
    }

    jj = b_nonzerox->size[0];
    b_nonzerox->size[0] = r5->size[0];
    emxEnsureCapacity_real_T1(b_nonzerox, jj);
    ii = r5->size[0];
    for (jj = 0; jj < ii; jj++) {
      b_nonzerox->data[jj] = nonzerox->data[r5->data[jj] - 1];
    }

    emxFree_int32_T(&r5);
    polyfit(b_nonzeroy, b_nonzerox, Leftpoints);
  }

  emxFree_boolean_T(&r2);
  emxFree_boolean_T(&r1);
  nx = r3->size[0];
  ii = 0;
  for (jj = 0; jj < nx; jj++) {
    if (r3->data[jj] && r4->data[jj]) {
      ii++;
    }
  }

  if (ii != 0) {
    nx = r3->size[0] - 1;
    ii = 0;
    for (jj = 0; jj <= nx; jj++) {
      if (r3->data[jj] && r4->data[jj]) {
        ii++;
      }
    }

    emxInit_int32_T(&r6, 1);
    jj = r6->size[0];
    r6->size[0] = ii;
    emxEnsureCapacity_int32_T(r6, jj);
    ii = 0;
    for (jj = 0; jj <= nx; jj++) {
      if (r3->data[jj] && r4->data[jj]) {
        r6->data[ii] = jj + 1;
        ii++;
      }
    }

    jj = b_nonzeroy->size[0];
    b_nonzeroy->size[0] = r6->size[0];
    emxEnsureCapacity_real_T1(b_nonzeroy, jj);
    ii = r6->size[0];
    for (jj = 0; jj < ii; jj++) {
      b_nonzeroy->data[jj] = nonzeroy->data[r6->data[jj] - 1];
    }

    jj = b_nonzerox->size[0];
    b_nonzerox->size[0] = r6->size[0];
    emxEnsureCapacity_real_T1(b_nonzerox, jj);
    ii = r6->size[0];
    for (jj = 0; jj < ii; jj++) {
      b_nonzerox->data[jj] = nonzerox->data[r6->data[jj] - 1];
    }

    emxFree_int32_T(&r6);
    polyfit(b_nonzeroy, b_nonzerox, Rightpoints);
  }

  emxFree_real_T(&b_nonzerox);
  emxFree_real_T(&b_nonzeroy);
  emxFree_boolean_T(&r4);
  emxFree_boolean_T(&r3);
  emxFree_int32_T(&nonzerox);
  emxFree_real_T(&nonzeroy);
}

static int b_ilazlc(int m, int n, const double A[1080], int ia0)
{
  int j;
  bool exitg2;
  int coltop;
  int ia;
  int exitg1;
  j = n;
  exitg2 = false;
  while ((!exitg2) && (j > 0)) {
    coltop = ia0 + (j - 1) * 360;
    ia = coltop;
    do {
      exitg1 = 0;
      if (ia <= (coltop + m) - 1) {
        if (A[ia - 1] != 0.0) {
          exitg1 = 1;
        } else {
          ia++;
        }
      } else {
        j--;
        exitg1 = 2;
      }
    } while (exitg1 == 0);

    if (exitg1 == 1) {
      exitg2 = true;
    }
  }

  return j;
}

static void b_polyfit(const double x[360], const double y[360], double p[3])
{
  double dv1[1080];
  int rr;
  b_vander(x, dv1);
  b_qrsolve(dv1, y, p, &rr);
}

static void b_qrsolve(const double A[1080], const double B[360], double Y[3],
                      int *rankR)
{
  double b_A[1080];
  double tau[3];
  int jpvt[3];
  double b_B[360];
  int j;
  int i;
  double wj;
  memcpy(&b_A[0], &A[0], 1080U * sizeof(double));
  b_xgeqp3(b_A, tau, jpvt);
  *rankR = b_rankFromQR(b_A);
  memcpy(&b_B[0], &B[0], 360U * sizeof(double));
  for (j = 0; j < 3; j++) {
    Y[j] = 0.0;
    if (tau[j] != 0.0) {
      wj = b_B[j];
      for (i = j + 1; i + 1 < 361; i++) {
        wj += b_A[i + 360 * j] * b_B[i];
      }

      wj *= tau[j];
      if (wj != 0.0) {
        b_B[j] -= wj;
        for (i = j + 1; i + 1 < 361; i++) {
          b_B[i] -= b_A[i + 360 * j] * wj;
        }
      }
    }
  }

  for (i = 0; i < 3; i++) {
    Y[jpvt[i] - 1] = b_B[i];
  }

  for (j = 2; j >= 0; j--) {
    Y[jpvt[j] - 1] /= b_A[j + 360 * j];
    for (i = 0; i < j; i++) {
      Y[jpvt[i] - 1] -= Y[jpvt[j] - 1] * b_A[i + 360 * j];
    }
  }
}

static int b_rankFromQR(const double A[1080])
{
  int r;
  double tol;
  r = 0;
  tol = 360.0 * std::abs(A[0]) * 2.2204460492503131E-16;
  while ((r < 3) && (!(std::abs(A[r + 360 * r]) <= tol))) {
    r++;
  }

  return r;
}

static void b_sqrt(double *x)
{
  *x = std::sqrt(*x);
}

static void b_vander(const double v[360], double A[1080])
{
  int k;
  for (k = 0; k < 360; k++) {
    A[720 + k] = 1.0;
    A[360 + k] = v[k];
    A[k] = v[k] * A[360 + k];
  }
}

static void b_xgemv(int m, int n, const double A[1080], int ia0, const double x
                    [1080], int ix0, double y[3])
{
  int iy;
  int i9;
  int iac;
  int ix;
  double c;
  int i10;
  int ia;
  if (n != 0) {
    for (iy = 1; iy <= n; iy++) {
      y[iy - 1] = 0.0;
    }

    iy = 0;
    i9 = ia0 + 360 * (n - 1);
    for (iac = ia0; iac <= i9; iac += 360) {
      ix = ix0;
      c = 0.0;
      i10 = (iac + m) - 1;
      for (ia = iac; ia <= i10; ia++) {
        c += A[ia - 1] * x[ix - 1];
        ix++;
      }

      y[iy] += c;
      iy++;
    }
  }
}

static void b_xgeqp3(double A[1080], double tau[3], int jpvt[3])
{
  int k;
  int pvt;
  int i;
  double work[3];
  double temp1;
  double vn1[3];
  double vn2[3];
  int itemp;
  double temp2;
  k = 1;
  for (pvt = 0; pvt < 3; pvt++) {
    jpvt[pvt] = 1 + pvt;
    work[pvt] = 0.0;
    temp1 = b_xnrm2(A, k);
    vn2[pvt] = temp1;
    k += 360;
    vn1[pvt] = temp1;
  }

  for (i = 0; i < 3; i++) {
    k = i + i * 360;
    pvt = (i + ixamax(3 - i, vn1, i + 1)) - 1;
    if (pvt + 1 != i + 1) {
      b_xswap(A, 1 + 360 * pvt, 1 + 360 * i);
      itemp = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = itemp;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }

    temp1 = A[k];
    tau[i] = b_xzlarfg(360 - i, &temp1, A, k + 2);
    A[k] = temp1;
    if (i + 1 < 3) {
      temp1 = A[k];
      A[k] = 1.0;
      b_xzlarf(360 - i, 2 - i, k + 1, tau[i], A, (i + (i + 1) * 360) + 1, work);
      A[k] = temp1;
    }

    for (pvt = i + 1; pvt + 1 < 4; pvt++) {
      if (vn1[pvt] != 0.0) {
        temp1 = std::abs(A[i + 360 * pvt]) / vn1[pvt];
        temp1 = 1.0 - temp1 * temp1;
        if (temp1 < 0.0) {
          temp1 = 0.0;
        }

        temp2 = vn1[pvt] / vn2[pvt];
        temp2 = temp1 * (temp2 * temp2);
        if (temp2 <= 1.4901161193847656E-8) {
          vn1[pvt] = c_xnrm2(359 - i, A, (i + 360 * pvt) + 2);
          vn2[pvt] = vn1[pvt];
        } else {
          b_sqrt(&temp1);
          vn1[pvt] *= temp1;
        }
      }
    }
  }
}

static void b_xgerc(int m, int n, double alpha1, int ix0, const double y[3],
                    double A[1080], int ia0)
{
  int jA;
  int jy;
  int j;
  double temp;
  int ix;
  int i11;
  int ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if (y[jy] != 0.0) {
        temp = y[jy] * alpha1;
        ix = ix0;
        i11 = m + jA;
        for (ijA = jA; ijA < i11; ijA++) {
          A[ijA] += A[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += 360;
    }
  }
}

static double b_xnrm2(const double x[1080], int ix0)
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = ix0; k <= ix0 + 359; k++) {
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

static void b_xswap(double x[1080], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 360; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

static void b_xzlarf(int m, int n, int iv0, double tau, double C[1080], int ic0,
                     double work[3])
{
  int lastv;
  int lastc;
  if (tau != 0.0) {
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = b_ilazlc(lastv, n, C, ic0);
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    b_xgemv(lastv, lastc, C, ic0, C, iv0, work);
    b_xgerc(lastv, lastc, -tau, iv0, work, C, ic0);
  }
}

static double b_xzlarfg(int n, double *alpha1, double x[1080], int ix0)
{
  double tau;
  double xnorm;
  int knt;
  int i8;
  int k;
  tau = 0.0;
  if (!(n <= 0)) {
    xnorm = c_xnrm2(n - 1, x, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (std::abs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        i8 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i8; k++) {
            x[k - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(std::abs(xnorm) >= 1.0020841800044864E-292));

        xnorm = rt_hypotd_snf(*alpha1, c_xnrm2(n - 1, x, ix0));
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i8 = (ix0 + n) - 2;
        for (k = ix0; k <= i8; k++) {
          x[k - 1] *= *alpha1;
        }

        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i8 = (ix0 + n) - 2;
        for (k = ix0; k <= i8; k++) {
          x[k - 1] *= *alpha1;
        }

        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

static void bwareaopen(const emxArray_uint8_T *varargin_1, emxArray_boolean_T
  *BW2)
{
  emxArray_boolean_T *BW;
  int j;
  int numForegroundPixels;
  emxArray_int32_T *regionLengths;
  emxArray_real_T *L;
  double numComponents;
  int numPixels;
  emxArray_int32_T *beginIdx;
  int i;
  emxArray_int32_T *pixelIdxList;
  unsigned int uv0[2];
  emxInit_boolean_T(&BW, 2);
  j = BW->size[0] * BW->size[1];
  BW->size[0] = varargin_1->size[0];
  BW->size[1] = varargin_1->size[1];
  emxEnsureCapacity_boolean_T(BW, j);
  numForegroundPixels = varargin_1->size[0] * varargin_1->size[1];
  for (j = 0; j < numForegroundPixels; j++) {
    BW->data[j] = (varargin_1->data[j] != 0);
  }

  emxInit_int32_T(&regionLengths, 1);
  emxInit_real_T1(&L, 2);
  bwlabel(BW, L, &numComponents);
  numPixels = L->size[0] * L->size[1];
  j = regionLengths->size[0];
  regionLengths->size[0] = (int)numComponents;
  emxEnsureCapacity_int32_T(regionLengths, j);
  numForegroundPixels = (int)numComponents;
  for (j = 0; j < numForegroundPixels; j++) {
    regionLengths->data[j] = 0;
  }

  for (numForegroundPixels = 0; numForegroundPixels < numPixels;
       numForegroundPixels++) {
    if ((int)L->data[numForegroundPixels] > 0) {
      regionLengths->data[(int)L->data[numForegroundPixels] - 1]++;
    }
  }

  emxInit_int32_T(&beginIdx, 1);
  numPixels = L->size[0] * L->size[1];
  numForegroundPixels = 0;
  j = beginIdx->size[0];
  beginIdx->size[0] = regionLengths->size[0];
  emxEnsureCapacity_int32_T(beginIdx, j);
  for (i = 0; i < regionLengths->size[0]; i++) {
    beginIdx->data[i] = numForegroundPixels;
    numForegroundPixels += regionLengths->data[i];
  }

  emxInit_int32_T(&pixelIdxList, 1);
  j = pixelIdxList->size[0];
  pixelIdxList->size[0] = numForegroundPixels;
  emxEnsureCapacity_int32_T(pixelIdxList, j);
  for (numForegroundPixels = 0; numForegroundPixels < numPixels;
       numForegroundPixels++) {
    if ((int)L->data[numForegroundPixels] > 0) {
      beginIdx->data[(int)L->data[numForegroundPixels] - 1]++;
      pixelIdxList->data[beginIdx->data[(int)L->data[numForegroundPixels] - 1] -
        1] = numForegroundPixels + 1;
    }
  }

  emxFree_int32_T(&beginIdx);
  emxFree_real_T(&L);
  for (j = 0; j < 2; j++) {
    uv0[j] = (unsigned int)BW->size[j];
  }

  emxFree_boolean_T(&BW);
  j = BW2->size[0] * BW2->size[1];
  BW2->size[0] = (int)uv0[0];
  BW2->size[1] = (int)uv0[1];
  emxEnsureCapacity_boolean_T(BW2, j);
  numForegroundPixels = (int)uv0[0] * (int)uv0[1];
  for (j = 0; j < numForegroundPixels; j++) {
    BW2->data[j] = false;
  }

  numForegroundPixels = -1;
  for (i = 0; i < (int)numComponents; i++) {
    if (regionLengths->data[i] >= 10) {
      for (j = 1; j <= regionLengths->data[i]; j++) {
        BW2->data[pixelIdxList->data[numForegroundPixels + j] - 1] = true;
      }
    }

    numForegroundPixels += regionLengths->data[i];
  }

  emxFree_int32_T(&pixelIdxList);
  emxFree_int32_T(&regionLengths);
}

static void bwlabel(const emxArray_boolean_T *varargin_1, emxArray_real_T *L,
                    double *numComponents)
{
  int numRuns;
  int lastRunOnPreviousColumn;
  emxArray_int32_T *startRow;
  emxArray_int32_T *endRow;
  emxArray_int32_T *startCol;
  emxArray_int32_T *labelForEachRun;
  int k;
  int runCounter;
  int currentColumn;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int firstRunOnPreviousColumn;
  int firstRunOnThisColumn;
  emxArray_int32_T *labelsRenumbered;
  int p;
  int root_k;
  int root_p;
  numRuns = 0;
  if ((varargin_1->size[0] != 0) && (varargin_1->size[1] != 0)) {
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < varargin_1->
         size[1]; lastRunOnPreviousColumn++) {
      if (varargin_1->data[varargin_1->size[0] * lastRunOnPreviousColumn]) {
        numRuns++;
      }

      for (k = 0; k <= varargin_1->size[0] - 2; k++) {
        if (varargin_1->data[(k + varargin_1->size[0] * lastRunOnPreviousColumn)
            + 1] && (!varargin_1->data[k + varargin_1->size[0] *
                     lastRunOnPreviousColumn])) {
          numRuns++;
        }
      }
    }
  }

  emxInit_int32_T(&startRow, 1);
  emxInit_int32_T(&endRow, 1);
  emxInit_int32_T(&startCol, 1);
  emxInit_int32_T(&labelForEachRun, 1);
  if (numRuns == 0) {
    runCounter = startRow->size[0];
    startRow->size[0] = 0;
    emxEnsureCapacity_int32_T(startRow, runCounter);
    runCounter = endRow->size[0];
    endRow->size[0] = 0;
    emxEnsureCapacity_int32_T(endRow, runCounter);
    runCounter = startCol->size[0];
    startCol->size[0] = 0;
    emxEnsureCapacity_int32_T(startCol, runCounter);
    runCounter = labelForEachRun->size[0];
    labelForEachRun->size[0] = 0;
    emxEnsureCapacity_int32_T(labelForEachRun, runCounter);
    unnamed_idx_0 = (unsigned int)varargin_1->size[0];
    unnamed_idx_1 = (unsigned int)varargin_1->size[1];
    runCounter = L->size[0] * L->size[1];
    L->size[0] = (int)unnamed_idx_0;
    L->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity_real_T(L, runCounter);
    currentColumn = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (runCounter = 0; runCounter < currentColumn; runCounter++) {
      L->data[runCounter] = 0.0;
    }

    *numComponents = 0.0;
  } else {
    runCounter = startRow->size[0];
    startRow->size[0] = numRuns;
    emxEnsureCapacity_int32_T(startRow, runCounter);
    runCounter = endRow->size[0];
    endRow->size[0] = numRuns;
    emxEnsureCapacity_int32_T(endRow, runCounter);
    runCounter = startCol->size[0];
    startCol->size[0] = numRuns;
    emxEnsureCapacity_int32_T(startCol, runCounter);
    currentColumn = varargin_1->size[0];
    runCounter = 0;
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < varargin_1->
         size[1]; lastRunOnPreviousColumn++) {
      firstRunOnPreviousColumn = 1;
      while (firstRunOnPreviousColumn <= currentColumn) {
        while ((firstRunOnPreviousColumn <= currentColumn) && (!varargin_1->
                data[(firstRunOnPreviousColumn + varargin_1->size[0] *
                      lastRunOnPreviousColumn) - 1])) {
          firstRunOnPreviousColumn++;
        }

        if ((firstRunOnPreviousColumn <= currentColumn) && varargin_1->data
            [(firstRunOnPreviousColumn + varargin_1->size[0] *
              lastRunOnPreviousColumn) - 1]) {
          startCol->data[runCounter] = lastRunOnPreviousColumn + 1;
          startRow->data[runCounter] = firstRunOnPreviousColumn;
          while ((firstRunOnPreviousColumn <= currentColumn) && varargin_1->
                 data[(firstRunOnPreviousColumn + varargin_1->size[0] *
                       lastRunOnPreviousColumn) - 1]) {
            firstRunOnPreviousColumn++;
          }

          endRow->data[runCounter] = firstRunOnPreviousColumn - 1;
          runCounter++;
        }
      }
    }

    runCounter = labelForEachRun->size[0];
    labelForEachRun->size[0] = numRuns;
    emxEnsureCapacity_int32_T(labelForEachRun, runCounter);
    for (runCounter = 0; runCounter < numRuns; runCounter++) {
      labelForEachRun->data[runCounter] = 0;
    }

    k = 0;
    currentColumn = 1;
    runCounter = 1;
    firstRunOnPreviousColumn = -1;
    lastRunOnPreviousColumn = -1;
    firstRunOnThisColumn = 0;
    while (k + 1 <= numRuns) {
      if (startCol->data[k] == currentColumn + 1) {
        firstRunOnPreviousColumn = firstRunOnThisColumn + 1;
        firstRunOnThisColumn = k;
        lastRunOnPreviousColumn = k;
        currentColumn = startCol->data[k];
      } else {
        if (startCol->data[k] > currentColumn + 1) {
          firstRunOnPreviousColumn = -1;
          lastRunOnPreviousColumn = -1;
          firstRunOnThisColumn = k;
          currentColumn = startCol->data[k];
        }
      }

      if (firstRunOnPreviousColumn >= 0) {
        for (p = firstRunOnPreviousColumn - 1; p < lastRunOnPreviousColumn; p++)
        {
          if ((endRow->data[k] >= startRow->data[p] - 1) && (startRow->data[k] <=
               endRow->data[p] + 1)) {
            if (labelForEachRun->data[k] == 0) {
              labelForEachRun->data[k] = labelForEachRun->data[p];
              runCounter++;
            } else {
              if (labelForEachRun->data[k] != labelForEachRun->data[p]) {
                for (root_k = k; root_k + 1 != labelForEachRun->data[root_k];
                     root_k = labelForEachRun->data[root_k] - 1) {
                  labelForEachRun->data[root_k] = labelForEachRun->
                    data[labelForEachRun->data[root_k] - 1];
                }

                for (root_p = p; root_p + 1 != labelForEachRun->data[root_p];
                     root_p = labelForEachRun->data[root_p] - 1) {
                  labelForEachRun->data[root_p] = labelForEachRun->
                    data[labelForEachRun->data[root_p] - 1];
                }

                if (root_k + 1 != root_p + 1) {
                  if (root_p + 1 < root_k + 1) {
                    labelForEachRun->data[root_k] = root_p + 1;
                    labelForEachRun->data[k] = root_p + 1;
                  } else {
                    labelForEachRun->data[root_p] = root_k + 1;
                    labelForEachRun->data[p] = root_k + 1;
                  }
                }
              }
            }
          }
        }
      }

      if (labelForEachRun->data[k] == 0) {
        labelForEachRun->data[k] = runCounter;
        runCounter++;
      }

      k++;
    }

    emxInit_int32_T(&labelsRenumbered, 1);
    runCounter = labelsRenumbered->size[0];
    labelsRenumbered->size[0] = labelForEachRun->size[0];
    emxEnsureCapacity_int32_T(labelsRenumbered, runCounter);
    *numComponents = 0.0;
    unnamed_idx_0 = (unsigned int)varargin_1->size[0];
    unnamed_idx_1 = (unsigned int)varargin_1->size[1];
    runCounter = L->size[0] * L->size[1];
    L->size[0] = (int)unnamed_idx_0;
    L->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity_real_T(L, runCounter);
    currentColumn = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (runCounter = 0; runCounter < currentColumn; runCounter++) {
      L->data[runCounter] = 0.0;
    }

    for (k = 0; k < numRuns; k++) {
      if (labelForEachRun->data[k] == k + 1) {
        (*numComponents)++;
        labelsRenumbered->data[k] = (int)*numComponents;
      }

      labelsRenumbered->data[k] = labelsRenumbered->data[labelForEachRun->data[k]
        - 1];
      for (runCounter = startRow->data[k]; runCounter <= endRow->data[k];
           runCounter++) {
        L->data[(runCounter + L->size[0] * (startCol->data[k] - 1)) - 1] =
          labelsRenumbered->data[k];
      }
    }

    emxFree_int32_T(&labelsRenumbered);
  }

  emxFree_int32_T(&labelForEachRun);
  emxFree_int32_T(&startCol);
  emxFree_int32_T(&endRow);
  emxFree_int32_T(&startRow);
}

static double c_xnrm2(int n, const double x[1080], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = std::abs(x[ix0 - 1]);
    } else {
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = std::abs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = 1.0 + y * t * t;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * std::sqrt(y);
    }
  }

  return y;
}

static int div_s32(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  bool quotientNeedsNegation;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    absNumerator /= absDenominator;
    if (quotientNeedsNegation) {
      quotient = -(int)absNumerator;
    } else {
      quotient = (int)absNumerator;
    }
  }

  return quotient;
}

static int ilazlc(int m, int n, const emxArray_real_T *A, int ia0, int lda)
{
  int j;
  bool exitg2;
  int coltop;
  int ia;
  int exitg1;
  j = n;
  exitg2 = false;
  while ((!exitg2) && (j > 0)) {
    coltop = ia0 + (j - 1) * lda;
    ia = coltop;
    do {
      exitg1 = 0;
      if (ia <= (coltop + m) - 1) {
        if (A->data[ia - 1] != 0.0) {
          exitg1 = 1;
        } else {
          ia++;
        }
      } else {
        j--;
        exitg1 = 2;
      }
    } while (exitg1 == 0);

    if (exitg1 == 1) {
      exitg2 = true;
    }
  }

  return j;
}

static bool isrow(const emxArray_boolean_T *x)
{
  return x->size[0] == 1;
}

static int ixamax(int n, const double x[3], int ix0)
{
  int idxmax;
  int ix;
  double smax;
  int k;
  double s;
  if (n < 1) {
    idxmax = 0;
  } else {
    idxmax = 1;
    if (n > 1) {
      ix = ix0 - 1;
      smax = std::abs(x[ix0 - 1]);
      for (k = 2; k <= n; k++) {
        ix++;
        s = std::abs(x[ix]);
        if (s > smax) {
          idxmax = k;
          smax = s;
        }
      }
    }
  }

  return idxmax;
}

static double mean(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += x->data[k - 1];
    }
  }

  y /= (double)x->size[0];
  return y;
}

static void morphopAlgo(const emxArray_boolean_T *A, emxArray_boolean_T *B)
{
  int centerPixelSub_idx_0;
  c_images_internal_coder_Neighbo np;
  static const bool nhConn[9] = { false, true, false, true, true, true, false,
    true, false };

  int imSize[2];
  int i;
  bool b_nhConn[9];
  int nhInds[5];
  int imageNeighborLinearOffsets[5];
  int imnhSubs[10];
  int pixelsPerImPage[2];
  double centerLocationInImage;
  int indx;
  int pind;
  int r;
  int firstIndRange[2];
  signed char subs[2];
  signed char b_subs[2];
  int a[10];
  emxArray_boolean_T *in;
  c_images_internal_coder_Neighbo *nhoodObj;
  int centerPixelSub_idx_1;
  int secondInd;
  bool imnh_data[25];
  signed char imnh_size[2];
  double centerPixelSub[2];
  bool padValue;
  int varargin_2;
  int imnhInds[5];
  int b_pind;
  int b_varargin_2;
  bool out__data[360];
  int minval;
  int loop_ub;
  int firstInd;
  int b_secondInd;
  int b_i;
  int b_firstInd;
  int varargin_1_size_idx_0;
  signed char varargin_1_data[26];
  int pixelSub[2];
  bool isInside[5];
  int trueCount;
  bool p;
  bool exitg1;
  int imnhInds_data[5];
  int tmp_data[5];
  int b_pixelSub[2];
  bool b_imnh_data[25];
  int k[2];
  signed char b_varargin_1_data[26];
  int b_trueCount;
  int b_tmp_data[5];
  int b_imnhInds_data[5];
  int c_pixelSub[2];
  int c_trueCount;
  int c_imnhInds_data[5];
  int c_tmp_data[5];
  int d_pixelSub[2];
  int d_tmp_data[5];
  int d_trueCount;
  int d_imnhInds_data[5];
  int e_tmp_data[5];
  if (!((A->size[0] == 0) || (A->size[1] == 0))) {
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      np.ImageSize[centerPixelSub_idx_0] = A->size[centerPixelSub_idx_0];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 9;
         centerPixelSub_idx_0++) {
      np.Neighborhood[centerPixelSub_idx_0] = nhConn[centerPixelSub_idx_0];
    }

    np.Padding = 1.0;
    np.ProcessBorder = true;
    np.NeighborhoodCenter = 1.0;
    np.PadValue = 0.0;
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      imSize[centerPixelSub_idx_0] = np.ImageSize[centerPixelSub_idx_0];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 9;
         centerPixelSub_idx_0++) {
      b_nhConn[centerPixelSub_idx_0] = np.Neighborhood[centerPixelSub_idx_0];
    }

    for (i = 0; i < 5; i++) {
      nhInds[i] = np.ImageNeighborLinearOffsets[i];
    }

    for (i = 0; i < 5; i++) {
      imageNeighborLinearOffsets[i] = np.NeighborLinearIndices[i];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
         centerPixelSub_idx_0++) {
      imnhSubs[centerPixelSub_idx_0] =
        np.NeighborSubscriptOffsets[centerPixelSub_idx_0];
    }

    /*  Process pixels with full neighborhood */
    /*  Process pixels with partial neighborhood */
    /*  Process pixels with full neighborhood */
    /*  Process pixels with partial neighborhood */
    pixelsPerImPage[0] = 1;
    pixelsPerImPage[1] = imSize[0];
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      imSize[centerPixelSub_idx_0]--;
    }

    centerLocationInImage = b_nhConn[0];
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 8;
         centerPixelSub_idx_0++) {
      centerLocationInImage += (double)b_nhConn[centerPixelSub_idx_0 + 1];
    }

    if (!(centerLocationInImage == 0.0)) {
      indx = 0;
      for (pind = 0; pind < 9; pind++) {
        if (b_nhConn[pind]) {
          r = (int)rt_remd_snf((1.0 + (double)pind) - 1.0, 3.0) + 1;
          subs[1] = (signed char)((int)(((double)(pind - r) + 1.0) / 3.0) + 1);
          subs[0] = (signed char)r;
          b_subs[0] = (signed char)r;
          b_subs[1] = (signed char)(subs[1] - 1);
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imnhSubs[indx + 5 * centerPixelSub_idx_0] =
              subs[centerPixelSub_idx_0];
            firstIndRange[centerPixelSub_idx_0] = b_subs[centerPixelSub_idx_0] *
              (1 + (centerPixelSub_idx_0 << 1));
          }

          imageNeighborLinearOffsets[indx] = firstIndRange[0] + firstIndRange[1];
          b_subs[0] = (signed char)r;
          b_subs[1] = (signed char)(subs[1] - 1);
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            firstIndRange[centerPixelSub_idx_0] = b_subs[centerPixelSub_idx_0] *
              pixelsPerImPage[centerPixelSub_idx_0];
          }

          nhInds[indx] = (int)((double)firstIndRange[0] + (double)firstIndRange
                               [1]);
          indx++;
        }
      }

      for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
           centerPixelSub_idx_0++) {
        firstIndRange[centerPixelSub_idx_0] = (2 - centerPixelSub_idx_0) *
          pixelsPerImPage[centerPixelSub_idx_0];
      }

      centerLocationInImage = (double)firstIndRange[0] + (double)firstIndRange[1];
      for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
           centerPixelSub_idx_0++) {
        nhInds[centerPixelSub_idx_0] -= (int)centerLocationInImage;
      }

      for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
           centerPixelSub_idx_0++) {
        a[centerPixelSub_idx_0] = imnhSubs[centerPixelSub_idx_0];
      }

      for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
           centerPixelSub_idx_0++) {
        for (indx = 0; indx < 5; indx++) {
          imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
            centerPixelSub_idx_0] - 2;
        }
      }
    }

    for (i = 0; i < 5; i++) {
      np.ImageNeighborLinearOffsets[i] = nhInds[i];
    }

    for (i = 0; i < 5; i++) {
      np.NeighborLinearIndices[i] = imageNeighborLinearOffsets[i];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
         centerPixelSub_idx_0++) {
      np.NeighborSubscriptOffsets[centerPixelSub_idx_0] =
        imnhSubs[centerPixelSub_idx_0];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      np.InteriorStart[centerPixelSub_idx_0] = 2.0;
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      np.InteriorEnd[centerPixelSub_idx_0] = imSize[centerPixelSub_idx_0];
    }

    emxInit_boolean_T(&in, 2);
    nhoodObj = &np;
    centerPixelSub_idx_0 = in->size[0] * in->size[1];
    in->size[0] = A->size[0];
    in->size[1] = A->size[1];
    emxEnsureCapacity_boolean_T(in, centerPixelSub_idx_0);
    indx = A->size[0] * A->size[1];
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
         centerPixelSub_idx_0++) {
      in->data[centerPixelSub_idx_0] = A->data[centerPixelSub_idx_0];
    }

    centerPixelSub_idx_0 = (int)np.InteriorStart[1];
    centerPixelSub_idx_1 = np.InteriorEnd[1];
    firstIndRange[0] = (int)np.InteriorStart[0];
    firstIndRange[1] = np.InteriorEnd[0];
    for (i = 0; i < 5; i++) {
      imageNeighborLinearOffsets[i] = np.ImageNeighborLinearOffsets[i];
    }

    indx = np.ImageSize[0];

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(imnh_data,imnh_size,imnhInds,b_pind,out__data,loop_ub,firstInd,b_i,varargin_1_size_idx_0) \
 firstprivate(varargin_1_data)

    for (secondInd = centerPixelSub_idx_0; secondInd <= centerPixelSub_idx_1;
         secondInd++) {
      loop_ub = B->size[0];
      for (firstInd = firstIndRange[0]; firstInd <= firstIndRange[1]; firstInd++)
      {
        b_pind = (secondInd - 1) * indx + firstInd;
        for (b_i = 0; b_i < 5; b_i++) {
          imnhInds[b_i] = imageNeighborLinearOffsets[b_i] + b_pind;
        }

        if (isrow(in)) {
          imnh_size[0] = 1;
          imnh_size[1] = 5;
          for (b_pind = 0; b_pind < 5; b_pind++) {
            imnh_data[b_pind] = in->data[imnhInds[b_pind] - 1];
          }
        } else {
          imnh_size[0] = 5;
          imnh_size[1] = 1;
          for (b_pind = 0; b_pind < 5; b_pind++) {
            imnh_data[b_pind] = in->data[imnhInds[b_pind] - 1];
          }
        }

        varargin_1_size_idx_0 = imnh_size[0] * imnh_size[1] + 1;
        b_i = imnh_size[0] * imnh_size[1];
        for (b_pind = 0; b_pind < b_i; b_pind++) {
          varargin_1_data[b_pind] = (signed char)imnh_data[b_pind];
        }

        varargin_1_data[imnh_size[0] * imnh_size[1]] = 0;
        if (varargin_1_size_idx_0 <= 2) {
          if (varargin_1_data[0] < varargin_1_data[1]) {
            b_pind = varargin_1_data[1];
          } else {
            b_pind = varargin_1_data[0];
          }
        } else {
          b_pind = varargin_1_data[0];
          for (b_i = 1; b_i < varargin_1_size_idx_0; b_i++) {
            if (b_pind < varargin_1_data[b_i]) {
              b_pind = varargin_1_data[b_i];
            }
          }
        }

        out__data[firstInd - 1] = (b_pind != 0);
      }

      for (b_pind = 0; b_pind < loop_ub; b_pind++) {
        B->data[b_pind + B->size[0] * (secondInd - 1)] = out__data[b_pind];
      }
    }

    if (nhoodObj->ProcessBorder) {
      firstIndRange[1] = nhoodObj->ImageSize[0];
      centerPixelSub[1] = nhoodObj->InteriorStart[1] - 1.0;
      padValue = (nhoodObj->PadValue != 0.0);
      varargin_2 = nhoodObj->ImageSize[0];
      indx = firstIndRange[1];
      if (indx < varargin_2) {
        varargin_2 = indx;
      }

      b_varargin_2 = nhoodObj->ImageSize[1];
      if (rtIsNaN(centerPixelSub[1]) || (centerPixelSub[1] > b_varargin_2)) {
        minval = b_varargin_2;
      } else {
        minval = (int)centerPixelSub[1];
      }

      for (b_secondInd = 0; b_secondInd < minval; b_secondInd++) {
        if (1 <= varargin_2) {
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
               centerPixelSub_idx_0++) {
            a[centerPixelSub_idx_0] = nhoodObj->
              NeighborSubscriptOffsets[centerPixelSub_idx_0];
          }
        }

        for (b_firstInd = 1; b_firstInd <= varargin_2; b_firstInd++) {
          indx = nhoodObj->ImageSize[0];
          pind = b_secondInd * indx + b_firstInd;
          for (i = 0; i < 5; i++) {
            nhInds[i] = nhoodObj->ImageNeighborLinearOffsets[i];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
               centerPixelSub_idx_0++) {
            nhInds[centerPixelSub_idx_0] += pind;
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imSize[centerPixelSub_idx_0] = nhoodObj->
              ImageSize[centerPixelSub_idx_0];
          }

          if (imSize[0] == 0) {
            r = 1;
          } else {
            r = pind - imSize[0] * div_s32(pind - 1, imSize[0]);
          }

          centerPixelSub_idx_0 = pind - r;
          if (imSize[0] == 0) {
            if (centerPixelSub_idx_0 == 0) {
              centerPixelSub_idx_1 = 0;
            } else if (centerPixelSub_idx_0 < 0) {
              centerPixelSub_idx_1 = MIN_int32_T;
            } else {
              centerPixelSub_idx_1 = MAX_int32_T;
            }
          } else if (imSize[0] == 1) {
            centerPixelSub_idx_1 = centerPixelSub_idx_0;
          } else if (imSize[0] == -1) {
            centerPixelSub_idx_1 = -centerPixelSub_idx_0;
          } else {
            if (centerPixelSub_idx_0 >= 0) {
              indx = centerPixelSub_idx_0;
            } else if (centerPixelSub_idx_0 == MIN_int32_T) {
              indx = MAX_int32_T;
            } else {
              indx = -centerPixelSub_idx_0;
            }

            if (imSize[0] >= 0) {
              i = imSize[0];
            } else if (imSize[0] == MIN_int32_T) {
              i = MAX_int32_T;
            } else {
              i = -imSize[0];
            }

            centerPixelSub_idx_1 = div_s32(indx, i);
            indx -= centerPixelSub_idx_1 * i;
            if ((indx > 0) && (indx >= (i >> 1) + (i & 1))) {
              centerPixelSub_idx_1++;
            }

            if ((centerPixelSub_idx_0 < 0) != (imSize[0] < 0)) {
              centerPixelSub_idx_1 = -centerPixelSub_idx_1;
            }
          }

          pixelSub[1] = centerPixelSub_idx_1 + 1;
          pixelSub[0] = r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            pixelsPerImPage[centerPixelSub_idx_0] =
              pixelSub[centerPixelSub_idx_0];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            for (indx = 0; indx < 5; indx++) {
              imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
                centerPixelSub_idx_0] + pixelsPerImPage[centerPixelSub_idx_0];
            }
          }

          for (i = 0; i < 5; i++) {
            isInside[i] = true;
          }

          switch ((int)nhoodObj->Padding) {
           case 1:
            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }

            trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                imnhInds_data[centerPixelSub_idx_0] = nhInds[i];
                centerPixelSub_idx_0++;
              }
            }
            break;

           case 2:
            trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              imnhInds_data[centerPixelSub_idx_0] = nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  imnhInds_data[centerPixelSub_idx_1] = 1;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }
            break;

           case 3:
            trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              imnhInds_data[centerPixelSub_idx_0] = nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = 1;
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = nhoodObj->ImageSize[centerPixelSub_idx_0];
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;

           case 4:
            trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              imnhInds_data[centerPixelSub_idx_0] = nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = pixelsPerImPage[centerPixelSub_idx_0] + (indx << 1);
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = ((indx << 1) - i) + 1;
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;
          }

          p = (in->size[0] == 1);
          if (p) {
            if (0 <= trueCount - 1) {
              memcpy(&tmp_data[0], &imnhInds_data[0], (unsigned int)(trueCount *
                      (int)sizeof(int)));
            }

            centerPixelSub_idx_1 = 1;
            r = trueCount;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[tmp_data[centerPixelSub_idx_0] - 1];
            }
          } else {
            centerPixelSub_idx_1 = trueCount;
            r = 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[imnhInds_data[centerPixelSub_idx_0] - 1];
            }
          }

          if (nhoodObj->Padding == 2.0) {
            indx = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                indx++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                b_tmp_data[centerPixelSub_idx_0] = i + 1;
                centerPixelSub_idx_0++;
              }
            }

            indx--;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 <= indx;
                 centerPixelSub_idx_0++) {
              b_imnh_data[b_tmp_data[centerPixelSub_idx_0] - 1] = padValue;
            }
          }

          i = centerPixelSub_idx_1 * r + 1;
          indx = centerPixelSub_idx_1 * r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
               centerPixelSub_idx_0++) {
            b_varargin_1_data[centerPixelSub_idx_0] = (signed char)
              b_imnh_data[centerPixelSub_idx_0];
          }

          b_varargin_1_data[centerPixelSub_idx_1 * r] = 0;
          if (i <= 2) {
            if (i == 1) {
              indx = b_varargin_1_data[0];
            } else if (b_varargin_1_data[0] < b_varargin_1_data[1]) {
              indx = b_varargin_1_data[1];
            } else {
              indx = b_varargin_1_data[0];
            }
          } else {
            indx = b_varargin_1_data[0];
            for (centerPixelSub_idx_0 = 1; centerPixelSub_idx_0 < i;
                 centerPixelSub_idx_0++) {
              if (indx < b_varargin_1_data[centerPixelSub_idx_0]) {
                indx = b_varargin_1_data[centerPixelSub_idx_0];
              }
            }
          }

          B->data[pind - 1] = (indx != 0);
        }
      }

      firstIndRange[1] = nhoodObj->ImageSize[0];
      centerPixelSub_idx_0 = nhoodObj->InteriorEnd[1] + 1;
      centerPixelSub_idx_1 = nhoodObj->ImageSize[1];
      padValue = (nhoodObj->PadValue != 0.0);
      varargin_2 = nhoodObj->ImageSize[0];
      indx = firstIndRange[1];
      if (indx < varargin_2) {
        varargin_2 = indx;
      }

      b_varargin_2 = nhoodObj->ImageSize[1];
      if (centerPixelSub_idx_1 < b_varargin_2) {
        b_varargin_2 = centerPixelSub_idx_1;
      }

      if (centerPixelSub_idx_0 < 1) {
        b_secondInd = 1;
      } else {
        b_secondInd = centerPixelSub_idx_0;
      }

      while (b_secondInd <= b_varargin_2) {
        if (1 <= varargin_2) {
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
               centerPixelSub_idx_0++) {
            a[centerPixelSub_idx_0] = nhoodObj->
              NeighborSubscriptOffsets[centerPixelSub_idx_0];
          }
        }

        for (b_firstInd = 1; b_firstInd <= varargin_2; b_firstInd++) {
          indx = nhoodObj->ImageSize[0];
          pind = (b_secondInd - 1) * indx + b_firstInd;
          for (i = 0; i < 5; i++) {
            nhInds[i] = nhoodObj->ImageNeighborLinearOffsets[i];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
               centerPixelSub_idx_0++) {
            nhInds[centerPixelSub_idx_0] += pind;
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imSize[centerPixelSub_idx_0] = nhoodObj->
              ImageSize[centerPixelSub_idx_0];
          }

          if (imSize[0] == 0) {
            r = 1;
          } else {
            r = pind - imSize[0] * div_s32(pind - 1, imSize[0]);
          }

          centerPixelSub_idx_0 = pind - r;
          if (imSize[0] == 0) {
            if (centerPixelSub_idx_0 == 0) {
              centerPixelSub_idx_1 = 0;
            } else if (centerPixelSub_idx_0 < 0) {
              centerPixelSub_idx_1 = MIN_int32_T;
            } else {
              centerPixelSub_idx_1 = MAX_int32_T;
            }
          } else if (imSize[0] == 1) {
            centerPixelSub_idx_1 = centerPixelSub_idx_0;
          } else if (imSize[0] == -1) {
            centerPixelSub_idx_1 = -centerPixelSub_idx_0;
          } else {
            if (centerPixelSub_idx_0 >= 0) {
              indx = centerPixelSub_idx_0;
            } else if (centerPixelSub_idx_0 == MIN_int32_T) {
              indx = MAX_int32_T;
            } else {
              indx = -centerPixelSub_idx_0;
            }

            if (imSize[0] >= 0) {
              i = imSize[0];
            } else if (imSize[0] == MIN_int32_T) {
              i = MAX_int32_T;
            } else {
              i = -imSize[0];
            }

            centerPixelSub_idx_1 = div_s32(indx, i);
            indx -= centerPixelSub_idx_1 * i;
            if ((indx > 0) && (indx >= (i >> 1) + (i & 1))) {
              centerPixelSub_idx_1++;
            }

            if ((centerPixelSub_idx_0 < 0) != (imSize[0] < 0)) {
              centerPixelSub_idx_1 = -centerPixelSub_idx_1;
            }
          }

          b_pixelSub[1] = centerPixelSub_idx_1 + 1;
          b_pixelSub[0] = r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            pixelsPerImPage[centerPixelSub_idx_0] =
              b_pixelSub[centerPixelSub_idx_0];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            for (indx = 0; indx < 5; indx++) {
              imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
                centerPixelSub_idx_0] + pixelsPerImPage[centerPixelSub_idx_0];
            }
          }

          for (i = 0; i < 5; i++) {
            isInside[i] = true;
          }

          switch ((int)nhoodObj->Padding) {
           case 1:
            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }

            b_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                b_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                b_imnhInds_data[centerPixelSub_idx_0] = nhInds[i];
                centerPixelSub_idx_0++;
              }
            }
            break;

           case 2:
            b_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              b_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  b_imnhInds_data[centerPixelSub_idx_1] = 1;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }
            break;

           case 3:
            b_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              b_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = 1;
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = nhoodObj->ImageSize[centerPixelSub_idx_0];
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                b_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;

           case 4:
            b_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              b_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = pixelsPerImPage[centerPixelSub_idx_0] + (indx << 1);
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = ((indx << 1) - i) + 1;
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                b_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;
          }

          p = (in->size[0] == 1);
          if (p) {
            if (0 <= b_trueCount - 1) {
              memcpy(&tmp_data[0], &b_imnhInds_data[0], (unsigned int)
                     (b_trueCount * (int)sizeof(int)));
            }

            centerPixelSub_idx_1 = 1;
            r = b_trueCount;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < b_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[tmp_data[centerPixelSub_idx_0] - 1];
            }
          } else {
            centerPixelSub_idx_1 = b_trueCount;
            r = 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < b_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[b_imnhInds_data[centerPixelSub_idx_0] - 1];
            }
          }

          if (nhoodObj->Padding == 2.0) {
            trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                c_tmp_data[centerPixelSub_idx_0] = i + 1;
                centerPixelSub_idx_0++;
              }
            }

            indx = trueCount - 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 <= indx;
                 centerPixelSub_idx_0++) {
              b_imnh_data[c_tmp_data[centerPixelSub_idx_0] - 1] = padValue;
            }
          }

          i = centerPixelSub_idx_1 * r + 1;
          indx = centerPixelSub_idx_1 * r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
               centerPixelSub_idx_0++) {
            b_varargin_1_data[centerPixelSub_idx_0] = (signed char)
              b_imnh_data[centerPixelSub_idx_0];
          }

          b_varargin_1_data[centerPixelSub_idx_1 * r] = 0;
          if (i <= 2) {
            if (i == 1) {
              indx = b_varargin_1_data[0];
            } else if (b_varargin_1_data[0] < b_varargin_1_data[1]) {
              indx = b_varargin_1_data[1];
            } else {
              indx = b_varargin_1_data[0];
            }
          } else {
            indx = b_varargin_1_data[0];
            for (centerPixelSub_idx_0 = 1; centerPixelSub_idx_0 < i;
                 centerPixelSub_idx_0++) {
              if (indx < b_varargin_1_data[centerPixelSub_idx_0]) {
                indx = b_varargin_1_data[centerPixelSub_idx_0];
              }
            }
          }

          B->data[pind - 1] = (indx != 0);
        }

        b_secondInd++;
      }

      centerPixelSub[1] = nhoodObj->InteriorStart[0] - 1.0;
      centerPixelSub_idx_1 = nhoodObj->ImageSize[1];
      padValue = (nhoodObj->PadValue != 0.0);
      varargin_2 = nhoodObj->ImageSize[0];
      if (rtIsNaN(centerPixelSub[1]) || (centerPixelSub[1] > varargin_2)) {
        minval = varargin_2;
      } else {
        minval = (int)centerPixelSub[1];
      }

      varargin_2 = nhoodObj->ImageSize[1];
      if (centerPixelSub_idx_1 < varargin_2) {
        varargin_2 = centerPixelSub_idx_1;
      }

      for (b_secondInd = 1; b_secondInd <= varargin_2; b_secondInd++) {
        if (0 <= minval - 1) {
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
               centerPixelSub_idx_0++) {
            a[centerPixelSub_idx_0] = nhoodObj->
              NeighborSubscriptOffsets[centerPixelSub_idx_0];
          }
        }

        for (b_firstInd = 0; b_firstInd < minval; b_firstInd++) {
          indx = nhoodObj->ImageSize[0];
          pind = (b_secondInd - 1) * indx + b_firstInd;
          for (i = 0; i < 5; i++) {
            nhInds[i] = nhoodObj->ImageNeighborLinearOffsets[i];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
               centerPixelSub_idx_0++) {
            nhInds[centerPixelSub_idx_0] = (nhInds[centerPixelSub_idx_0] + pind)
              + 1;
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imSize[centerPixelSub_idx_0] = nhoodObj->
              ImageSize[centerPixelSub_idx_0];
          }

          if (imSize[0] == 0) {
            r = 0;
          } else {
            r = pind - imSize[0] * div_s32(pind, imSize[0]);
          }

          centerPixelSub_idx_0 = pind - r;
          if (imSize[0] == 0) {
            if (centerPixelSub_idx_0 == 0) {
              centerPixelSub_idx_1 = 0;
            } else if (centerPixelSub_idx_0 < 0) {
              centerPixelSub_idx_1 = MIN_int32_T;
            } else {
              centerPixelSub_idx_1 = MAX_int32_T;
            }
          } else if (imSize[0] == 1) {
            centerPixelSub_idx_1 = centerPixelSub_idx_0;
          } else if (imSize[0] == -1) {
            centerPixelSub_idx_1 = -centerPixelSub_idx_0;
          } else {
            if (centerPixelSub_idx_0 >= 0) {
              indx = centerPixelSub_idx_0;
            } else if (centerPixelSub_idx_0 == MIN_int32_T) {
              indx = MAX_int32_T;
            } else {
              indx = -centerPixelSub_idx_0;
            }

            if (imSize[0] >= 0) {
              i = imSize[0];
            } else if (imSize[0] == MIN_int32_T) {
              i = MAX_int32_T;
            } else {
              i = -imSize[0];
            }

            centerPixelSub_idx_1 = div_s32(indx, i);
            indx -= centerPixelSub_idx_1 * i;
            if ((indx > 0) && (indx >= (i >> 1) + (i & 1))) {
              centerPixelSub_idx_1++;
            }

            if ((centerPixelSub_idx_0 < 0) != (imSize[0] < 0)) {
              centerPixelSub_idx_1 = -centerPixelSub_idx_1;
            }
          }

          c_pixelSub[1] = centerPixelSub_idx_1 + 1;
          c_pixelSub[0] = r + 1;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            pixelsPerImPage[centerPixelSub_idx_0] =
              c_pixelSub[centerPixelSub_idx_0];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            for (indx = 0; indx < 5; indx++) {
              imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
                centerPixelSub_idx_0] + pixelsPerImPage[centerPixelSub_idx_0];
            }
          }

          for (i = 0; i < 5; i++) {
            isInside[i] = true;
          }

          switch ((int)nhoodObj->Padding) {
           case 1:
            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }

            c_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                c_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                c_imnhInds_data[centerPixelSub_idx_0] = nhInds[i];
                centerPixelSub_idx_0++;
              }
            }
            break;

           case 2:
            c_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              c_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  c_imnhInds_data[centerPixelSub_idx_1] = 1;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }
            break;

           case 3:
            c_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              c_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = 1;
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = nhoodObj->ImageSize[centerPixelSub_idx_0];
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                c_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;

           case 4:
            c_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              c_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = pixelsPerImPage[centerPixelSub_idx_0] + (indx << 1);
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = ((indx << 1) - i) + 1;
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                c_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;
          }

          p = (in->size[0] == 1);
          if (p) {
            if (0 <= c_trueCount - 1) {
              memcpy(&tmp_data[0], &c_imnhInds_data[0], (unsigned int)
                     (c_trueCount * (int)sizeof(int)));
            }

            centerPixelSub_idx_1 = 1;
            r = c_trueCount;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < c_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[tmp_data[centerPixelSub_idx_0] - 1];
            }
          } else {
            centerPixelSub_idx_1 = c_trueCount;
            r = 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < c_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[c_imnhInds_data[centerPixelSub_idx_0] - 1];
            }
          }

          if (nhoodObj->Padding == 2.0) {
            b_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                b_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                d_tmp_data[centerPixelSub_idx_0] = i + 1;
                centerPixelSub_idx_0++;
              }
            }

            indx = b_trueCount - 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 <= indx;
                 centerPixelSub_idx_0++) {
              b_imnh_data[d_tmp_data[centerPixelSub_idx_0] - 1] = padValue;
            }
          }

          i = centerPixelSub_idx_1 * r + 1;
          indx = centerPixelSub_idx_1 * r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
               centerPixelSub_idx_0++) {
            b_varargin_1_data[centerPixelSub_idx_0] = (signed char)
              b_imnh_data[centerPixelSub_idx_0];
          }

          b_varargin_1_data[centerPixelSub_idx_1 * r] = 0;
          if (i <= 2) {
            if (i == 1) {
              indx = b_varargin_1_data[0];
            } else if (b_varargin_1_data[0] < b_varargin_1_data[1]) {
              indx = b_varargin_1_data[1];
            } else {
              indx = b_varargin_1_data[0];
            }
          } else {
            indx = b_varargin_1_data[0];
            for (centerPixelSub_idx_0 = 1; centerPixelSub_idx_0 < i;
                 centerPixelSub_idx_0++) {
              if (indx < b_varargin_1_data[centerPixelSub_idx_0]) {
                indx = b_varargin_1_data[centerPixelSub_idx_0];
              }
            }
          }

          B->data[pind] = (indx != 0);
        }
      }

      firstIndRange[0] = nhoodObj->InteriorEnd[0] + 1;
      firstIndRange[1] = nhoodObj->ImageSize[0];
      centerPixelSub_idx_1 = nhoodObj->ImageSize[1];
      padValue = (nhoodObj->PadValue != 0.0);
      if (firstIndRange[0] < 1) {
        minval = 1;
      } else {
        minval = firstIndRange[0];
      }

      if (firstIndRange[0] < 1) {
        firstIndRange[0] = 1;
      }

      varargin_2 = nhoodObj->ImageSize[0];
      indx = firstIndRange[1];
      if (indx < varargin_2) {
        varargin_2 = indx;
      }

      b_varargin_2 = nhoodObj->ImageSize[1];
      if (centerPixelSub_idx_1 < b_varargin_2) {
        b_varargin_2 = centerPixelSub_idx_1;
      }

      for (b_secondInd = 1; b_secondInd <= b_varargin_2; b_secondInd++) {
        if (firstIndRange[0] <= varargin_2) {
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
               centerPixelSub_idx_0++) {
            a[centerPixelSub_idx_0] = nhoodObj->
              NeighborSubscriptOffsets[centerPixelSub_idx_0];
          }
        }

        for (b_firstInd = minval; b_firstInd <= varargin_2; b_firstInd++) {
          indx = nhoodObj->ImageSize[0];
          pind = (b_secondInd - 1) * indx + b_firstInd;
          for (i = 0; i < 5; i++) {
            nhInds[i] = nhoodObj->ImageNeighborLinearOffsets[i];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
               centerPixelSub_idx_0++) {
            nhInds[centerPixelSub_idx_0] += pind;
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imSize[centerPixelSub_idx_0] = nhoodObj->
              ImageSize[centerPixelSub_idx_0];
          }

          if (imSize[0] == 0) {
            r = 1;
          } else {
            r = pind - imSize[0] * div_s32(pind - 1, imSize[0]);
          }

          centerPixelSub_idx_0 = pind - r;
          if (imSize[0] == 0) {
            if (centerPixelSub_idx_0 == 0) {
              centerPixelSub_idx_1 = 0;
            } else if (centerPixelSub_idx_0 < 0) {
              centerPixelSub_idx_1 = MIN_int32_T;
            } else {
              centerPixelSub_idx_1 = MAX_int32_T;
            }
          } else if (imSize[0] == 1) {
            centerPixelSub_idx_1 = centerPixelSub_idx_0;
          } else if (imSize[0] == -1) {
            centerPixelSub_idx_1 = -centerPixelSub_idx_0;
          } else {
            if (centerPixelSub_idx_0 >= 0) {
              indx = centerPixelSub_idx_0;
            } else if (centerPixelSub_idx_0 == MIN_int32_T) {
              indx = MAX_int32_T;
            } else {
              indx = -centerPixelSub_idx_0;
            }

            if (imSize[0] >= 0) {
              i = imSize[0];
            } else if (imSize[0] == MIN_int32_T) {
              i = MAX_int32_T;
            } else {
              i = -imSize[0];
            }

            centerPixelSub_idx_1 = div_s32(indx, i);
            indx -= centerPixelSub_idx_1 * i;
            if ((indx > 0) && (indx >= (i >> 1) + (i & 1))) {
              centerPixelSub_idx_1++;
            }

            if ((centerPixelSub_idx_0 < 0) != (imSize[0] < 0)) {
              centerPixelSub_idx_1 = -centerPixelSub_idx_1;
            }
          }

          d_pixelSub[1] = centerPixelSub_idx_1 + 1;
          d_pixelSub[0] = r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            pixelsPerImPage[centerPixelSub_idx_0] =
              d_pixelSub[centerPixelSub_idx_0];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            for (indx = 0; indx < 5; indx++) {
              imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
                centerPixelSub_idx_0] + pixelsPerImPage[centerPixelSub_idx_0];
            }
          }

          for (i = 0; i < 5; i++) {
            isInside[i] = true;
          }

          switch ((int)nhoodObj->Padding) {
           case 1:
            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }

            d_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                d_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                d_imnhInds_data[centerPixelSub_idx_0] = nhInds[i];
                centerPixelSub_idx_0++;
              }
            }
            break;

           case 2:
            d_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              d_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  d_imnhInds_data[centerPixelSub_idx_1] = 1;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }
            break;

           case 3:
            d_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              d_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = 1;
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = nhoodObj->ImageSize[centerPixelSub_idx_0];
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                d_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;

           case 4:
            d_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              d_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = pixelsPerImPage[centerPixelSub_idx_0] + (indx << 1);
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = ((indx << 1) - i) + 1;
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                d_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;
          }

          p = (in->size[0] == 1);
          if (p) {
            if (0 <= d_trueCount - 1) {
              memcpy(&tmp_data[0], &d_imnhInds_data[0], (unsigned int)
                     (d_trueCount * (int)sizeof(int)));
            }

            centerPixelSub_idx_1 = 1;
            r = d_trueCount;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < d_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[tmp_data[centerPixelSub_idx_0] - 1];
            }
          } else {
            centerPixelSub_idx_1 = d_trueCount;
            r = 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < d_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[d_imnhInds_data[centerPixelSub_idx_0] - 1];
            }
          }

          if (nhoodObj->Padding == 2.0) {
            c_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                c_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                e_tmp_data[centerPixelSub_idx_0] = i + 1;
                centerPixelSub_idx_0++;
              }
            }

            indx = c_trueCount - 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 <= indx;
                 centerPixelSub_idx_0++) {
              b_imnh_data[e_tmp_data[centerPixelSub_idx_0] - 1] = padValue;
            }
          }

          i = centerPixelSub_idx_1 * r + 1;
          indx = centerPixelSub_idx_1 * r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
               centerPixelSub_idx_0++) {
            b_varargin_1_data[centerPixelSub_idx_0] = (signed char)
              b_imnh_data[centerPixelSub_idx_0];
          }

          b_varargin_1_data[centerPixelSub_idx_1 * r] = 0;
          if (i <= 2) {
            if (i == 1) {
              indx = b_varargin_1_data[0];
            } else if (b_varargin_1_data[0] < b_varargin_1_data[1]) {
              indx = b_varargin_1_data[1];
            } else {
              indx = b_varargin_1_data[0];
            }
          } else {
            indx = b_varargin_1_data[0];
            for (centerPixelSub_idx_0 = 1; centerPixelSub_idx_0 < i;
                 centerPixelSub_idx_0++) {
              if (indx < b_varargin_1_data[centerPixelSub_idx_0]) {
                indx = b_varargin_1_data[centerPixelSub_idx_0];
              }
            }
          }

          B->data[pind - 1] = (indx != 0);
        }
      }
    }

    emxFree_boolean_T(&in);
  }
}

static void polyfit(const emxArray_real_T *x, const emxArray_real_T *y, double
                    p[3])
{
  emxArray_real_T *r0;
  int b_y[1];
  emxArray_real_T c_y;
  int rr;
  emxInit_real_T1(&r0, 2);
  vander(x, r0);
  b_y[0] = y->size[0];
  c_y = *y;
  c_y.size = (int *)&b_y;
  c_y.numDimensions = 1;
  qrsolve(r0, &c_y, p, &rr);
  emxFree_real_T(&r0);
}

static void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  int a_idx_0;
  int b_a_idx_0;
  int i3;
  a_idx_0 = a->size[0];
  b_a_idx_0 = a->size[0];
  i3 = y->size[0];
  y->size[0] = b_a_idx_0;
  emxEnsureCapacity_real_T1(y, i3);
  for (b_a_idx_0 = 0; b_a_idx_0 < a_idx_0; b_a_idx_0++) {
    y->data[b_a_idx_0] = a->data[b_a_idx_0] * a->data[b_a_idx_0];
  }
}

static void qrsolve(const emxArray_real_T *A, const emxArray_real_T *B, double
                    Y[3], int *rankR)
{
  int mn;
  emxArray_real_T *b_A;
  int i2;
  int loop_ub;
  emxArray_real_T *b_B;
  double tau_data[3];
  int tau_size[1];
  int jpvt[3];
  mn = A->size[0];
  if (!(mn < 3)) {
    mn = 3;
  }

  emxInit_real_T1(&b_A, 2);
  i2 = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = 3;
  emxEnsureCapacity_real_T(b_A, i2);
  loop_ub = A->size[0] * A->size[1];
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_A->data[i2] = A->data[i2];
  }

  emxInit_real_T(&b_B, 1);
  xgeqp3(b_A, tau_data, tau_size, jpvt);
  *rankR = rankFromQR(b_A);
  i2 = b_B->size[0];
  b_B->size[0] = B->size[0];
  emxEnsureCapacity_real_T1(b_B, i2);
  loop_ub = B->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_B->data[i2] = B->data[i2];
  }

  LSQFromQR(b_A, tau_data, jpvt, b_B, mn, Y);
  emxFree_real_T(&b_B);
  emxFree_real_T(&b_A);
}

static int rankFromQR(const emxArray_real_T *A)
{
  int r;
  int minmn;
  int maxmn;
  double tol;
  r = 0;
  if (A->size[0] < 3) {
    minmn = A->size[0];
    maxmn = 3;
  } else {
    minmn = 3;
    maxmn = A->size[0];
  }

  if (minmn > 0) {
    tol = (double)maxmn * std::abs(A->data[0]) * 2.2204460492503131E-16;
    while ((r < minmn) && (!(std::abs(A->data[r + A->size[0] * r]) <= tol))) {
      r++;
    }
  }

  return r;
}

static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = 1.0;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

static double rt_remd_snf(double u0, double u1)
{
  double y;
  double b_u1;
  double q;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    y = rtNaN;
  } else {
    if (u1 < 0.0) {
      b_u1 = std::ceil(u1);
    } else {
      b_u1 = std::floor(u1);
    }

    if ((u1 != 0.0) && (u1 != b_u1)) {
      q = std::abs(u0 / u1);
      if (std::abs(q - std::floor(q + 0.5)) <= DBL_EPSILON * q) {
        y = 0.0 * u0;
      } else {
        y = std::fmod(u0, u1);
      }
    } else {
      y = std::fmod(u0, u1);
    }
  }

  return y;
}

static void sum(const emxArray_uint8_T *x, double y_data[], int y_size[2])
{
  int i;
  int xpageoffset;
  int k;
  if (x->size[1] == 0) {
    y_size[0] = 1;
    y_size[1] = 0;
  } else {
    y_size[0] = 1;
    y_size[1] = (short)x->size[1];
    for (i = 0; i < x->size[1]; i++) {
      xpageoffset = i * 181;
      y_data[i] = x->data[xpageoffset];
      for (k = 0; k < 180; k++) {
        y_data[i] += (double)x->data[(xpageoffset + k) + 1];
      }
    }
  }
}

static void vander(const emxArray_real_T *v, emxArray_real_T *A)
{
  int n;
  int k;
  n = v->size[0] - 1;
  k = A->size[0] * A->size[1];
  A->size[0] = v->size[0];
  A->size[1] = 3;
  emxEnsureCapacity_real_T(A, k);
  if (A->size[0] != 0) {
    for (k = 0; k <= n; k++) {
      A->data[k + (A->size[0] << 1)] = 1.0;
    }

    for (k = 0; k <= n; k++) {
      A->data[k + A->size[0]] = v->data[k];
    }

    for (k = 0; k <= n; k++) {
      A->data[k] = v->data[k] * A->data[k + A->size[0]];
    }
  }
}

static void xgemv(int m, int n, const emxArray_real_T *A, int ia0, int lda,
                  const emxArray_real_T *x, int ix0, double y[3])
{
  int iy;
  int i5;
  int iac;
  int ix;
  double c;
  int i6;
  int ia;
  if (n != 0) {
    for (iy = 1; iy <= n; iy++) {
      y[iy - 1] = 0.0;
    }

    iy = 0;
    i5 = ia0 + lda * (n - 1);
    iac = ia0;
    while ((lda > 0) && (iac <= i5)) {
      ix = ix0;
      c = 0.0;
      i6 = (iac + m) - 1;
      for (ia = iac; ia <= i6; ia++) {
        c += A->data[ia - 1] * x->data[ix - 1];
        ix++;
      }

      y[iy] += c;
      iy++;
      iac += lda;
    }
  }
}

static void xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int
                   jpvt[3])
{
  int m;
  int mn;
  int k;
  int j;
  int i;
  double work[3];
  double temp1;
  double vn2[3];
  int mmi;
  double vn1[3];
  int itemp;
  double temp2;
  m = A->size[0];
  mn = A->size[0];
  if (!(mn < 3)) {
    mn = 3;
  }

  tau_size[0] = mn;
  for (k = 0; k < 3; k++) {
    jpvt[k] = 1 + k;
  }

  if (A->size[0] != 0) {
    k = 1;
    for (j = 0; j < 3; j++) {
      work[j] = 0.0;
      temp1 = xnrm2(m, A, k);
      vn2[j] = temp1;
      k += m;
      vn1[j] = temp1;
    }

    for (i = 1; i <= mn; i++) {
      k = (i + (i - 1) * m) - 1;
      mmi = m - i;
      j = (i + ixamax(4 - i, vn1, i)) - 2;
      if (j + 1 != i) {
        xswap(m, A, 1 + m * j, 1 + m * (i - 1));
        itemp = jpvt[j];
        jpvt[j] = jpvt[i - 1];
        jpvt[i - 1] = itemp;
        vn1[j] = vn1[i - 1];
        vn2[j] = vn2[i - 1];
      }

      if (i < m) {
        temp1 = A->data[k];
        tau_data[i - 1] = xzlarfg(mmi + 1, &temp1, A, k + 2);
        A->data[k] = temp1;
      } else {
        tau_data[i - 1] = 0.0;
      }

      if (i < 3) {
        temp1 = A->data[k];
        A->data[k] = 1.0;
        xzlarf(mmi + 1, 3 - i, k + 1, tau_data[i - 1], A, i + i * m, m, work);
        A->data[k] = temp1;
      }

      for (j = i; j + 1 < 4; j++) {
        if (vn1[j] != 0.0) {
          temp1 = std::abs(A->data[(i + A->size[0] * j) - 1]) / vn1[j];
          temp1 = 1.0 - temp1 * temp1;
          if (temp1 < 0.0) {
            temp1 = 0.0;
          }

          temp2 = vn1[j] / vn2[j];
          temp2 = temp1 * (temp2 * temp2);
          if (temp2 <= 1.4901161193847656E-8) {
            if (i < m) {
              vn1[j] = xnrm2(mmi, A, (i + m * j) + 1);
              vn2[j] = vn1[j];
            } else {
              vn1[j] = 0.0;
              vn2[j] = 0.0;
            }
          } else {
            b_sqrt(&temp1);
            vn1[j] *= temp1;
          }
        }
      }
    }
  }
}

static void xgerc(int m, int n, double alpha1, int ix0, const double y[3],
                  emxArray_real_T *A, int ia0, int lda)
{
  int jA;
  int jy;
  int j;
  double temp;
  int ix;
  int i7;
  int ijA;
  if (!(alpha1 == 0.0)) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if (y[jy] != 0.0) {
        temp = y[jy] * alpha1;
        ix = ix0;
        i7 = m + jA;
        for (ijA = jA; ijA < i7; ijA++) {
          A->data[ijA] += A->data[ix - 1] * temp;
          ix++;
        }
      }

      jy++;
      jA += lda;
    }
  }
}

static double xnrm2(int n, const emxArray_real_T *x, int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = std::abs(x->data[ix0 - 1]);
    } else {
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = std::abs(x->data[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = 1.0 + y * t * t;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * std::sqrt(y);
    }
  }

  return y;
}

static void xswap(int n, emxArray_real_T *x, int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 1; k <= n; k++) {
    temp = x->data[ix];
    x->data[ix] = x->data[iy];
    x->data[iy] = temp;
    ix++;
    iy++;
  }
}

static void xzlarf(int m, int n, int iv0, double tau, emxArray_real_T *C, int
                   ic0, int ldc, double work[3])
{
  int lastv;
  int lastc;
  if (tau != 0.0) {
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C->data[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = ilazlc(lastv, n, C, ic0, ldc);
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    xgemv(lastv, lastc, C, ic0, ldc, C, iv0, work);
    xgerc(lastv, lastc, -tau, iv0, work, C, ic0, ldc);
  }
}

static double xzlarfg(int n, double *alpha1, emxArray_real_T *x, int ix0)
{
  double tau;
  double xnorm;
  int knt;
  int i4;
  int k;
  tau = 0.0;
  if (!(n <= 0)) {
    xnorm = xnrm2(n - 1, x, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (std::abs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        i4 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i4; k++) {
            x->data[k - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(std::abs(xnorm) >= 1.0020841800044864E-292));

        xnorm = rt_hypotd_snf(*alpha1, xnrm2(n - 1, x, ix0));
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i4 = (ix0 + n) - 2;
        for (k = ix0; k <= i4; k++) {
          x->data[k - 1] *= *alpha1;
        }

        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i4 = (ix0 + n) - 2;
        for (k = ix0; k <= i4; k++) {
          x->data[k - 1] *= *alpha1;
        }

        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

void processedout(const emxArray_uint8_T *Binaryimage, double PointsA[720],
                  double PointsB[720], int *AlertSide, double center_data[], int
                  center_size[1], double *left_curvature, double
                  *right_curveature)
{
  emxArray_boolean_T *binary_strel;
  emxArray_uint8_T *binary_image;
  emxArray_boolean_T *B;
  int ii;
  int idx;
  double left_fit_cr[3];
  double right_fit_cr[3];
  double y;
  double x[10];
  static const double b[10] = { 0.0, 4.9382716049382722, 19.753086419753089,
    44.44444444444445, 79.012345679012356, 123.45679012345678, 177.7777777777778,
    241.97530864197535, 316.04938271604942, 400.0 };

  int jj;
  static const double dv0[360] = { 0.083333333333333329, 0.16666666666666666,
    0.25, 0.33333333333333331, 0.41666666666666663, 0.5, 0.58333333333333326,
    0.66666666666666663, 0.75, 0.83333333333333326, 0.91666666666666663, 1.0,
    1.0833333333333333, 1.1666666666666665, 1.25, 1.3333333333333333,
    1.4166666666666665, 1.5, 1.5833333333333333, 1.6666666666666665, 1.75,
    1.8333333333333333, 1.9166666666666665, 2.0, 2.083333333333333,
    2.1666666666666665, 2.25, 2.333333333333333, 2.4166666666666665, 2.5,
    2.583333333333333, 2.6666666666666665, 2.75, 2.833333333333333,
    2.9166666666666665, 3.0, 3.083333333333333, 3.1666666666666665, 3.25,
    3.333333333333333, 3.4166666666666665, 3.5, 3.583333333333333,
    3.6666666666666665, 3.75, 3.833333333333333, 3.9166666666666665, 4.0,
    4.083333333333333, 4.1666666666666661, 4.25, 4.333333333333333,
    4.4166666666666661, 4.5, 4.583333333333333, 4.6666666666666661, 4.75,
    4.833333333333333, 4.9166666666666661, 5.0, 5.083333333333333,
    5.1666666666666661, 5.25, 5.333333333333333, 5.4166666666666661, 5.5,
    5.583333333333333, 5.6666666666666661, 5.75, 5.833333333333333,
    5.9166666666666661, 6.0, 6.083333333333333, 6.1666666666666661, 6.25,
    6.333333333333333, 6.4166666666666661, 6.5, 6.583333333333333,
    6.6666666666666661, 6.75, 6.833333333333333, 6.9166666666666661, 7.0,
    7.083333333333333, 7.1666666666666661, 7.25, 7.333333333333333,
    7.4166666666666661, 7.5, 7.583333333333333, 7.6666666666666661, 7.75,
    7.833333333333333, 7.9166666666666661, 8.0, 8.0833333333333321,
    8.1666666666666661, 8.25, 8.3333333333333321, 8.4166666666666661, 8.5,
    8.5833333333333321, 8.6666666666666661, 8.75, 8.8333333333333321,
    8.9166666666666661, 9.0, 9.0833333333333321, 9.1666666666666661, 9.25,
    9.3333333333333321, 9.4166666666666661, 9.5, 9.5833333333333321,
    9.6666666666666661, 9.75, 9.8333333333333321, 9.9166666666666661, 10.0,
    10.083333333333332, 10.166666666666666, 10.25, 10.333333333333332,
    10.416666666666666, 10.5, 10.583333333333332, 10.666666666666666, 10.75,
    10.833333333333332, 10.916666666666666, 11.0, 11.083333333333332,
    11.166666666666666, 11.25, 11.333333333333332, 11.416666666666666, 11.5,
    11.583333333333332, 11.666666666666666, 11.75, 11.833333333333332,
    11.916666666666666, 12.0, 12.083333333333332, 12.166666666666666, 12.25,
    12.333333333333332, 12.416666666666666, 12.5, 12.583333333333332,
    12.666666666666666, 12.75, 12.833333333333332, 12.916666666666666, 13.0,
    13.083333333333332, 13.166666666666666, 13.25, 13.333333333333332,
    13.416666666666666, 13.5, 13.583333333333332, 13.666666666666666, 13.75,
    13.833333333333332, 13.916666666666666, 14.0, 14.083333333333332,
    14.166666666666666, 14.25, 14.333333333333332, 14.416666666666666, 14.5,
    14.583333333333332, 14.666666666666666, 14.75, 14.833333333333332,
    14.916666666666666, 15.0, 15.083333333333332, 15.166666666666666, 15.25,
    15.333333333333332, 15.416666666666666, 15.5, 15.583333333333332,
    15.666666666666666, 15.75, 15.833333333333332, 15.916666666666666, 16.0,
    16.083333333333332, 16.166666666666664, 16.25, 16.333333333333332,
    16.416666666666664, 16.5, 16.583333333333332, 16.666666666666664, 16.75,
    16.833333333333332, 16.916666666666664, 17.0, 17.083333333333332,
    17.166666666666664, 17.25, 17.333333333333332, 17.416666666666664, 17.5,
    17.583333333333332, 17.666666666666664, 17.75, 17.833333333333332,
    17.916666666666664, 18.0, 18.083333333333332, 18.166666666666664, 18.25,
    18.333333333333332, 18.416666666666664, 18.5, 18.583333333333332,
    18.666666666666664, 18.75, 18.833333333333332, 18.916666666666664, 19.0,
    19.083333333333332, 19.166666666666664, 19.25, 19.333333333333332,
    19.416666666666664, 19.5, 19.583333333333332, 19.666666666666664, 19.75,
    19.833333333333332, 19.916666666666664, 20.0, 20.083333333333332,
    20.166666666666664, 20.25, 20.333333333333332, 20.416666666666664, 20.5,
    20.583333333333332, 20.666666666666664, 20.75, 20.833333333333332,
    20.916666666666664, 21.0, 21.083333333333332, 21.166666666666664, 21.25,
    21.333333333333332, 21.416666666666664, 21.5, 21.583333333333332,
    21.666666666666664, 21.75, 21.833333333333332, 21.916666666666664, 22.0,
    22.083333333333332, 22.166666666666664, 22.25, 22.333333333333332,
    22.416666666666664, 22.5, 22.583333333333332, 22.666666666666664, 22.75,
    22.833333333333332, 22.916666666666664, 23.0, 23.083333333333332,
    23.166666666666664, 23.25, 23.333333333333332, 23.416666666666664, 23.5,
    23.583333333333332, 23.666666666666664, 23.75, 23.833333333333332,
    23.916666666666664, 24.0, 24.083333333333332, 24.166666666666664, 24.25,
    24.333333333333332, 24.416666666666664, 24.5, 24.583333333333332,
    24.666666666666664, 24.75, 24.833333333333332, 24.916666666666664, 25.0,
    25.083333333333332, 25.166666666666664, 25.25, 25.333333333333332,
    25.416666666666664, 25.5, 25.583333333333332, 25.666666666666664, 25.75,
    25.833333333333332, 25.916666666666664, 26.0, 26.083333333333332,
    26.166666666666664, 26.25, 26.333333333333332, 26.416666666666664, 26.5,
    26.583333333333332, 26.666666666666664, 26.75, 26.833333333333332,
    26.916666666666664, 27.0, 27.083333333333332, 27.166666666666664, 27.25,
    27.333333333333332, 27.416666666666664, 27.5, 27.583333333333332,
    27.666666666666664, 27.75, 27.833333333333332, 27.916666666666664, 28.0,
    28.083333333333332, 28.166666666666664, 28.25, 28.333333333333332,
    28.416666666666664, 28.5, 28.583333333333332, 28.666666666666664, 28.75,
    28.833333333333332, 28.916666666666664, 29.0, 29.083333333333332,
    29.166666666666664, 29.25, 29.333333333333332, 29.416666666666664, 29.5,
    29.583333333333332, 29.666666666666664, 29.75, 29.833333333333332,
    29.916666666666664, 30.0 };

  double left_fitx[360];
  static const int b_b[360] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144,
    169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729,
    784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600,
    1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809,
    2916, 3025, 3136, 3249, 3364, 3481, 3600, 3721, 3844, 3969, 4096, 4225, 4356,
    4489, 4624, 4761, 4900, 5041, 5184, 5329, 5476, 5625, 5776, 5929, 6084, 6241,
    6400, 6561, 6724, 6889, 7056, 7225, 7396, 7569, 7744, 7921, 8100, 8281, 8464,
    8649, 8836, 9025, 9216, 9409, 9604, 9801, 10000, 10201, 10404, 10609, 10816,
    11025, 11236, 11449, 11664, 11881, 12100, 12321, 12544, 12769, 12996, 13225,
    13456, 13689, 13924, 14161, 14400, 14641, 14884, 15129, 15376, 15625, 15876,
    16129, 16384, 16641, 16900, 17161, 17424, 17689, 17956, 18225, 18496, 18769,
    19044, 19321, 19600, 19881, 20164, 20449, 20736, 21025, 21316, 21609, 21904,
    22201, 22500, 22801, 23104, 23409, 23716, 24025, 24336, 24649, 24964, 25281,
    25600, 25921, 26244, 26569, 26896, 27225, 27556, 27889, 28224, 28561, 28900,
    29241, 29584, 29929, 30276, 30625, 30976, 31329, 31684, 32041, 32400, 32761,
    33124, 33489, 33856, 34225, 34596, 34969, 35344, 35721, 36100, 36481, 36864,
    37249, 37636, 38025, 38416, 38809, 39204, 39601, 40000, 40401, 40804, 41209,
    41616, 42025, 42436, 42849, 43264, 43681, 44100, 44521, 44944, 45369, 45796,
    46225, 46656, 47089, 47524, 47961, 48400, 48841, 49284, 49729, 50176, 50625,
    51076, 51529, 51984, 52441, 52900, 53361, 53824, 54289, 54756, 55225, 55696,
    56169, 56644, 57121, 57600, 58081, 58564, 59049, 59536, 60025, 60516, 61009,
    61504, 62001, 62500, 63001, 63504, 64009, 64516, 65025, 65536, 66049, 66564,
    67081, 67600, 68121, 68644, 69169, 69696, 70225, 70756, 71289, 71824, 72361,
    72900, 73441, 73984, 74529, 75076, 75625, 76176, 76729, 77284, 77841, 78400,
    78961, 79524, 80089, 80656, 81225, 81796, 82369, 82944, 83521, 84100, 84681,
    85264, 85849, 86436, 87025, 87616, 88209, 88804, 89401, 90000, 90601, 91204,
    91809, 92416, 93025, 93636, 94249, 94864, 95481, 96100, 96721, 97344, 97969,
    98596, 99225, 99856, 100489, 101124, 101761, 102400, 103041, 103684, 104329,
    104976, 105625, 106276, 106929, 107584, 108241, 108900, 109561, 110224,
    110889, 111556, 112225, 112896, 113569, 114244, 114921, 115600, 116281,
    116964, 117649, 118336, 119025, 119716, 120409, 121104, 121801, 122500,
    123201, 123904, 124609, 125316, 126025, 126736, 127449, 128164, 128881,
    129600 };

  double right_fitx;
  double b_right_fitx[360];
  bool exitg1;
  double v_data[1];
  bool b_y;
  bool x_data[1];
  emxInit_boolean_T(&binary_strel, 2);
  emxInit_uint8_T(&binary_image, 2);
  emxInit_boolean_T(&B, 2);
  bwareaopen(Binaryimage, binary_strel);
  ii = B->size[0] * B->size[1];
  B->size[0] = binary_strel->size[0];
  B->size[1] = binary_strel->size[1];
  emxEnsureCapacity_boolean_T(B, ii);
  morphopAlgo(binary_strel, B);
  ii = binary_image->size[0] * binary_image->size[1];
  binary_image->size[0] = B->size[0];
  binary_image->size[1] = B->size[1];
  emxEnsureCapacity_uint8_T(binary_image, ii);
  idx = B->size[0] * B->size[1];
  emxFree_boolean_T(&binary_strel);
  for (ii = 0; ii < idx; ii++) {
    binary_image->data[ii] = (unsigned char)(B->data[ii] * 255U);
  }

  emxFree_boolean_T(&B);
  if (counter == 400.0) {
    counter = 0.0;
    ImageTestFunction(binary_image, left_fit, right_fit);
    for (ii = 0; ii < 3; ii++) {
      last_left[ii] = left_fit[ii];
      last_right[ii] = right_fit[ii];
    }
  } else {
    VideoProcess(binary_image, left_fit, right_fit, left_fit_cr, right_fit_cr);
    for (ii = 0; ii < 3; ii++) {
      left_fit[ii] = left_fit_cr[ii];
      right_fit[ii] = right_fit_cr[ii];
    }
  }

  emxFree_uint8_T(&binary_image);
  for (ii = 0; ii < 10; ii++) {
    x[ii] = ((right_fit[0] * b[ii] + right_fit[1] * (2.2222222222222223 *
               (double)ii)) + right_fit[2]) - ((left_fit[0] * b[ii] + left_fit[1]
      * (2.2222222222222223 * (double)ii)) + left_fit[2]);
  }

  y = x[0];
  for (idx = 0; idx < 9; idx++) {
    y += x[idx + 1];
  }

  if ((std::abs((2.0 * left_fit[0] + left_fit[1]) - (2.0 * right_fit[0] +
         right_fit[1])) <= 0.9) && (std::abs((2.0 * left_fit[0] * 360.0 +
         left_fit[1]) - (2.0 * right_fit[0] * 360.0 + right_fit[1])) <= 0.9) &&
      (std::abs((2.0 * right_fit[0] * 180.0 + right_fit[1]) - (2.0 * left_fit[0]
         * 180.0 + left_fit[1])) <= 0.9) && (y / 10.0 > 75.0)) {
    for (ii = 0; ii < 3; ii++) {
      last_left[ii] = left_fit[ii];
      last_right[ii] = right_fit[ii];
    }

    counter++;
  } else {
    for (ii = 0; ii < 3; ii++) {
      left_fit[ii] = last_left[ii];
      right_fit[ii] = last_right[ii];
    }
  }

  jj = 1;
  for (idx = 0; idx < 359; idx++) {
    if (jj < idx + 2) {
      jj = idx + 2;
    }
  }

  /* Curvature calulation */
  for (ii = 0; ii < 360; ii++) {
    y = (left_fit[0] * (double)b_b[ii] + left_fit[1] * (1.0 + (double)ii)) +
      left_fit[2];
    right_fitx = (right_fit[0] * (double)b_b[ii] + right_fit[1] * (1.0 + (double)
      ii)) + right_fit[2];
    PointsA[ii] = y;
    PointsA[360 + ii] = 1.0 + (double)ii;
    PointsB[ii] = right_fitx;
    PointsB[360 + ii] = 1.0 + (double)ii;
    left_fitx[ii] = y * 0.010571428571428572;
    b_right_fitx[ii] = right_fitx;
  }

  b_polyfit(dv0, left_fitx, left_fit_cr);
  for (ii = 0; ii < 360; ii++) {
    left_fitx[ii] = b_right_fitx[ii] * 0.010571428571428572;
  }

  b_polyfit(dv0, left_fitx, right_fit_cr);
  y = 2.0 * left_fit_cr[0] * (double)jj * 0.083333333333333329 + left_fit_cr[1];
  *left_curvature = rt_powd_snf(1.0 + y * y, 1.5) / std::abs(2.0 * left_fit_cr[0]);
  y = 2.0 * right_fit_cr[0] * (double)jj * 0.083333333333333329 + right_fit_cr[1];
  *right_curveature = rt_powd_snf(1.0 + y * y, 1.5) / std::abs(2.0 *
    right_fit_cr[0]);
  idx = 0;
  center_size[0] = 1;
  ii = 359;
  jj = 1;
  exitg1 = false;
  while ((!exitg1) && (jj > 0)) {
    if (PointsA[ii] != 0.0) {
      idx = 1;
      center_data[0] = PointsA[ii];
      exitg1 = true;
    } else {
      ii--;
      if (ii + 1 < 1) {
        ii = 359;
        jj = 0;
      }
    }
  }

  if (idx == 0) {
    center_size[0] = 0;
  }

  ii = 359;
  jj = 1;
  exitg1 = false;
  while ((!exitg1) && (jj > 0)) {
    if (PointsB[ii] != 0.0) {
      v_data[0] = PointsB[ii];
      exitg1 = true;
    } else {
      ii--;
      if (ii + 1 < 1) {
        ii = 359;
        jj = 0;
      }
    }
  }

  /* left_lane_bottom = (((left_fit(1,1)*y_eval).^2) + (left_fit(1,1)*y_eval) + (left_fit(1,3))); */
  /* right_lane_bottom = (((right_fit(1,1)*y_eval).^2) + (right_fit(1,1)*y_eval) + (right_fit(1,3))); */
  idx = center_size[0];
  for (ii = 0; ii < idx; ii++) {
    center_data[ii] = ((center_data[ii] + v_data[ii]) / 2.0 - 320.0) *
      0.010571428571428572;
  }

  idx = center_size[0];
  for (ii = 0; ii < idx; ii++) {
    x_data[ii] = (center_data[ii] < 0.0);
  }

  b_y = !(center_size[0] == 0);
  if (b_y) {
    idx = 1;
    exitg1 = false;
    while ((!exitg1) && (idx <= center_size[0])) {
      if (!x_data[0]) {
        b_y = false;
        exitg1 = true;
      } else {
        idx = 2;
      }
    }
  }

  if (b_y) {
    *AlertSide = 1;
  } else {
    *AlertSide = 2;
  }
}

void processedout_initialize()
{
  int i0;
  static const double b_last_right[3] = { 0.00018116581828425175,
    -0.087427288003327164, 584.66140963106932 };

  static const double b_last_left[3] = { 3.2390492747651419E-6,
    -0.026398650995851397, 183.95119780475775 };

  static const double b_right_fit[3] = { 0.00018116581828425175,
    -0.087427288003327164, 584.66140963106932 };

  static const double b_left_fit[3] = { 3.2390492747651419E-6,
    -0.026398650995851397, 183.95119780475775 };

  rt_InitInfAndNaN(8U);
  omp_init_nest_lock(&emlrtNestLockGlobal);
  for (i0 = 0; i0 < 3; i0++) {
    last_right[i0] = b_last_right[i0];
    last_left[i0] = b_last_left[i0];
    right_fit[i0] = b_right_fit[i0];
    left_fit[i0] = b_left_fit[i0];
  }

  counter = b_counter;
  ImageTestFunction_init();
}

void processedout_terminate()
{
  ImageTestFunction_free();
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
}

/* End of code generation (processedout.cpp) */
