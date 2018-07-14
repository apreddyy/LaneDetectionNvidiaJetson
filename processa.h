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
#include "HSVFrame.h"
#include "RESIZEFrame.h"
#include "GrayFrame.h"
#include "Binary_Frame.h"
#include "BirdView.h"
#include "sobelfilter.h"
#include "adjust.h"


using namespace std;
using namespace cv;


void processinga_frame(cuda::GpuMat& src, cuda::GpuMat& resize, cuda::GpuMat& dst);
//void processinga_frame(Mat& src, Mat& resize, Mat& dst);
