/*
 * LaneLogic.h
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

#ifndef RTW_HEADER_LaneLogic_h_
#define RTW_HEADER_LaneLogic_h_
#include <string.h>
#include <stddef.h>
#include "rtw_modelmap.h"
#ifndef LaneLogic_COMMON_INCLUDES_
# define LaneLogic_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* LaneLogic_COMMON_INCLUDES_ */

#include "LaneLogic_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Req_speedout;                 /* '<S2>/Chart' */
} B_LaneLogic_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c9_LaneLogic;      /* '<S4>/Chart2' */
  uint8_T is_c9_LaneLogic;             /* '<S4>/Chart2' */
} DW_LaneLogic_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [30:1:80])
   * Referenced by:
   *   '<S2>/1-D Lookup Table'
   *   '<S2>/1-D Lookup Table1'
   */
  real_T pooled2[51];

  /* Pooled Parameter (Expression: [89:7:439])
   * Referenced by:
   *   '<S2>/1-D Lookup Table'
   *   '<S2>/1-D Lookup Table1'
   */
  real_T pooled3[51];
} ConstP_LaneLogic_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Distance;                     /* '<Root>/Distance' */
  real_T LeftCurvature;                /* '<Root>/LeftCurvature' */
  real_T RightCurvature;               /* '<Root>/RightCurvature' */
  real_T Veh_speed;                    /* '<Root>/Veh_speed' */
  real_T RFF_distance;                 /* '<Root>/RFF_distance' */
  real_T FImage_Dist;                  /* '<Root>/FImage_Dist' */
  real_T FLadirDist;                   /* '<Root>/FLadirDist' */
  real_T BreakPercentage;              /* '<Root>/BreakPercentage' */
  int8_T LChangeRequest;               /* '<Root>/LChangeRequest' */
  real_T LadirLB;                      /* '<Root>/LadirLB' */
  real_T LadirLF;                      /* '<Root>/LadirLF' */
  real_T RaderLF;                      /* '<Root>/RaderLF' */
  real_T RaderLB;                      /* '<Root>/RaderLB' */
  real_T LadirRB;                      /* '<Root>/LadirRB' */
  real_T LadirRF;                      /* '<Root>/LadirRF' */
  real_T RaderRF;                      /* '<Root>/RaderRF' */
  real_T RaderRB;                      /* '<Root>/RaderRB' */
} ExtU_LaneLogic_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Alert;                        /* '<Root>/Alert' */
  real_T CenterCurvature;              /* '<Root>/CenterCurvature' */
  real_T ChangeLaneout;                /* '<Root>/ChangeLaneout' */
  int8_T BrakePercentage;              /* '<Root>/BrakePercentage' */
} ExtY_LaneLogic_T;

/* Real-time Model Data Structure */
struct tag_RTM_LaneLogic_T {
  const char_T *errorStatus;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[1];
    int32_T* vardimsAddress[1];
    RTWLoggingFcnPtr loggingPtrs[1];
  } DataMapInfo;
};

/* Constant parameters (default storage) */
extern const ConstP_LaneLogic_T LaneLogic_ConstP;

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  LaneLogic_GetCAPIStaticMap(void);

/* Class declaration for model LaneLogic */
class LaneLogicModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_LaneLogic_T LaneLogic_U;

  /* External outputs */
  ExtY_LaneLogic_T LaneLogic_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  LaneLogicModelClass();

  /* Destructor */
  ~LaneLogicModelClass();

  /* Real-Time Model get method */
  RT_MODEL_LaneLogic_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_LaneLogic_T LaneLogic_B;

  /* Block states */
  DW_LaneLogic_T LaneLogic_DW;

  /* Real-Time Model */
  RT_MODEL_LaneLogic_T LaneLogic_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'LaneLogic'
 * '<S1>'   : 'LaneLogic/Laneogicfull'
 * '<S2>'   : 'LaneLogic/Laneogicfull/F_Lane'
 * '<S3>'   : 'LaneLogic/Laneogicfull/Lane_system'
 * '<S4>'   : 'LaneLogic/Laneogicfull/Subsystem'
 * '<S5>'   : 'LaneLogic/Laneogicfull/F_Lane/Chart'
 * '<S6>'   : 'LaneLogic/Laneogicfull/F_Lane/Chart1'
 * '<S7>'   : 'LaneLogic/Laneogicfull/F_Lane/Chart2'
 * '<S8>'   : 'LaneLogic/Laneogicfull/F_Lane/Chart3'
 * '<S9>'   : 'LaneLogic/Laneogicfull/F_Lane/Chart4'
 * '<S10>'  : 'LaneLogic/Laneogicfull/Lane_system/Curvature'
 * '<S11>'  : 'LaneLogic/Laneogicfull/Lane_system/LaneSafeZone'
 * '<S12>'  : 'LaneLogic/Laneogicfull/Lane_system/LaneSafeZone/Chart'
 * '<S13>'  : 'LaneLogic/Laneogicfull/Subsystem/Chart'
 * '<S14>'  : 'LaneLogic/Laneogicfull/Subsystem/Chart1'
 * '<S15>'  : 'LaneLogic/Laneogicfull/Subsystem/Chart2'
 */
#endif                                 /* RTW_HEADER_LaneLogic_h_ */
