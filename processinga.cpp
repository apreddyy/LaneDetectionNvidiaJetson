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
#include "processa.h"

using namespace std;
using namespace cv;

void hsv_frame(cuda::GpuMat& src, cuda::GpuMat& dst);
void resize_frame(cuda::GpuMat& src, cuda::GpuMat& dst);
void gray_frame(cuda::GpuMat& src, cuda::GpuMat& dst);
void binary_frame(cuda::GpuMat& src, cuda::GpuMat& dst);
void birdview_frame(cuda::GpuMat& src, cuda::GpuMat& dst);
void sobel_frame(cuda::GpuMat& src, cuda::GpuMat& dst);
void imadjust(cuda::GpuMat& src, cuda::GpuMat& dst);

/*void hsv_frame(Mat& src, Mat& dst);
void resize_frame(Mat& src, Mat& dst);
void gray_frame(Mat& src, Mat& dst);
void binary_frame(Mat& src, Mat& dst);
void birdview_frame(Mat& src, Mat& dst);
void sobel_frame(Mat& src, Mat& dst);
void imadjust(Mat& src, Mat& dst);*/




void processinga_frame(cuda::GpuMat& src, cuda::GpuMat& resize, cuda::GpuMat& dst)//void processinga_frame(Mat& src, Mat& resize, Mat& dst)
{
	Mat frame, cudaout_frame, MergeFrameOut, cudaout_framet;
	cuda::GpuMat  resize_framea, gray_framea, binary_framea, birdview_framea, hsv_framea, threshold_frame, sobel_frameout;
	resize_frame(src, resize_framea);
	resize = resize_framea;
	/*imadjust(resize_framea, adjust_framea);*/
	birdview_frame(resize_framea, birdview_framea);
	sobel_frame(birdview_framea, sobel_frameout);
	hsv_frame(birdview_framea, hsv_framea);
	gray_frame(hsv_framea, gray_framea);
	binary_frame(gray_framea, binary_framea);
	cuda::addWeighted(binary_framea, 0.9, sobel_frameout, 0.1, -1, dst);
}
