#include "rt_nonfinite.h"
#include "processedout.h"
#include "sum.h"

void sum(const emxArray_uint8_T *x, double y_data[], int y_size[2])
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
