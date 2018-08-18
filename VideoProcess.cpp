#include "rt_nonfinite.h"
#include "processedout.h"
#include "VideoProcess.h"
#include "processedout_emxutil.h"
#include "polyfit.h"
#include "power.h"

void VideoProcess(const emxArray_uint8_T *Binaryimage, const double left[3],
                  const double right[3], double Leftpoints[3], double
                  Rightpoints[3])
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
