#include <cmath>
#include <string.h>
#include "rt_nonfinite.h"
#include "processedout.h"
#include "qrsolve.h"
#include "xgeqp3.h"
#include "processedout_emxutil.h"

static void LSQFromQR(const emxArray_real_T *A, const double tau_data[], const
                      int jpvt[3], emxArray_real_T *B, int rankA, double Y[3]);
static int b_rankFromQR(const double A[1080]);
static int rankFromQR(const emxArray_real_T *A);
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

void b_qrsolve(const double A[1080], const double B[360], double Y[3], int
               *rankR)
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

void qrsolve(const emxArray_real_T *A, const emxArray_real_T *B, double Y[3],
             int *rankR)
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
