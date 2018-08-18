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
#include "imagewrap.h"

using namespace std;
using namespace cv;

void wrapframe::wrap_frame(cuda::GpuMat& src, cuda::GpuMat& dst, Point2f* src_points, Point2f* dst_points)
{
	
	Mat trans_points = getPerspectiveTransform(src_points, dst_points);
	cuda::warpPerspective(src, dst, trans_points, src.size(), cv::INTER_LINEAR);

}