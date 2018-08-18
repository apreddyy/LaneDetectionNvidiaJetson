#include "rt_nonfinite.h"
#include "processedout.h"
#include "polyfit.h"
#include "qrsolve.h"
#include "vander.h"
#include "processedout_emxutil.h"

void b_polyfit(const double x[360], const double y[360], double p[3])
{
  double dv1[1080];
  int rr;
  b_vander(x, dv1);
  b_qrsolve(dv1, y, p, &rr);
}

void polyfit(const emxArray_real_T *x, const emxArray_real_T *y, double p[3])
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
