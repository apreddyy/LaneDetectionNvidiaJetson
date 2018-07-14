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
#include "Binary_Frame.h"

using namespace std;
using namespace cv;


void binary_frame(cuda::GpuMat& src, cuda::GpuMat& dst)/*void binary_frame(Mat& src, Mat& dst)*/
{
	int threshold_value = 110;
	int max_value = 255;
	cuda::threshold(src, dst, threshold_value, max_value, THRESH_BINARY);
	/*threshold(src, dst, threshold_value, max_value, THRESH_BINARY);*/
}
