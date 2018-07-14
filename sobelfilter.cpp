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
#include "sobelfilter.h"
#include "GrayFrame.h"

using namespace std;
using namespace cv;

void sobel_frame(cuda::GpuMat& src, cuda::GpuMat& dst)
{
	cuda::GpuMat sobelx, sobely, adwsobelx, adwsobely, gray_framea;
	gray_frame(src, gray_framea);
	Ptr<cuda::Filter> filter = cv::cuda::createSobelFilter(gray_framea.type(), CV_16S, 1, 0, 3, 1, BORDER_DEFAULT);
	filter->apply(gray_framea, sobelx);
	//Sobel(gray_framea, sobelx, CV_16S, 1, 0, 3, 1, BORDER_DEFAULT);;
	cuda::abs(sobelx, sobelx);
	sobelx.convertTo(dst, CV_8UC1);
}
