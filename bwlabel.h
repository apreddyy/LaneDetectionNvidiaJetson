#ifndef BWLABEL_H
#define BWLABEL_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "omp.h"
#include "processedout_types.h"

extern void bwlabel(const emxArray_boolean_T *varargin_1, emxArray_real_T *L,
                    double *numComponents);

#endif
