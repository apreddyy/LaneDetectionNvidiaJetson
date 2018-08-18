#include "rt_nonfinite.h"
#include "processedout.h"
#include "ImageTestFunction.h"
#include "processedout_emxutil.h"
#include "polyfit.h"
#include "mean.h"
#include "sum.h"

static emxArray_real_T *Leftxout;
static bool Leftxout_not_empty;
static emxArray_real_T *Leftyout;
static bool Leftyout_not_empty;
static emxArray_real_T *Rightxout;
static bool Rightxout_not_empty;
static emxArray_real_T *Rightyout;
static bool Rightyout_not_empty;
void ImageTestFunction(const emxArray_uint8_T *Binaryimage, double Leftpoints[3],
  double Rightpoints[3])
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

void ImageTestFunction_free()
{
  emxFree_real_T(&Leftxout);
  emxFree_real_T(&Leftyout);
  emxFree_real_T(&Rightxout);
  emxFree_real_T(&Rightyout);
}

void ImageTestFunction_init()
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
