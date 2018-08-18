#ifndef PROCESSEDOUT_DATA_H
#define PROCESSEDOUT_DATA_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern double counter;
extern double left_fit[3];
extern double right_fit[3];
extern double last_left[3];
extern double last_right[3];
extern omp_nest_lock_t emlrtNestLockGlobal;

#endif
