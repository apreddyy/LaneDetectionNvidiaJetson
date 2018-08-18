#include <stdlib.h>
#include "rt_nonfinite.h"
#include "processedout.h"
#include "processedout_emxAPI.h"
#include "processedout_emxutil.h"

emxArray_uint8_T *emxCreateND_uint8_T(int b_numDimensions, int *b_size)
{
  emxArray_uint8_T *emx;
  int numEl;
  int i;
  emxInit_uint8_T(&emx, b_numDimensions);
  numEl = 1;
  for (i = 0; i < b_numDimensions; i++) {
    numEl *= b_size[i];
    emx->size[i] = b_size[i];
  }

  emx->data = (unsigned char *)calloc((unsigned int)numEl, sizeof(unsigned char));
  emx->numDimensions = b_numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

emxArray_uint8_T *emxCreateWrapperND_uint8_T(unsigned char *b_data, int
  b_numDimensions, int *b_size)
{
  emxArray_uint8_T *emx;
  int numEl;
  int i;
  emxInit_uint8_T(&emx, b_numDimensions);
  numEl = 1;
  for (i = 0; i < b_numDimensions; i++) {
    numEl *= b_size[i];
    emx->size[i] = b_size[i];
  }

  emx->data = b_data;
  emx->numDimensions = b_numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

emxArray_uint8_T *emxCreateWrapper_uint8_T(unsigned char *b_data, int rows, int
  cols)
{
  emxArray_uint8_T *emx;
  int b_size[2];
  int numEl;
  int i;
  b_size[0] = rows;
  b_size[1] = cols;
  emxInit_uint8_T(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= b_size[i];
    emx->size[i] = b_size[i];
  }

  emx->data = b_data;
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

emxArray_uint8_T *emxCreate_uint8_T(int rows, int cols)
{
  emxArray_uint8_T *emx;
  int b_size[2];
  int numEl;
  int i;
  b_size[0] = rows;
  b_size[1] = cols;
  emxInit_uint8_T(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= b_size[i];
    emx->size[i] = b_size[i];
  }

  emx->data = (unsigned char *)calloc((unsigned int)numEl, sizeof(unsigned char));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

void emxDestroyArray_uint8_T(emxArray_uint8_T *emxArray)
{
  emxFree_uint8_T(&emxArray);
}

void emxInitArray_uint8_T(emxArray_uint8_T **pEmxArray, int b_numDimensions)
{
  emxInit_uint8_T(pEmxArray, b_numDimensions);
}
