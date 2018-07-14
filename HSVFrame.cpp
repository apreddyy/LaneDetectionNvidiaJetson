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
#include "HSVFrame.h"


using namespace std;
using namespace cv;


void hsv_frame(cuda::GpuMat& src, cuda::GpuMat& dst)//void hsv_frame(Mat& src, Mat& dst)
{
	cuda::GpuMat hsv_frame, temp;
	cuda::GpuMat channels_device[3];
	cuda::GpuMat channels_device_dest[3];
	cuda::cvtColor(src, hsv_frame, COLOR_BGR2HSV);
	cuda::split(hsv_frame, channels_device);
	cuda::threshold(channels_device[0], channels_device_dest[0],  0, 100, THRESH_BINARY);
	cuda::threshold(channels_device[2], channels_device_dest[1], 210, 255, THRESH_BINARY);
	cuda::threshold(channels_device[2], channels_device_dest[2], 200, 255, THRESH_BINARY);
	cuda::merge(channels_device_dest, 3, temp);
	cuda::cvtColor(temp, dst, COLOR_HSV2BGR);
	/*Mat hsv_frame, temp;
	Mat channels_device[3];
	Mat channels_device_dest[3];
	cvtColor(src, hsv_frame, COLOR_BGR2HSV);
	split(hsv_frame, channels_device);
	threshold(channels_device[0], channels_device_dest[0],  0, 100, THRESH_BINARY);
	threshold(channels_device[2], channels_device_dest[1], 210, 255, THRESH_BINARY);
	threshold(channels_device[2], channels_device_dest[2], 200, 255, THRESH_BINARY);
	merge(channels_device_dest, 3, temp);
	cvtColor(temp, dst, COLOR_HSV2BGR);*/
}
