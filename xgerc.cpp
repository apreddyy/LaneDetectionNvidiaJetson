#include "rt_nonfinite.h"
#include "processedout.h"
#include "xgerc.h"

void b_xgerc(int m, int n, double alpha1, int ix0, const double y[3], double A
             [1080], int ia0)
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

void xgerc(int m, int n, double alpha1, int ix0, const double y[3],
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
