#include "rt_nonfinite.h"
#include "processedout.h"
#include "bwlabel.h"
#include "processedout_emxutil.h"

void bwlabel(const emxArray_boolean_T *varargin_1, emxArray_real_T *L, double
             *numComponents)
{
  int numRuns;
  int lastRunOnPreviousColumn;
  emxArray_int32_T *startRow;
  emxArray_int32_T *endRow;
  emxArray_int32_T *startCol;
  emxArray_int32_T *labelForEachRun;
  int k;
  int runCounter;
  int currentColumn;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int firstRunOnPreviousColumn;
  int firstRunOnThisColumn;
  emxArray_int32_T *labelsRenumbered;
  int p;
  int root_k;
  int root_p;
  numRuns = 0;
  if ((varargin_1->size[0] != 0) && (varargin_1->size[1] != 0)) {
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < varargin_1->
         size[1]; lastRunOnPreviousColumn++) {
      if (varargin_1->data[varargin_1->size[0] * lastRunOnPreviousColumn]) {
        numRuns++;
      }

      for (k = 0; k <= varargin_1->size[0] - 2; k++) {
        if (varargin_1->data[(k + varargin_1->size[0] * lastRunOnPreviousColumn)
            + 1] && (!varargin_1->data[k + varargin_1->size[0] *
                     lastRunOnPreviousColumn])) {
          numRuns++;
        }
      }
    }
  }

  emxInit_int32_T(&startRow, 1);
  emxInit_int32_T(&endRow, 1);
  emxInit_int32_T(&startCol, 1);
  emxInit_int32_T(&labelForEachRun, 1);
  if (numRuns == 0) {
    runCounter = startRow->size[0];
    startRow->size[0] = 0;
    emxEnsureCapacity_int32_T(startRow, runCounter);
    runCounter = endRow->size[0];
    endRow->size[0] = 0;
    emxEnsureCapacity_int32_T(endRow, runCounter);
    runCounter = startCol->size[0];
    startCol->size[0] = 0;
    emxEnsureCapacity_int32_T(startCol, runCounter);
    runCounter = labelForEachRun->size[0];
    labelForEachRun->size[0] = 0;
    emxEnsureCapacity_int32_T(labelForEachRun, runCounter);
    unnamed_idx_0 = (unsigned int)varargin_1->size[0];
    unnamed_idx_1 = (unsigned int)varargin_1->size[1];
    runCounter = L->size[0] * L->size[1];
    L->size[0] = (int)unnamed_idx_0;
    L->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity_real_T(L, runCounter);
    currentColumn = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (runCounter = 0; runCounter < currentColumn; runCounter++) {
      L->data[runCounter] = 0.0;
    }

    *numComponents = 0.0;
  } else {
    runCounter = startRow->size[0];
    startRow->size[0] = numRuns;
    emxEnsureCapacity_int32_T(startRow, runCounter);
    runCounter = endRow->size[0];
    endRow->size[0] = numRuns;
    emxEnsureCapacity_int32_T(endRow, runCounter);
    runCounter = startCol->size[0];
    startCol->size[0] = numRuns;
    emxEnsureCapacity_int32_T(startCol, runCounter);
    currentColumn = varargin_1->size[0];
    runCounter = 0;
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < varargin_1->
         size[1]; lastRunOnPreviousColumn++) {
      firstRunOnPreviousColumn = 1;
      while (firstRunOnPreviousColumn <= currentColumn) {
        while ((firstRunOnPreviousColumn <= currentColumn) && (!varargin_1->
                data[(firstRunOnPreviousColumn + varargin_1->size[0] *
                      lastRunOnPreviousColumn) - 1])) {
          firstRunOnPreviousColumn++;
        }

        if ((firstRunOnPreviousColumn <= currentColumn) && varargin_1->data
            [(firstRunOnPreviousColumn + varargin_1->size[0] *
              lastRunOnPreviousColumn) - 1]) {
          startCol->data[runCounter] = lastRunOnPreviousColumn + 1;
          startRow->data[runCounter] = firstRunOnPreviousColumn;
          while ((firstRunOnPreviousColumn <= currentColumn) && varargin_1->
                 data[(firstRunOnPreviousColumn + varargin_1->size[0] *
                       lastRunOnPreviousColumn) - 1]) {
            firstRunOnPreviousColumn++;
          }

          endRow->data[runCounter] = firstRunOnPreviousColumn - 1;
          runCounter++;
        }
      }
    }

    runCounter = labelForEachRun->size[0];
    labelForEachRun->size[0] = numRuns;
    emxEnsureCapacity_int32_T(labelForEachRun, runCounter);
    for (runCounter = 0; runCounter < numRuns; runCounter++) {
      labelForEachRun->data[runCounter] = 0;
    }

    k = 0;
    currentColumn = 1;
    runCounter = 1;
    firstRunOnPreviousColumn = -1;
    lastRunOnPreviousColumn = -1;
    firstRunOnThisColumn = 0;
    while (k + 1 <= numRuns) {
      if (startCol->data[k] == currentColumn + 1) {
        firstRunOnPreviousColumn = firstRunOnThisColumn + 1;
        firstRunOnThisColumn = k;
        lastRunOnPreviousColumn = k;
        currentColumn = startCol->data[k];
      } else {
        if (startCol->data[k] > currentColumn + 1) {
          firstRunOnPreviousColumn = -1;
          lastRunOnPreviousColumn = -1;
          firstRunOnThisColumn = k;
          currentColumn = startCol->data[k];
        }
      }

      if (firstRunOnPreviousColumn >= 0) {
        for (p = firstRunOnPreviousColumn - 1; p < lastRunOnPreviousColumn; p++)
        {
          if ((endRow->data[k] >= startRow->data[p] - 1) && (startRow->data[k] <=
               endRow->data[p] + 1)) {
            if (labelForEachRun->data[k] == 0) {
              labelForEachRun->data[k] = labelForEachRun->data[p];
              runCounter++;
            } else {
              if (labelForEachRun->data[k] != labelForEachRun->data[p]) {
                for (root_k = k; root_k + 1 != labelForEachRun->data[root_k];
                     root_k = labelForEachRun->data[root_k] - 1) {
                  labelForEachRun->data[root_k] = labelForEachRun->
                    data[labelForEachRun->data[root_k] - 1];
                }

                for (root_p = p; root_p + 1 != labelForEachRun->data[root_p];
                     root_p = labelForEachRun->data[root_p] - 1) {
                  labelForEachRun->data[root_p] = labelForEachRun->
                    data[labelForEachRun->data[root_p] - 1];
                }

                if (root_k + 1 != root_p + 1) {
                  if (root_p + 1 < root_k + 1) {
                    labelForEachRun->data[root_k] = root_p + 1;
                    labelForEachRun->data[k] = root_p + 1;
                  } else {
                    labelForEachRun->data[root_p] = root_k + 1;
                    labelForEachRun->data[p] = root_k + 1;
                  }
                }
              }
            }
          }
        }
      }

      if (labelForEachRun->data[k] == 0) {
        labelForEachRun->data[k] = runCounter;
        runCounter++;
      }

      k++;
    }

    emxInit_int32_T(&labelsRenumbered, 1);
    runCounter = labelsRenumbered->size[0];
    labelsRenumbered->size[0] = labelForEachRun->size[0];
    emxEnsureCapacity_int32_T(labelsRenumbered, runCounter);
    *numComponents = 0.0;
    unnamed_idx_0 = (unsigned int)varargin_1->size[0];
    unnamed_idx_1 = (unsigned int)varargin_1->size[1];
    runCounter = L->size[0] * L->size[1];
    L->size[0] = (int)unnamed_idx_0;
    L->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity_real_T(L, runCounter);
    currentColumn = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (runCounter = 0; runCounter < currentColumn; runCounter++) {
      L->data[runCounter] = 0.0;
    }

    for (k = 0; k < numRuns; k++) {
      if (labelForEachRun->data[k] == k + 1) {
        (*numComponents)++;
        labelsRenumbered->data[k] = (int)*numComponents;
      }

      labelsRenumbered->data[k] = labelsRenumbered->data[labelForEachRun->data[k]
        - 1];
      for (runCounter = startRow->data[k]; runCounter <= endRow->data[k];
           runCounter++) {
        L->data[(runCounter + L->size[0] * (startCol->data[k] - 1)) - 1] =
          labelsRenumbered->data[k];
      }
    }

    emxFree_int32_T(&labelsRenumbered);
  }

  emxFree_int32_T(&labelForEachRun);
  emxFree_int32_T(&startCol);
  emxFree_int32_T(&endRow);
  emxFree_int32_T(&startRow);
}
