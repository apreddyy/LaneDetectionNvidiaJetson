#include <cmath>
#include "rt_nonfinite.h"
#include "processedout.h"
#include "xgeqp3.h"
#include "xnrm2.h"
#include "sqrt.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include "xswap.h"
#include "ixamax.h"

void b_xgeqp3(double A[1080], double tau[3], int jpvt[3])
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

void xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int jpvt[3])
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
