#include "rt_nonfinite.h"
#include "processedout.h"
#include "xgemv.h"

void b_xgemv(int m, int n, const double A[1080], int ia0, const double x[1080],
             int ix0, double y[3])
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

void xgemv(int m, int n, const emxArray_real_T *A, int ia0, int lda, const
           emxArray_real_T *x, int ix0, double y[3])
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
