//#####################################################################################//
//#####################################################################################//
//#####################################################################################//
//# Please include the Github Repositories web URL if you are using this material.    #//
//#####################################################################################//
//#####################################################################################//
//#####################################################################################//



#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/cudaarithm.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/cudawarping.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;



void processinga_frame(cuda::GpuMat& src, cuda::GpuMat& resize, cuda::GpuMat& dst, cuda::GpuMat& gpu_mapa, cuda::GpuMat& gpu_mapb);
void processingb_frame(Mat& frame, cuda::GpuMat& src, double PointsA[720], double PointsB[720], double AlertSide, double center_data[], cuda::GpuMat& dst);
void calibration_on(int calibration);