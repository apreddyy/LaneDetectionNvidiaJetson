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
#include "sobel.h"
#include "gray.h"

using namespace std;
using namespace cv;

void sobelframe::sobel_frame(cuda::GpuMat& src, cuda::GpuMat& dst)
{
	grayframe grayouts;
	cuda::GpuMat sobelx, sobely, adwsobelx, adwsobely, gray_framea;
	grayouts.gray_frame(src, gray_framea);
	Ptr<cuda::Filter> filter = cv::cuda::createSobelFilter(gray_framea.type(), CV_16S, 1, 0, 3, 1, BORDER_DEFAULT);
	filter->apply(gray_framea, sobelx);
	cuda::abs(sobelx, sobelx);
	sobelx.convertTo(dst, CV_8UC1);
}