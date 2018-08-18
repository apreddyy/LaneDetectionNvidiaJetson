#include "rt_nonfinite.h"
#include "processedout.h"
#include "power.h"
#include "processedout_emxutil.h"

void power(const emxArray_real_T *a, emxArray_real_T *y)
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
