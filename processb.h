#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/cudaarithm.hpp"
#include "opencv2/cudabgsegm.hpp"
#include "opencv2/cudacodec.hpp"
#include "opencv2/cudafeatures2d.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/cudaobjdetect.hpp"
#include "opencv2/cudaoptflow.hpp"
#include "opencv2/cudastereo.hpp"
#include "opencv2/cudawarping.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "opencv2/objdetect.hpp"
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "processedout.h"
#include "unwrap.h"
#include "processedout_emxAPI.h"
#include "processedout_types.h"
/*#include "LaneLogic/Implement/LaneLogic_grt_rtw/LaneLogic.h"*/
#include <thread>
#include "Rightprocessing.h"
#include "Leftprocessing.h"

using namespace std;
using namespace cv;




void processingb_frame(Mat& frame, cuda::GpuMat& src, double PointsA[720], double PointsB[720], int AlertSide, double center_data[], cuda::GpuMat& dst);
//void processingb_frame(Mat& frame, Mat& src, double PointsA[720], double PointsB[720], int AlertSide, double center_data[], Mat& dst);
