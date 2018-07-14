/*
 * LaneLogic.cpp
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "LaneLogic".
 *
 * Model version              : 1.66
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C++ source code generated on : Sat May  5 20:47:56 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: All passed
 */

#include "LaneLogic_capi.h"
#include "LaneLogic.h"
#include "LaneLogic_private.h"

/* Named constants for Chart: '<S4>/Chart2' */
#define LaneLogic_IN_LeftChangeStatus  ((uint8_T)1U)
#define LaneLogic_IN_Nochange          ((uint8_T)2U)
#define LaneLogic_IN_RightChangeStatus ((uint8_T)3U)

real_T look1_binlx(real_T u0, const real_T bp0[], const real_T table[], uint32_T
                   maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

/* Model step function */
void LaneLogicModelClass::step()
{
  real_T rtb_LLaneChangeR;
  real_T rtb_LLaneChange;

  /* Chart: '<S11>/Chart' incorporates:
   *  Constant: '<S11>/Threshold'
   *  Inport: '<Root>/Distance'
   */
  /* Gateway: Laneogicfull/Lane_system/LaneSafeZone/Chart */
  /* During: Laneogicfull/Lane_system/LaneSafeZone/Chart */
  /* Entry Internal: Laneogicfull/Lane_system/LaneSafeZone/Chart */
  /* Transition: '<S12>:19' */
  /* '<S12>:10:1' sf_internal_predicateOutput = ... */
  /* '<S12>:10:1' Distance>Threshold; */
  if (LaneLogic_U.Distance > 0.5) {
    /* Outport: '<Root>/Alert' */
    /* Transition: '<S12>:10' */
    /* Transition: '<S12>:11' */
    /* '<S12>:11:1' Alert = 1; */
    LaneLogic_Y.Alert = 1.0;

    /* Transition: '<S12>:17' */
    /* Transition: '<S12>:18' */
  } else {
    /* Transition: '<S12>:15' */
    /* '<S12>:12:1' sf_internal_predicateOutput = ... */
    /* '<S12>:12:1' Distance <(-(Threshold)); */
    if (LaneLogic_U.Distance < -0.5) {
      /* Outport: '<Root>/Alert' */
      /* Transition: '<S12>:12' */
      /* Transition: '<S12>:14' */
      /* '<S12>:14:1' Alert = 2; */
      LaneLogic_Y.Alert = 2.0;

      /* Transition: '<S12>:18' */
    } else {
      /* Outport: '<Root>/Alert' */
      /* Transition: '<S12>:16' */
      /* '<S12>:16:1' Alert = 3; */
      LaneLogic_Y.Alert = 3.0;
    }
  }

  /* End of Chart: '<S11>/Chart' */

  /* Outport: '<Root>/CenterCurvature' incorporates:
   *  Constant: '<S10>/Constant'
   *  Inport: '<Root>/LeftCurvature'
   *  Inport: '<Root>/RightCurvature'
   *  Product: '<S10>/Divide'
   *  Sum: '<S10>/Sum'
   */
  LaneLogic_Y.CenterCurvature = (LaneLogic_U.LeftCurvature +
    LaneLogic_U.RightCurvature) / 2.0;

  /* Chart: '<S4>/Chart1' incorporates:
   *  Inport: '<Root>/LChangeRequest'
   *  Inport: '<Root>/LadirRB'
   *  Inport: '<Root>/LadirRF'
   *  Inport: '<Root>/RaderRB'
   *  Inport: '<Root>/RaderRF'
   */
  /* Gateway: Laneogicfull/Subsystem/Chart1 */
  /* During: Laneogicfull/Subsystem/Chart1 */
  /* Entry Internal: Laneogicfull/Subsystem/Chart1 */
  /* Transition: '<S14>:13' */
  /* '<S14>:3:1' sf_internal_predicateOutput = ... */
  /* '<S14>:3:1'  ((Lcange == 2) && (LLFadirR  > 15)  && (LRFDistR > 15) && (LLRaiderR > 15) && (LRFRR > 15)); */
  if ((LaneLogic_U.LChangeRequest == 2) && (LaneLogic_U.LadirRB > 15.0) &&
      (LaneLogic_U.RaderRB > 15.0) && (LaneLogic_U.LadirRF > 15.0) &&
      (LaneLogic_U.RaderRF > 15.0)) {
    /* Transition: '<S14>:3' */
    /* Transition: '<S14>:8' */
    /* '<S14>:8:1' LLaneChangeR = 0; */
    rtb_LLaneChangeR = 0.0;

    /* Transition: '<S14>:12' */
    /* Transition: '<S14>:11' */
  } else {
    /* Transition: '<S14>:1' */
    /* '<S14>:15:1' sf_internal_predicateOutput = ... */
    /* '<S14>:15:1' (Lcange  == 0) || (Lcange  == 1); */
    if ((LaneLogic_U.LChangeRequest == 0) || (LaneLogic_U.LChangeRequest == 1))
    {
      /* Transition: '<S14>:15' */
      /* Transition: '<S14>:2' */
      /* '<S14>:2:1' LLaneChangeR  = 0; */
      rtb_LLaneChangeR = 0.0;

      /* Transition: '<S14>:11' */
    } else {
      /* Transition: '<S14>:10' */
      /* '<S14>:10:1' LLaneChangeR  =1; */
      rtb_LLaneChangeR = 1.0;
    }
  }

  /* End of Chart: '<S4>/Chart1' */

  /* Chart: '<S4>/Chart' incorporates:
   *  Inport: '<Root>/LChangeRequest'
   *  Inport: '<Root>/LadirLB'
   *  Inport: '<Root>/LadirLF'
   *  Inport: '<Root>/RaderLB'
   *  Inport: '<Root>/RaderLF'
   */
  /* Gateway: Laneogicfull/Subsystem/Chart */
  /* During: Laneogicfull/Subsystem/Chart */
  /* Entry Internal: Laneogicfull/Subsystem/Chart */
  /* Transition: '<S13>:8' */
  /* '<S13>:9:1' sf_internal_predicateOutput = ... */
  /* '<S13>:9:1'  ((Lcange == 1) && (LLFadir  > 15)  && (LRFDist > 15) && (LLRaider > 15) && (LRFR > 15)); */
  if ((LaneLogic_U.LChangeRequest == 1) && (LaneLogic_U.LadirLF > 15.0) &&
      (LaneLogic_U.LadirLB > 15.0) && (LaneLogic_U.RaderLB > 15.0) &&
      (LaneLogic_U.RaderLF > 15.0)) {
    /* Transition: '<S13>:9' */
    /* Transition: '<S13>:10' */
    /* '<S13>:10:1' LLaneChange = 0; */
    rtb_LLaneChange = 0.0;

    /* Transition: '<S13>:16' */
    /* Transition: '<S13>:17' */
  } else {
    /* Transition: '<S13>:11' */
    /* '<S13>:13:1' sf_internal_predicateOutput = ... */
    /* '<S13>:13:1' (Lcange  == 0) || (Lcange  == 2); */
    if ((LaneLogic_U.LChangeRequest == 0) || (LaneLogic_U.LChangeRequest == 2))
    {
      /* Transition: '<S13>:13' */
      /* Transition: '<S13>:15' */
      /* '<S13>:15:1' LLaneChange  = 0; */
      rtb_LLaneChange = 0.0;

      /* Transition: '<S13>:17' */
    } else {
      /* Transition: '<S13>:12' */
      /* '<S13>:12:1' LLaneChange  = 1; */
      rtb_LLaneChange = 1.0;
    }
  }

  /* End of Chart: '<S4>/Chart' */

  /* Chart: '<S4>/Chart2' */
  /* Gateway: Laneogicfull/Subsystem/Chart2 */
  /* During: Laneogicfull/Subsystem/Chart2 */
  if (LaneLogic_DW.is_active_c9_LaneLogic == 0U) {
    /* Entry: Laneogicfull/Subsystem/Chart2 */
    LaneLogic_DW.is_active_c9_LaneLogic = 1U;

    /* Entry Internal: Laneogicfull/Subsystem/Chart2 */
    /* Transition: '<S15>:2' */
    LaneLogic_DW.is_c9_LaneLogic = LaneLogic_IN_Nochange;

    /* Outport: '<Root>/ChangeLaneout' */
    /* Entry 'Nochange': '<S15>:1' */
    /* '<S15>:1:1' Change = 0; */
    LaneLogic_Y.ChangeLaneout = 0.0;
  } else {
    switch (LaneLogic_DW.is_c9_LaneLogic) {
     case LaneLogic_IN_LeftChangeStatus:
      /* Outport: '<Root>/ChangeLaneout' */
      LaneLogic_Y.ChangeLaneout = 1.0;

      /* During 'LeftChangeStatus': '<S15>:3' */
      /* '<S15>:6:1' sf_internal_predicateOutput = ... */
      /* '<S15>:6:1' RightChange == 1; */
      if (rtb_LLaneChangeR == 1.0) {
        /* Transition: '<S15>:6' */
        LaneLogic_DW.is_c9_LaneLogic = LaneLogic_IN_RightChangeStatus;

        /* Outport: '<Root>/ChangeLaneout' */
        /* Entry 'RightChangeStatus': '<S15>:5' */
        /* '<S15>:5:1' Change = 2; */
        LaneLogic_Y.ChangeLaneout = 2.0;
      }
      break;

     case LaneLogic_IN_Nochange:
      /* Outport: '<Root>/ChangeLaneout' */
      LaneLogic_Y.ChangeLaneout = 0.0;

      /* During 'Nochange': '<S15>:1' */
      /* '<S15>:4:1' sf_internal_predicateOutput = ... */
      /* '<S15>:4:1' LeftChange == 1; */
      if (rtb_LLaneChange == 1.0) {
        /* Transition: '<S15>:4' */
        LaneLogic_DW.is_c9_LaneLogic = LaneLogic_IN_LeftChangeStatus;

        /* Outport: '<Root>/ChangeLaneout' */
        /* Entry 'LeftChangeStatus': '<S15>:3' */
        /* '<S15>:3:1' Change = 1; */
        LaneLogic_Y.ChangeLaneout = 1.0;
      }
      break;

     default:
      /* Outport: '<Root>/ChangeLaneout' */
      LaneLogic_Y.ChangeLaneout = 2.0;

      /* During 'RightChangeStatus': '<S15>:5' */
      /* '<S15>:7:1' sf_internal_predicateOutput = ... */
      /* '<S15>:7:1' ((LeftChange && RightChange)  == 0); */
      if (!((rtb_LLaneChange != 0.0) && (rtb_LLaneChangeR != 0.0))) {
        /* Transition: '<S15>:7' */
        LaneLogic_DW.is_c9_LaneLogic = LaneLogic_IN_Nochange;

        /* Outport: '<Root>/ChangeLaneout' */
        /* Entry 'Nochange': '<S15>:1' */
        /* '<S15>:1:1' Change = 0; */
        LaneLogic_Y.ChangeLaneout = 0.0;
      }
      break;
    }
  }

  /* End of Chart: '<S4>/Chart2' */

  /* Lookup_n-D: '<S2>/1-D Lookup Table' incorporates:
   *  Inport: '<Root>/Veh_speed'
   */
  rtb_LLaneChangeR = look1_binlx(LaneLogic_U.Veh_speed, LaneLogic_ConstP.pooled3,
    LaneLogic_ConstP.pooled2, 50U);

  /* Product: '<S2>/Divide' incorporates:
   *  Constant: '<S2>/Constant'
   *  Inport: '<Root>/FImage_Dist'
   *  Inport: '<Root>/RFF_distance'
   *  Sum: '<S2>/Add'
   */
  rtb_LLaneChange = (LaneLogic_U.RFF_distance + LaneLogic_U.FImage_Dist) / 2.0;

  /* Chart: '<S2>/Chart' incorporates:
   *  Inport: '<Root>/Veh_speed'
   *  Lookup_n-D: '<S2>/1-D Lookup Table1'
   */
  /* Gateway: Laneogicfull/F_Lane/Chart */
  /* During: Laneogicfull/F_Lane/Chart */
  /* Entry Internal: Laneogicfull/F_Lane/Chart */
  /* Transition: '<S5>:6' */
  /* '<S5>:4:1' sf_internal_predicateOutput = ... */
  /* '<S5>:4:1' Req_dist >= Pre_distance; */
  if (rtb_LLaneChangeR >= rtb_LLaneChange) {
    /* Transition: '<S5>:4' */
    /* Transition: '<S5>:9' */
    /* '<S5>:9:1' Req_speedout = Speed_in; */
    LaneLogic_B.Req_speedout = LaneLogic_U.Veh_speed;

    /* Transition: '<S5>:16' */
    /* Transition: '<S5>:12' */
  } else {
    /* Transition: '<S5>:14' */
    /* '<S5>:15:1' sf_internal_predicateOutput = ... */
    /* '<S5>:15:1' Req_dist < Pre_distance; */
    if (rtb_LLaneChangeR < rtb_LLaneChange) {
      /* Transition: '<S5>:15' */
      /* Transition: '<S5>:13' */
      /* '<S5>:13:1' Req_speedout = Speedin_req; */
      LaneLogic_B.Req_speedout = look1_binlx(rtb_LLaneChangeR,
        LaneLogic_ConstP.pooled2, LaneLogic_ConstP.pooled3, 50U);

      /* Transition: '<S5>:12' */
    } else {
      /* Transition: '<S5>:7' */
      /* '<S5>:7:1' Req_speedout == 0; */
    }
  }

  /* End of Chart: '<S2>/Chart' */

  /* Outport: '<Root>/BrakePercentage' incorporates:
   *  Chart: '<S2>/Chart3'
   *  Chart: '<S2>/Chart4'
   */
  /* Gateway: Laneogicfull/F_Lane/Chart1 */
  /* During: Laneogicfull/F_Lane/Chart1 */
  /* Entry Internal: Laneogicfull/F_Lane/Chart1 */
  /* Transition: '<S6>:20' */
  /* '<S6>:9:1' sf_internal_predicateOutput = ... */
  /* '<S6>:9:1' (Req_speed -  Speedin) >4; */
  /* Transition: '<S6>:13' */
  /* Gateway: Laneogicfull/F_Lane/Chart2 */
  /* During: Laneogicfull/F_Lane/Chart2 */
  /* Entry Internal: Laneogicfull/F_Lane/Chart2 */
  /* Transition: '<S7>:8' */
  /* '<S7>:9:1' sf_internal_predicateOutput = ... */
  /* '<S7>:9:1' Brake ~= 0; */
  /* Gateway: Laneogicfull/F_Lane/Chart3 */
  /* During: Laneogicfull/F_Lane/Chart3 */
  /* Entry Internal: Laneogicfull/F_Lane/Chart3 */
  /* Transition: '<S8>:10' */
  /* '<S8>:11:1' sf_internal_predicateOutput = ... */
  /* '<S8>:11:1' (6 <=Ladir <= 10); */
  /* Transition: '<S8>:11' */
  /* Transition: '<S8>:12' */
  /* '<S8>:12:1' Brake_outoverite = 70; */
  /* Transition: '<S8>:5' */
  /* Transition: '<S8>:13' */
  /* Gateway: Laneogicfull/F_Lane/Chart4 */
  /* During: Laneogicfull/F_Lane/Chart4 */
  /* Entry Internal: Laneogicfull/F_Lane/Chart4 */
  /* Transition: '<S9>:10' */
  /* '<S9>:11:1' sf_internal_predicateOutput = ... */
  /* '<S9>:11:1' (BrekoutOverite ~= 0); */
  /* Transition: '<S9>:11' */
  /* Transition: '<S9>:2' */
  /* '<S9>:2:1' Brake_Total =  BrekoutOverite; */
  LaneLogic_Y.BrakePercentage = 70;

  /* Transition: '<S9>:15' */
  /* Transition: '<S9>:13' */
}

/* Model initialize function */
void LaneLogicModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&LaneLogic_M), 0,
                sizeof(RT_MODEL_LaneLogic_T));

  /* block I/O */
  (void) memset(((void *) &LaneLogic_B), 0,
                sizeof(B_LaneLogic_T));

  /* states (dwork) */
  (void) memset((void *)&LaneLogic_DW, 0,
                sizeof(DW_LaneLogic_T));

  /* external inputs */
  (void)memset((void *)&LaneLogic_U, 0, sizeof(ExtU_LaneLogic_T));

  /* external outputs */
  (void) memset((void *)&LaneLogic_Y, 0,
                sizeof(ExtY_LaneLogic_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  LaneLogic_InitializeDataMapInfo((&LaneLogic_M), &LaneLogic_B);

  /* SystemInitialize for Chart: '<S4>/Chart2' */
  LaneLogic_DW.is_active_c9_LaneLogic = 0U;
  LaneLogic_DW.is_c9_LaneLogic = 0;
}

/* Model terminate function */
void LaneLogicModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
LaneLogicModelClass::LaneLogicModelClass()
{
}

/* Destructor */
LaneLogicModelClass::~LaneLogicModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_LaneLogic_T * LaneLogicModelClass::getRTM()
{
  return (&LaneLogic_M);
}
