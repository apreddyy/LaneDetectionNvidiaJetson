#include <cmath>
#include <float.h>
#include "rt_nonfinite.h"
#include <string.h>
#include "processedout.h"
#include "morphopAlgo.h"
#include "isrow.h"
#include "processedout_emxutil.h"

typedef struct {
  bool Neighborhood[9];
  int ImageSize[2];
  double InteriorStart[2];
  int InteriorEnd[2];
  int ImageNeighborLinearOffsets[5];
  double Padding;
  double PadValue;
  bool ProcessBorder;
  double NeighborhoodCenter;
  int NeighborLinearIndices[5];
  int NeighborSubscriptOffsets[10];
} c_images_internal_coder_Neighbo;

static int div_s32(int numerator, int denominator);
static double rt_remd_snf(double u0, double u1);
static int div_s32(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  bool quotientNeedsNegation;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    absNumerator /= absDenominator;
    if (quotientNeedsNegation) {
      quotient = -(int)absNumerator;
    } else {
      quotient = (int)absNumerator;
    }
  }

  return quotient;
}

static double rt_remd_snf(double u0, double u1)
{
  double y;
  double b_u1;
  double q;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    y = rtNaN;
  } else {
    if (u1 < 0.0) {
      b_u1 = std::ceil(u1);
    } else {
      b_u1 = std::floor(u1);
    }

    if ((u1 != 0.0) && (u1 != b_u1)) {
      q = std::abs(u0 / u1);
      if (std::abs(q - std::floor(q + 0.5)) <= DBL_EPSILON * q) {
        y = 0.0 * u0;
      } else {
        y = std::fmod(u0, u1);
      }
    } else {
      y = std::fmod(u0, u1);
    }
  }

  return y;
}

void morphopAlgo(const emxArray_boolean_T *A, emxArray_boolean_T *B)
{
  int centerPixelSub_idx_0;
  c_images_internal_coder_Neighbo np;
  static const bool nhConn[9] = { false, true, false, true, true, true, false,
    true, false };

  int imSize[2];
  int i;
  bool b_nhConn[9];
  int nhInds[5];
  int imageNeighborLinearOffsets[5];
  int pixelsPerImPage[2];
  int imnhSubs[10];
  double centerLocationInImage;
  int indx;
  int pind;
  int r;
  int firstIndRange[2];
  signed char subs[2];
  signed char b_subs[2];
  int a[10];
  emxArray_boolean_T *in;
  c_images_internal_coder_Neighbo *nhoodObj;
  int centerPixelSub_idx_1;
  int secondInd;
  bool imnh_data[25];
  signed char imnh_size[2];
  double centerPixelSub[2];
  bool padValue;
  int varargin_2;
  int imnhInds[5];
  int b_pind;
  int b_varargin_2;
  bool out__data[360];
  int minval;
  int loop_ub;
  int firstInd;
  int b_secondInd;
  int b_i;
  int b_firstInd;
  int varargin_1_size_idx_0;
  signed char varargin_1_data[26];
  int pixelSub[2];
  bool isInside[5];
  int trueCount;
  bool p;
  bool exitg1;
  int imnhInds_data[5];
  int tmp_data[5];
  int b_pixelSub[2];
  bool b_imnh_data[25];
  int k[2];
  signed char b_varargin_1_data[26];
  int b_trueCount;
  int b_tmp_data[5];
  int b_imnhInds_data[5];
  int c_pixelSub[2];
  int c_trueCount;
  int c_imnhInds_data[5];
  int c_tmp_data[5];
  int d_pixelSub[2];
  int d_tmp_data[5];
  int d_trueCount;
  int d_imnhInds_data[5];
  int e_tmp_data[5];
  if (!((A->size[0] == 0) || (A->size[1] == 0))) {
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      np.ImageSize[centerPixelSub_idx_0] = A->size[centerPixelSub_idx_0];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 9;
         centerPixelSub_idx_0++) {
      np.Neighborhood[centerPixelSub_idx_0] = nhConn[centerPixelSub_idx_0];
    }

    np.Padding = 1.0;
    np.ProcessBorder = true;
    np.NeighborhoodCenter = 1.0;
    np.PadValue = 0.0;
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      imSize[centerPixelSub_idx_0] = np.ImageSize[centerPixelSub_idx_0];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 9;
         centerPixelSub_idx_0++) {
      b_nhConn[centerPixelSub_idx_0] = np.Neighborhood[centerPixelSub_idx_0];
    }

    for (i = 0; i < 5; i++) {
      nhInds[i] = np.ImageNeighborLinearOffsets[i];
    }

    for (i = 0; i < 5; i++) {
      imageNeighborLinearOffsets[i] = np.NeighborLinearIndices[i];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
         centerPixelSub_idx_0++) {
      imnhSubs[centerPixelSub_idx_0] =
        np.NeighborSubscriptOffsets[centerPixelSub_idx_0];
    }

    pixelsPerImPage[0] = 1;
    pixelsPerImPage[1] = imSize[0];
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      imSize[centerPixelSub_idx_0]--;
    }

    centerLocationInImage = b_nhConn[0];
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 8;
         centerPixelSub_idx_0++) {
      centerLocationInImage += (double)b_nhConn[centerPixelSub_idx_0 + 1];
    }

    if (!(centerLocationInImage == 0.0)) {
      indx = 0;
      for (pind = 0; pind < 9; pind++) {
        if (b_nhConn[pind]) {
          r = (int)rt_remd_snf((1.0 + (double)pind) - 1.0, 3.0) + 1;
          subs[1] = (signed char)((int)(((double)(pind - r) + 1.0) / 3.0) + 1);
          subs[0] = (signed char)r;
          b_subs[0] = (signed char)r;
          b_subs[1] = (signed char)(subs[1] - 1);
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imnhSubs[indx + 5 * centerPixelSub_idx_0] =
              subs[centerPixelSub_idx_0];
            firstIndRange[centerPixelSub_idx_0] = b_subs[centerPixelSub_idx_0] *
              (1 + (centerPixelSub_idx_0 << 1));
          }

          imageNeighborLinearOffsets[indx] = firstIndRange[0] + firstIndRange[1];
          b_subs[0] = (signed char)r;
          b_subs[1] = (signed char)(subs[1] - 1);
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            firstIndRange[centerPixelSub_idx_0] = b_subs[centerPixelSub_idx_0] *
              pixelsPerImPage[centerPixelSub_idx_0];
          }

          nhInds[indx] = (int)((double)firstIndRange[0] + (double)firstIndRange
                               [1]);
          indx++;
        }
      }

      for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
           centerPixelSub_idx_0++) {
        firstIndRange[centerPixelSub_idx_0] = (2 - centerPixelSub_idx_0) *
          pixelsPerImPage[centerPixelSub_idx_0];
      }

      centerLocationInImage = (double)firstIndRange[0] + (double)firstIndRange[1];
      for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
           centerPixelSub_idx_0++) {
        nhInds[centerPixelSub_idx_0] -= (int)centerLocationInImage;
      }

      for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
           centerPixelSub_idx_0++) {
        a[centerPixelSub_idx_0] = imnhSubs[centerPixelSub_idx_0];
      }

      for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
           centerPixelSub_idx_0++) {
        for (indx = 0; indx < 5; indx++) {
          imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
            centerPixelSub_idx_0] - 2;
        }
      }
    }

    for (i = 0; i < 5; i++) {
      np.ImageNeighborLinearOffsets[i] = nhInds[i];
    }

    for (i = 0; i < 5; i++) {
      np.NeighborLinearIndices[i] = imageNeighborLinearOffsets[i];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
         centerPixelSub_idx_0++) {
      np.NeighborSubscriptOffsets[centerPixelSub_idx_0] =
        imnhSubs[centerPixelSub_idx_0];
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      np.InteriorStart[centerPixelSub_idx_0] = 2.0;
    }

    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
         centerPixelSub_idx_0++) {
      np.InteriorEnd[centerPixelSub_idx_0] = imSize[centerPixelSub_idx_0];
    }

    emxInit_boolean_T(&in, 2);
    nhoodObj = &np;
    centerPixelSub_idx_0 = in->size[0] * in->size[1];
    in->size[0] = A->size[0];
    in->size[1] = A->size[1];
    emxEnsureCapacity_boolean_T(in, centerPixelSub_idx_0);
    indx = A->size[0] * A->size[1];
    for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
         centerPixelSub_idx_0++) {
      in->data[centerPixelSub_idx_0] = A->data[centerPixelSub_idx_0];
    }

    centerPixelSub_idx_0 = (int)np.InteriorStart[1];
    centerPixelSub_idx_1 = np.InteriorEnd[1];
    firstIndRange[0] = (int)np.InteriorStart[0];
    firstIndRange[1] = np.InteriorEnd[0];
    for (i = 0; i < 5; i++) {
      imageNeighborLinearOffsets[i] = np.ImageNeighborLinearOffsets[i];
    }

    indx = np.ImageSize[0];

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(imnh_data,imnh_size,imnhInds,b_pind,out__data,loop_ub,firstInd,b_i,varargin_1_size_idx_0) \
 firstprivate(varargin_1_data)

    for (secondInd = centerPixelSub_idx_0; secondInd <= centerPixelSub_idx_1;
         secondInd++) {
      loop_ub = B->size[0];
      for (firstInd = firstIndRange[0]; firstInd <= firstIndRange[1]; firstInd++)
      {
        b_pind = (secondInd - 1) * indx + firstInd;
        for (b_i = 0; b_i < 5; b_i++) {
          imnhInds[b_i] = imageNeighborLinearOffsets[b_i] + b_pind;
        }

        if (isrow(in)) {
          imnh_size[0] = 1;
          imnh_size[1] = 5;
          for (b_pind = 0; b_pind < 5; b_pind++) {
            imnh_data[b_pind] = in->data[imnhInds[b_pind] - 1];
          }
        } else {
          imnh_size[0] = 5;
          imnh_size[1] = 1;
          for (b_pind = 0; b_pind < 5; b_pind++) {
            imnh_data[b_pind] = in->data[imnhInds[b_pind] - 1];
          }
        }

        varargin_1_size_idx_0 = imnh_size[0] * imnh_size[1] + 1;
        b_i = imnh_size[0] * imnh_size[1];
        for (b_pind = 0; b_pind < b_i; b_pind++) {
          varargin_1_data[b_pind] = (signed char)imnh_data[b_pind];
        }

        varargin_1_data[imnh_size[0] * imnh_size[1]] = 0;
        if (varargin_1_size_idx_0 <= 2) {
          if (varargin_1_data[0] < varargin_1_data[1]) {
            b_pind = varargin_1_data[1];
          } else {
            b_pind = varargin_1_data[0];
          }
        } else {
          b_pind = varargin_1_data[0];
          for (b_i = 1; b_i < varargin_1_size_idx_0; b_i++) {
            if (b_pind < varargin_1_data[b_i]) {
              b_pind = varargin_1_data[b_i];
            }
          }
        }

        out__data[firstInd - 1] = (b_pind != 0);
      }

      for (b_pind = 0; b_pind < loop_ub; b_pind++) {
        B->data[b_pind + B->size[0] * (secondInd - 1)] = out__data[b_pind];
      }
    }

    if (nhoodObj->ProcessBorder) {
      firstIndRange[1] = nhoodObj->ImageSize[0];
      centerPixelSub[1] = nhoodObj->InteriorStart[1] - 1.0;
      padValue = (nhoodObj->PadValue != 0.0);
      varargin_2 = nhoodObj->ImageSize[0];
      indx = firstIndRange[1];
      if (indx < varargin_2) {
        varargin_2 = indx;
      }

      b_varargin_2 = nhoodObj->ImageSize[1];
      if (rtIsNaN(centerPixelSub[1]) || (centerPixelSub[1] > b_varargin_2)) {
        minval = b_varargin_2;
      } else {
        minval = (int)centerPixelSub[1];
      }

      for (b_secondInd = 0; b_secondInd < minval; b_secondInd++) {
        if (1 <= varargin_2) {
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
               centerPixelSub_idx_0++) {
            a[centerPixelSub_idx_0] = nhoodObj->
              NeighborSubscriptOffsets[centerPixelSub_idx_0];
          }
        }

        for (b_firstInd = 1; b_firstInd <= varargin_2; b_firstInd++) {
          indx = nhoodObj->ImageSize[0];
          pind = b_secondInd * indx + b_firstInd;
          for (i = 0; i < 5; i++) {
            nhInds[i] = nhoodObj->ImageNeighborLinearOffsets[i];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
               centerPixelSub_idx_0++) {
            nhInds[centerPixelSub_idx_0] += pind;
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imSize[centerPixelSub_idx_0] = nhoodObj->
              ImageSize[centerPixelSub_idx_0];
          }

          if (imSize[0] == 0) {
            r = 1;
          } else {
            r = pind - imSize[0] * div_s32(pind - 1, imSize[0]);
          }

          centerPixelSub_idx_0 = pind - r;
          if (imSize[0] == 0) {
            if (centerPixelSub_idx_0 == 0) {
              centerPixelSub_idx_1 = 0;
            } else if (centerPixelSub_idx_0 < 0) {
              centerPixelSub_idx_1 = MIN_int32_T;
            } else {
              centerPixelSub_idx_1 = MAX_int32_T;
            }
          } else if (imSize[0] == 1) {
            centerPixelSub_idx_1 = centerPixelSub_idx_0;
          } else if (imSize[0] == -1) {
            centerPixelSub_idx_1 = -centerPixelSub_idx_0;
          } else {
            if (centerPixelSub_idx_0 >= 0) {
              indx = centerPixelSub_idx_0;
            } else if (centerPixelSub_idx_0 == MIN_int32_T) {
              indx = MAX_int32_T;
            } else {
              indx = -centerPixelSub_idx_0;
            }

            if (imSize[0] >= 0) {
              i = imSize[0];
            } else if (imSize[0] == MIN_int32_T) {
              i = MAX_int32_T;
            } else {
              i = -imSize[0];
            }

            centerPixelSub_idx_1 = div_s32(indx, i);
            indx -= centerPixelSub_idx_1 * i;
            if ((indx > 0) && (indx >= (i >> 1) + (i & 1))) {
              centerPixelSub_idx_1++;
            }

            if ((centerPixelSub_idx_0 < 0) != (imSize[0] < 0)) {
              centerPixelSub_idx_1 = -centerPixelSub_idx_1;
            }
          }

          pixelSub[1] = centerPixelSub_idx_1 + 1;
          pixelSub[0] = r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            pixelsPerImPage[centerPixelSub_idx_0] =
              pixelSub[centerPixelSub_idx_0];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            for (indx = 0; indx < 5; indx++) {
              imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
                centerPixelSub_idx_0] + pixelsPerImPage[centerPixelSub_idx_0];
            }
          }

          for (i = 0; i < 5; i++) {
            isInside[i] = true;
          }

          switch ((int)nhoodObj->Padding) {
           case 1:
            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }

            trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                imnhInds_data[centerPixelSub_idx_0] = nhInds[i];
                centerPixelSub_idx_0++;
              }
            }
            break;

           case 2:
            trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              imnhInds_data[centerPixelSub_idx_0] = nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  imnhInds_data[centerPixelSub_idx_1] = 1;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }
            break;

           case 3:
            trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              imnhInds_data[centerPixelSub_idx_0] = nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = 1;
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = nhoodObj->ImageSize[centerPixelSub_idx_0];
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;

           case 4:
            trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              imnhInds_data[centerPixelSub_idx_0] = nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = pixelsPerImPage[centerPixelSub_idx_0] + (indx << 1);
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = ((indx << 1) - i) + 1;
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;
          }

          p = (in->size[0] == 1);
          if (p) {
            if (0 <= trueCount - 1) {
              memcpy(&tmp_data[0], &imnhInds_data[0], (unsigned int)(trueCount *
                      (int)sizeof(int)));
            }

            centerPixelSub_idx_1 = 1;
            r = trueCount;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[tmp_data[centerPixelSub_idx_0] - 1];
            }
          } else {
            centerPixelSub_idx_1 = trueCount;
            r = 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[imnhInds_data[centerPixelSub_idx_0] - 1];
            }
          }

          if (nhoodObj->Padding == 2.0) {
            indx = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                indx++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                b_tmp_data[centerPixelSub_idx_0] = i + 1;
                centerPixelSub_idx_0++;
              }
            }

            indx--;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 <= indx;
                 centerPixelSub_idx_0++) {
              b_imnh_data[b_tmp_data[centerPixelSub_idx_0] - 1] = padValue;
            }
          }

          i = centerPixelSub_idx_1 * r + 1;
          indx = centerPixelSub_idx_1 * r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
               centerPixelSub_idx_0++) {
            b_varargin_1_data[centerPixelSub_idx_0] = (signed char)
              b_imnh_data[centerPixelSub_idx_0];
          }

          b_varargin_1_data[centerPixelSub_idx_1 * r] = 0;
          if (i <= 2) {
            if (i == 1) {
              indx = b_varargin_1_data[0];
            } else if (b_varargin_1_data[0] < b_varargin_1_data[1]) {
              indx = b_varargin_1_data[1];
            } else {
              indx = b_varargin_1_data[0];
            }
          } else {
            indx = b_varargin_1_data[0];
            for (centerPixelSub_idx_0 = 1; centerPixelSub_idx_0 < i;
                 centerPixelSub_idx_0++) {
              if (indx < b_varargin_1_data[centerPixelSub_idx_0]) {
                indx = b_varargin_1_data[centerPixelSub_idx_0];
              }
            }
          }

          B->data[pind - 1] = (indx != 0);
        }
      }

      firstIndRange[1] = nhoodObj->ImageSize[0];
      centerPixelSub_idx_0 = nhoodObj->InteriorEnd[1] + 1;
      centerPixelSub_idx_1 = nhoodObj->ImageSize[1];
      padValue = (nhoodObj->PadValue != 0.0);
      varargin_2 = nhoodObj->ImageSize[0];
      indx = firstIndRange[1];
      if (indx < varargin_2) {
        varargin_2 = indx;
      }

      b_varargin_2 = nhoodObj->ImageSize[1];
      if (centerPixelSub_idx_1 < b_varargin_2) {
        b_varargin_2 = centerPixelSub_idx_1;
      }

      if (centerPixelSub_idx_0 < 1) {
        b_secondInd = 1;
      } else {
        b_secondInd = centerPixelSub_idx_0;
      }

      while (b_secondInd <= b_varargin_2) {
        if (1 <= varargin_2) {
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
               centerPixelSub_idx_0++) {
            a[centerPixelSub_idx_0] = nhoodObj->
              NeighborSubscriptOffsets[centerPixelSub_idx_0];
          }
        }

        for (b_firstInd = 1; b_firstInd <= varargin_2; b_firstInd++) {
          indx = nhoodObj->ImageSize[0];
          pind = (b_secondInd - 1) * indx + b_firstInd;
          for (i = 0; i < 5; i++) {
            nhInds[i] = nhoodObj->ImageNeighborLinearOffsets[i];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
               centerPixelSub_idx_0++) {
            nhInds[centerPixelSub_idx_0] += pind;
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imSize[centerPixelSub_idx_0] = nhoodObj->
              ImageSize[centerPixelSub_idx_0];
          }

          if (imSize[0] == 0) {
            r = 1;
          } else {
            r = pind - imSize[0] * div_s32(pind - 1, imSize[0]);
          }

          centerPixelSub_idx_0 = pind - r;
          if (imSize[0] == 0) {
            if (centerPixelSub_idx_0 == 0) {
              centerPixelSub_idx_1 = 0;
            } else if (centerPixelSub_idx_0 < 0) {
              centerPixelSub_idx_1 = MIN_int32_T;
            } else {
              centerPixelSub_idx_1 = MAX_int32_T;
            }
          } else if (imSize[0] == 1) {
            centerPixelSub_idx_1 = centerPixelSub_idx_0;
          } else if (imSize[0] == -1) {
            centerPixelSub_idx_1 = -centerPixelSub_idx_0;
          } else {
            if (centerPixelSub_idx_0 >= 0) {
              indx = centerPixelSub_idx_0;
            } else if (centerPixelSub_idx_0 == MIN_int32_T) {
              indx = MAX_int32_T;
            } else {
              indx = -centerPixelSub_idx_0;
            }

            if (imSize[0] >= 0) {
              i = imSize[0];
            } else if (imSize[0] == MIN_int32_T) {
              i = MAX_int32_T;
            } else {
              i = -imSize[0];
            }

            centerPixelSub_idx_1 = div_s32(indx, i);
            indx -= centerPixelSub_idx_1 * i;
            if ((indx > 0) && (indx >= (i >> 1) + (i & 1))) {
              centerPixelSub_idx_1++;
            }

            if ((centerPixelSub_idx_0 < 0) != (imSize[0] < 0)) {
              centerPixelSub_idx_1 = -centerPixelSub_idx_1;
            }
          }

          b_pixelSub[1] = centerPixelSub_idx_1 + 1;
          b_pixelSub[0] = r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            pixelsPerImPage[centerPixelSub_idx_0] =
              b_pixelSub[centerPixelSub_idx_0];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            for (indx = 0; indx < 5; indx++) {
              imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
                centerPixelSub_idx_0] + pixelsPerImPage[centerPixelSub_idx_0];
            }
          }

          for (i = 0; i < 5; i++) {
            isInside[i] = true;
          }

          switch ((int)nhoodObj->Padding) {
           case 1:
            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }

            b_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                b_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                b_imnhInds_data[centerPixelSub_idx_0] = nhInds[i];
                centerPixelSub_idx_0++;
              }
            }
            break;

           case 2:
            b_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              b_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  b_imnhInds_data[centerPixelSub_idx_1] = 1;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }
            break;

           case 3:
            b_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              b_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = 1;
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = nhoodObj->ImageSize[centerPixelSub_idx_0];
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                b_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;

           case 4:
            b_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              b_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = pixelsPerImPage[centerPixelSub_idx_0] + (indx << 1);
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = ((indx << 1) - i) + 1;
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                b_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;
          }

          p = (in->size[0] == 1);
          if (p) {
            if (0 <= b_trueCount - 1) {
              memcpy(&tmp_data[0], &b_imnhInds_data[0], (unsigned int)
                     (b_trueCount * (int)sizeof(int)));
            }

            centerPixelSub_idx_1 = 1;
            r = b_trueCount;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < b_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[tmp_data[centerPixelSub_idx_0] - 1];
            }
          } else {
            centerPixelSub_idx_1 = b_trueCount;
            r = 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < b_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[b_imnhInds_data[centerPixelSub_idx_0] - 1];
            }
          }

          if (nhoodObj->Padding == 2.0) {
            trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                c_tmp_data[centerPixelSub_idx_0] = i + 1;
                centerPixelSub_idx_0++;
              }
            }

            indx = trueCount - 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 <= indx;
                 centerPixelSub_idx_0++) {
              b_imnh_data[c_tmp_data[centerPixelSub_idx_0] - 1] = padValue;
            }
          }

          i = centerPixelSub_idx_1 * r + 1;
          indx = centerPixelSub_idx_1 * r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
               centerPixelSub_idx_0++) {
            b_varargin_1_data[centerPixelSub_idx_0] = (signed char)
              b_imnh_data[centerPixelSub_idx_0];
          }

          b_varargin_1_data[centerPixelSub_idx_1 * r] = 0;
          if (i <= 2) {
            if (i == 1) {
              indx = b_varargin_1_data[0];
            } else if (b_varargin_1_data[0] < b_varargin_1_data[1]) {
              indx = b_varargin_1_data[1];
            } else {
              indx = b_varargin_1_data[0];
            }
          } else {
            indx = b_varargin_1_data[0];
            for (centerPixelSub_idx_0 = 1; centerPixelSub_idx_0 < i;
                 centerPixelSub_idx_0++) {
              if (indx < b_varargin_1_data[centerPixelSub_idx_0]) {
                indx = b_varargin_1_data[centerPixelSub_idx_0];
              }
            }
          }

          B->data[pind - 1] = (indx != 0);
        }

        b_secondInd++;
      }

      centerPixelSub[1] = nhoodObj->InteriorStart[0] - 1.0;
      centerPixelSub_idx_1 = nhoodObj->ImageSize[1];
      padValue = (nhoodObj->PadValue != 0.0);
      varargin_2 = nhoodObj->ImageSize[0];
      if (rtIsNaN(centerPixelSub[1]) || (centerPixelSub[1] > varargin_2)) {
        minval = varargin_2;
      } else {
        minval = (int)centerPixelSub[1];
      }

      varargin_2 = nhoodObj->ImageSize[1];
      if (centerPixelSub_idx_1 < varargin_2) {
        varargin_2 = centerPixelSub_idx_1;
      }

      for (b_secondInd = 1; b_secondInd <= varargin_2; b_secondInd++) {
        if (0 <= minval - 1) {
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
               centerPixelSub_idx_0++) {
            a[centerPixelSub_idx_0] = nhoodObj->
              NeighborSubscriptOffsets[centerPixelSub_idx_0];
          }
        }

        for (b_firstInd = 0; b_firstInd < minval; b_firstInd++) {
          indx = nhoodObj->ImageSize[0];
          pind = (b_secondInd - 1) * indx + b_firstInd;
          for (i = 0; i < 5; i++) {
            nhInds[i] = nhoodObj->ImageNeighborLinearOffsets[i];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
               centerPixelSub_idx_0++) {
            nhInds[centerPixelSub_idx_0] = (nhInds[centerPixelSub_idx_0] + pind)
              + 1;
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imSize[centerPixelSub_idx_0] = nhoodObj->
              ImageSize[centerPixelSub_idx_0];
          }

          if (imSize[0] == 0) {
            r = 0;
          } else {
            r = pind - imSize[0] * div_s32(pind, imSize[0]);
          }

          centerPixelSub_idx_0 = pind - r;
          if (imSize[0] == 0) {
            if (centerPixelSub_idx_0 == 0) {
              centerPixelSub_idx_1 = 0;
            } else if (centerPixelSub_idx_0 < 0) {
              centerPixelSub_idx_1 = MIN_int32_T;
            } else {
              centerPixelSub_idx_1 = MAX_int32_T;
            }
          } else if (imSize[0] == 1) {
            centerPixelSub_idx_1 = centerPixelSub_idx_0;
          } else if (imSize[0] == -1) {
            centerPixelSub_idx_1 = -centerPixelSub_idx_0;
          } else {
            if (centerPixelSub_idx_0 >= 0) {
              indx = centerPixelSub_idx_0;
            } else if (centerPixelSub_idx_0 == MIN_int32_T) {
              indx = MAX_int32_T;
            } else {
              indx = -centerPixelSub_idx_0;
            }

            if (imSize[0] >= 0) {
              i = imSize[0];
            } else if (imSize[0] == MIN_int32_T) {
              i = MAX_int32_T;
            } else {
              i = -imSize[0];
            }

            centerPixelSub_idx_1 = div_s32(indx, i);
            indx -= centerPixelSub_idx_1 * i;
            if ((indx > 0) && (indx >= (i >> 1) + (i & 1))) {
              centerPixelSub_idx_1++;
            }

            if ((centerPixelSub_idx_0 < 0) != (imSize[0] < 0)) {
              centerPixelSub_idx_1 = -centerPixelSub_idx_1;
            }
          }

          c_pixelSub[1] = centerPixelSub_idx_1 + 1;
          c_pixelSub[0] = r + 1;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            pixelsPerImPage[centerPixelSub_idx_0] =
              c_pixelSub[centerPixelSub_idx_0];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            for (indx = 0; indx < 5; indx++) {
              imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
                centerPixelSub_idx_0] + pixelsPerImPage[centerPixelSub_idx_0];
            }
          }

          for (i = 0; i < 5; i++) {
            isInside[i] = true;
          }

          switch ((int)nhoodObj->Padding) {
           case 1:
            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }

            c_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                c_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                c_imnhInds_data[centerPixelSub_idx_0] = nhInds[i];
                centerPixelSub_idx_0++;
              }
            }
            break;

           case 2:
            c_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              c_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  c_imnhInds_data[centerPixelSub_idx_1] = 1;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }
            break;

           case 3:
            c_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              c_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = 1;
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = nhoodObj->ImageSize[centerPixelSub_idx_0];
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                c_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;

           case 4:
            c_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              c_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = pixelsPerImPage[centerPixelSub_idx_0] + (indx << 1);
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = ((indx << 1) - i) + 1;
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                c_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;
          }

          p = (in->size[0] == 1);
          if (p) {
            if (0 <= c_trueCount - 1) {
              memcpy(&tmp_data[0], &c_imnhInds_data[0], (unsigned int)
                     (c_trueCount * (int)sizeof(int)));
            }

            centerPixelSub_idx_1 = 1;
            r = c_trueCount;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < c_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[tmp_data[centerPixelSub_idx_0] - 1];
            }
          } else {
            centerPixelSub_idx_1 = c_trueCount;
            r = 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < c_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[c_imnhInds_data[centerPixelSub_idx_0] - 1];
            }
          }

          if (nhoodObj->Padding == 2.0) {
            b_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                b_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                d_tmp_data[centerPixelSub_idx_0] = i + 1;
                centerPixelSub_idx_0++;
              }
            }

            indx = b_trueCount - 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 <= indx;
                 centerPixelSub_idx_0++) {
              b_imnh_data[d_tmp_data[centerPixelSub_idx_0] - 1] = padValue;
            }
          }

          i = centerPixelSub_idx_1 * r + 1;
          indx = centerPixelSub_idx_1 * r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
               centerPixelSub_idx_0++) {
            b_varargin_1_data[centerPixelSub_idx_0] = (signed char)
              b_imnh_data[centerPixelSub_idx_0];
          }

          b_varargin_1_data[centerPixelSub_idx_1 * r] = 0;
          if (i <= 2) {
            if (i == 1) {
              indx = b_varargin_1_data[0];
            } else if (b_varargin_1_data[0] < b_varargin_1_data[1]) {
              indx = b_varargin_1_data[1];
            } else {
              indx = b_varargin_1_data[0];
            }
          } else {
            indx = b_varargin_1_data[0];
            for (centerPixelSub_idx_0 = 1; centerPixelSub_idx_0 < i;
                 centerPixelSub_idx_0++) {
              if (indx < b_varargin_1_data[centerPixelSub_idx_0]) {
                indx = b_varargin_1_data[centerPixelSub_idx_0];
              }
            }
          }

          B->data[pind] = (indx != 0);
        }
      }

      firstIndRange[0] = nhoodObj->InteriorEnd[0] + 1;
      firstIndRange[1] = nhoodObj->ImageSize[0];
      centerPixelSub_idx_1 = nhoodObj->ImageSize[1];
      padValue = (nhoodObj->PadValue != 0.0);
      if (firstIndRange[0] < 1) {
        minval = 1;
      } else {
        minval = firstIndRange[0];
      }

      if (firstIndRange[0] < 1) {
        firstIndRange[0] = 1;
      }

      varargin_2 = nhoodObj->ImageSize[0];
      indx = firstIndRange[1];
      if (indx < varargin_2) {
        varargin_2 = indx;
      }

      b_varargin_2 = nhoodObj->ImageSize[1];
      if (centerPixelSub_idx_1 < b_varargin_2) {
        b_varargin_2 = centerPixelSub_idx_1;
      }

      for (b_secondInd = 1; b_secondInd <= b_varargin_2; b_secondInd++) {
        if (firstIndRange[0] <= varargin_2) {
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 10;
               centerPixelSub_idx_0++) {
            a[centerPixelSub_idx_0] = nhoodObj->
              NeighborSubscriptOffsets[centerPixelSub_idx_0];
          }
        }

        for (b_firstInd = minval; b_firstInd <= varargin_2; b_firstInd++) {
          indx = nhoodObj->ImageSize[0];
          pind = (b_secondInd - 1) * indx + b_firstInd;
          for (i = 0; i < 5; i++) {
            nhInds[i] = nhoodObj->ImageNeighborLinearOffsets[i];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
               centerPixelSub_idx_0++) {
            nhInds[centerPixelSub_idx_0] += pind;
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            imSize[centerPixelSub_idx_0] = nhoodObj->
              ImageSize[centerPixelSub_idx_0];
          }

          if (imSize[0] == 0) {
            r = 1;
          } else {
            r = pind - imSize[0] * div_s32(pind - 1, imSize[0]);
          }

          centerPixelSub_idx_0 = pind - r;
          if (imSize[0] == 0) {
            if (centerPixelSub_idx_0 == 0) {
              centerPixelSub_idx_1 = 0;
            } else if (centerPixelSub_idx_0 < 0) {
              centerPixelSub_idx_1 = MIN_int32_T;
            } else {
              centerPixelSub_idx_1 = MAX_int32_T;
            }
          } else if (imSize[0] == 1) {
            centerPixelSub_idx_1 = centerPixelSub_idx_0;
          } else if (imSize[0] == -1) {
            centerPixelSub_idx_1 = -centerPixelSub_idx_0;
          } else {
            if (centerPixelSub_idx_0 >= 0) {
              indx = centerPixelSub_idx_0;
            } else if (centerPixelSub_idx_0 == MIN_int32_T) {
              indx = MAX_int32_T;
            } else {
              indx = -centerPixelSub_idx_0;
            }

            if (imSize[0] >= 0) {
              i = imSize[0];
            } else if (imSize[0] == MIN_int32_T) {
              i = MAX_int32_T;
            } else {
              i = -imSize[0];
            }

            centerPixelSub_idx_1 = div_s32(indx, i);
            indx -= centerPixelSub_idx_1 * i;
            if ((indx > 0) && (indx >= (i >> 1) + (i & 1))) {
              centerPixelSub_idx_1++;
            }

            if ((centerPixelSub_idx_0 < 0) != (imSize[0] < 0)) {
              centerPixelSub_idx_1 = -centerPixelSub_idx_1;
            }
          }

          d_pixelSub[1] = centerPixelSub_idx_1 + 1;
          d_pixelSub[0] = r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            pixelsPerImPage[centerPixelSub_idx_0] =
              d_pixelSub[centerPixelSub_idx_0];
          }

          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
               centerPixelSub_idx_0++) {
            for (indx = 0; indx < 5; indx++) {
              imnhSubs[indx + 5 * centerPixelSub_idx_0] = a[indx + 5 *
                centerPixelSub_idx_0] + pixelsPerImPage[centerPixelSub_idx_0];
            }
          }

          for (i = 0; i < 5; i++) {
            isInside[i] = true;
          }

          switch ((int)nhoodObj->Padding) {
           case 1:
            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }

            d_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                d_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (isInside[i]) {
                d_imnhInds_data[centerPixelSub_idx_0] = nhInds[i];
                centerPixelSub_idx_0++;
              }
            }
            break;

           case 2:
            d_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              d_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              centerPixelSub_idx_0 = 0;
              exitg1 = false;
              while ((!exitg1) && (centerPixelSub_idx_0 < 2)) {
                if ((imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0] <
                     1) || (imnhSubs[centerPixelSub_idx_1 + 5 *
                            centerPixelSub_idx_0] > nhoodObj->
                            ImageSize[centerPixelSub_idx_0])) {
                  isInside[centerPixelSub_idx_1] = false;
                  d_imnhInds_data[centerPixelSub_idx_1] = 1;
                  exitg1 = true;
                } else {
                  centerPixelSub_idx_0++;
                }
              }
            }
            break;

           case 3:
            d_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              d_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = 1;
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  i = nhoodObj->ImageSize[centerPixelSub_idx_0];
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                d_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;

           case 4:
            d_trueCount = 5;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 5;
                 centerPixelSub_idx_0++) {
              d_imnhInds_data[centerPixelSub_idx_0] =
                nhInds[centerPixelSub_idx_0];
            }

            for (centerPixelSub_idx_1 = 0; centerPixelSub_idx_1 < 5;
                 centerPixelSub_idx_1++) {
              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                pixelsPerImPage[centerPixelSub_idx_0] =
                  imnhSubs[centerPixelSub_idx_1 + 5 * centerPixelSub_idx_0];
              }

              for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                   centerPixelSub_idx_0++) {
                i = pixelsPerImPage[centerPixelSub_idx_0];
                if (pixelsPerImPage[centerPixelSub_idx_0] < 1) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = pixelsPerImPage[centerPixelSub_idx_0] + (indx << 1);
                }

                if (i > nhoodObj->ImageSize[centerPixelSub_idx_0]) {
                  isInside[centerPixelSub_idx_1] = false;
                  indx = nhoodObj->ImageSize[centerPixelSub_idx_0];
                  i = ((indx << 1) - i) + 1;
                }

                pixelsPerImPage[centerPixelSub_idx_0] = i;
              }

              if (!isInside[centerPixelSub_idx_1]) {
                for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < 2;
                     centerPixelSub_idx_0++) {
                  imSize[centerPixelSub_idx_0] = nhoodObj->
                    ImageSize[centerPixelSub_idx_0];
                }

                k[0] = 1;
                k[1] = imSize[0];
                indx = 1;
                for (i = 0; i < 2; i++) {
                  indx += (pixelsPerImPage[i] - 1) * k[i];
                }

                d_imnhInds_data[centerPixelSub_idx_1] = indx;
              }
            }
            break;
          }

          p = (in->size[0] == 1);
          if (p) {
            if (0 <= d_trueCount - 1) {
              memcpy(&tmp_data[0], &d_imnhInds_data[0], (unsigned int)
                     (d_trueCount * (int)sizeof(int)));
            }

            centerPixelSub_idx_1 = 1;
            r = d_trueCount;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < d_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[tmp_data[centerPixelSub_idx_0] - 1];
            }
          } else {
            centerPixelSub_idx_1 = d_trueCount;
            r = 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < d_trueCount;
                 centerPixelSub_idx_0++) {
              b_imnh_data[centerPixelSub_idx_0] = in->
                data[d_imnhInds_data[centerPixelSub_idx_0] - 1];
            }
          }

          if (nhoodObj->Padding == 2.0) {
            c_trueCount = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                c_trueCount++;
              }
            }

            centerPixelSub_idx_0 = 0;
            for (i = 0; i < 5; i++) {
              if (!isInside[i]) {
                e_tmp_data[centerPixelSub_idx_0] = i + 1;
                centerPixelSub_idx_0++;
              }
            }

            indx = c_trueCount - 1;
            for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 <= indx;
                 centerPixelSub_idx_0++) {
              b_imnh_data[e_tmp_data[centerPixelSub_idx_0] - 1] = padValue;
            }
          }

          i = centerPixelSub_idx_1 * r + 1;
          indx = centerPixelSub_idx_1 * r;
          for (centerPixelSub_idx_0 = 0; centerPixelSub_idx_0 < indx;
               centerPixelSub_idx_0++) {
            b_varargin_1_data[centerPixelSub_idx_0] = (signed char)
              b_imnh_data[centerPixelSub_idx_0];
          }

          b_varargin_1_data[centerPixelSub_idx_1 * r] = 0;
          if (i <= 2) {
            if (i == 1) {
              indx = b_varargin_1_data[0];
            } else if (b_varargin_1_data[0] < b_varargin_1_data[1]) {
              indx = b_varargin_1_data[1];
            } else {
              indx = b_varargin_1_data[0];
            }
          } else {
            indx = b_varargin_1_data[0];
            for (centerPixelSub_idx_0 = 1; centerPixelSub_idx_0 < i;
                 centerPixelSub_idx_0++) {
              if (indx < b_varargin_1_data[centerPixelSub_idx_0]) {
                indx = b_varargin_1_data[centerPixelSub_idx_0];
              }
            }
          }

          B->data[pind - 1] = (indx != 0);
        }
      }
    }

    emxFree_boolean_T(&in);
  }
}
