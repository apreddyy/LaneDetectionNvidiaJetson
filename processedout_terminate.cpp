#include "rt_nonfinite.h"
#include "processedout.h"
#include "processedout_terminate.h"
#include "ImageTestFunction.h"
#include "processedout_data.h"

void processedout_terminate()
{
  ImageTestFunction_free();
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
}
