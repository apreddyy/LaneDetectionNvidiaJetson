#include "rt_nonfinite.h"
#include <cmath>
#include <limits>

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
void rt_InitInfAndNaN(size_t realSize)
{
  (void)realSize;
  rtNaN = std::numeric_limits<real_T>::quiet_NaN();
  rtNaNF = std::numeric_limits<real32_T>::quiet_NaN();
  rtInf = std::numeric_limits<real_T>::infinity();
  rtInfF = std::numeric_limits<real32_T>::infinity();
  rtMinusInf = -std::numeric_limits<real_T>::infinity();
  rtMinusInfF = -std::numeric_limits<real32_T>::infinity();
}

boolean_T rtIsInf(real_T value)
{
  return ((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

boolean_T rtIsInfF(real32_T value)
{
  return(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

boolean_T rtIsNaN(real_T value)
{
  return (value!=value)? 1U:0U;
}

boolean_T rtIsNaNF(real32_T value)
{
  return (value!=value)? 1U:0U;
}
