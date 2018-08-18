#include "rt_nonfinite.h"
#include "processedout.h"
#include "bwareaopen.h"
#include "processedout_emxutil.h"
#include "bwlabel.h"

void bwareaopen(const emxArray_uint8_T *varargin_1, emxArray_boolean_T *BW2)
{
  emxArray_boolean_T *BW;
  int j;
  int numForegroundPixels;
  emxArray_int32_T *regionLengths;
  emxArray_real_T *L;
  double numComponents;
  int numPixels;
  emxArray_int32_T *beginIdx;
  int i;
  emxArray_int32_T *pixelIdxList;
  unsigned int uv0[2];
  emxInit_boolean_T(&BW, 2);
  j = BW->size[0] * BW->size[1];
  BW->size[0] = varargin_1->size[0];
  BW->size[1] = varargin_1->size[1];
  emxEnsureCapacity_boolean_T(BW, j);
  numForegroundPixels = varargin_1->size[0] * varargin_1->size[1];
  for (j = 0; j < numForegroundPixels; j++) {
    BW->data[j] = (varargin_1->data[j] != 0);
  }

  emxInit_int32_T(&regionLengths, 1);
  emxInit_real_T1(&L, 2);
  bwlabel(BW, L, &numComponents);
  numPixels = L->size[0] * L->size[1];
  j = regionLengths->size[0];
  regionLengths->size[0] = (int)numComponents;
  emxEnsureCapacity_int32_T(regionLengths, j);
  numForegroundPixels = (int)numComponents;
  for (j = 0; j < numForegroundPixels; j++) {
    regionLengths->data[j] = 0;
  }

  for (numForegroundPixels = 0; numForegroundPixels < numPixels;
       numForegroundPixels++) {
    if ((int)L->data[numForegroundPixels] > 0) {
      regionLengths->data[(int)L->data[numForegroundPixels] - 1]++;
    }
  }

  emxInit_int32_T(&beginIdx, 1);
  numPixels = L->size[0] * L->size[1];
  numForegroundPixels = 0;
  j = beginIdx->size[0];
  beginIdx->size[0] = regionLengths->size[0];
  emxEnsureCapacity_int32_T(beginIdx, j);
  for (i = 0; i < regionLengths->size[0]; i++) {
    beginIdx->data[i] = numForegroundPixels;
    numForegroundPixels += regionLengths->data[i];
  }

  emxInit_int32_T(&pixelIdxList, 1);
  j = pixelIdxList->size[0];
  pixelIdxList->size[0] = numForegroundPixels;
  emxEnsureCapacity_int32_T(pixelIdxList, j);
  for (numForegroundPixels = 0; numForegroundPixels < numPixels;
       numForegroundPixels++) {
    if ((int)L->data[numForegroundPixels] > 0) {
      beginIdx->data[(int)L->data[numForegroundPixels] - 1]++;
      pixelIdxList->data[beginIdx->data[(int)L->data[numForegroundPixels] - 1] -
        1] = numForegroundPixels + 1;
    }
  }

  emxFree_int32_T(&beginIdx);
  emxFree_real_T(&L);
  for (j = 0; j < 2; j++) {
    uv0[j] = (unsigned int)BW->size[j];
  }

  emxFree_boolean_T(&BW);
  j = BW2->size[0] * BW2->size[1];
  BW2->size[0] = (int)uv0[0];
  BW2->size[1] = (int)uv0[1];
  emxEnsureCapacity_boolean_T(BW2, j);
  numForegroundPixels = (int)uv0[0] * (int)uv0[1];
  for (j = 0; j < numForegroundPixels; j++) {
    BW2->data[j] = false;
  }

  numForegroundPixels = -1;
  for (i = 0; i < (int)numComponents; i++) {
    if (regionLengths->data[i] >= 10) {
      for (j = 1; j <= regionLengths->data[i]; j++) {
        BW2->data[pixelIdxList->data[numForegroundPixels + j] - 1] = true;
      }
    }

    numForegroundPixels += regionLengths->data[i];
  }

  emxFree_int32_T(&pixelIdxList);
  emxFree_int32_T(&regionLengths);
}
