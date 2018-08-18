#include "rt_nonfinite.h"
#include "processedout.h"
#include "processedout_initialize.h"
#include "ImageTestFunction.h"
#include "processedout_data.h"
#define b_counter                      (37.0)

void processedout_initialize()
{
  int i0;
  static const double b_last_right[3] = { -0.0003611443651100786,
    0.41155055381245592, 458.8602605144315 };

  static const double b_last_left[3] = { -0.000692749899423815,
    0.43436010206237591, 94.668096440893862 };

  static const double b_right_fit[3] = { -0.0003611443651100786,
    0.41155055381245592, 458.8602605144315 };

  static const double b_left_fit[3] = { -0.000692749899423815,
    0.43436010206237591, 94.668096440893862 };

  rt_InitInfAndNaN(8U);
  omp_init_nest_lock(&emlrtNestLockGlobal);
  for (i0 = 0; i0 < 3; i0++) {
    last_right[i0] = b_last_right[i0];
    last_left[i0] = b_last_left[i0];
    right_fit[i0] = b_right_fit[i0];
    left_fit[i0] = b_left_fit[i0];
  }

  counter = b_counter;
  ImageTestFunction_init();
}
