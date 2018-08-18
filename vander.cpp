#include "rt_nonfinite.h"
#include "processedout.h"
#include "vander.h"
#include "processedout_emxutil.h"

void b_vander(const double v[360], double A[1080])
{
  int k;
  for (k = 0; k < 360; k++) {
    A[720 + k] = 1.0;
    A[360 + k] = v[k];
    A[k] = v[k] * A[360 + k];
  }
}

void vander(const emxArray_real_T *v, emxArray_real_T *A)
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
