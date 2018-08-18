#include "rt_nonfinite.h"
#include "processedout.h"
#include "processedout_data.h"

double counter;
double left_fit[3];
double right_fit[3];
double last_left[3];
double last_right[3];
omp_nest_lock_t emlrtNestLockGlobal;
