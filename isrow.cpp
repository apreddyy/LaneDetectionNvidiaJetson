#include "rt_nonfinite.h"
#include "processedout.h"
#include "isrow.h"

bool isrow(const emxArray_boolean_T *x)
{
  return x->size[0] == 1;
}
