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
#include "RESIZEFrame.h"



using namespace std;
using namespace cv;


void resize_frame(cuda::GpuMat& src, cuda::GpuMat& dst)//void resize_frame(Mat& src, Mat& dst)
{
	double resize_height = 0.5;
	double resize_weidght = 0.5;
	cuda::resize(src, dst, Size(), resize_weidght, resize_height);

}
