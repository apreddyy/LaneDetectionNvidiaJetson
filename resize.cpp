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
#include "resize.h"



using namespace std;
using namespace cv;


void resizeframe::resize_frame(cuda::GpuMat& src, cuda::GpuMat& dst)
{
	int resize_height = 360;
	int resize_weidght = 640;
	cuda::resize(src, dst, Size(resize_weidght, resize_height));
}