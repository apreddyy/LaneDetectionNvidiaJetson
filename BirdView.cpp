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
#include "BirdView.h"

using namespace std;
using namespace cv;
void birdview_frame(cuda::GpuMat& src, cuda::GpuMat& dst)//void birdview_frame(Mat& src, Mat& dst)
{
	cv::Point2f src_points[4];
	cv::Point2f dst_points[4];
	src_points[0] = cv::Point2f(290, 230);
	src_points[1] = cv::Point2f(350, 230);
	src_points[2] = cv::Point2f(520, 340);
	src_points[3] = cv::Point2f(130, 340);
	// to points
	dst_points[0] = cv::Point2f(130, 0);
	dst_points[1] = cv::Point2f(520, 0);
	dst_points[2] = cv::Point2f(520, 360);
	dst_points[3] = cv::Point2f(130, 360);
	Mat trans_points = getPerspectiveTransform(src_points, dst_points);
	cuda::warpPerspective(src, dst, trans_points, src.size(), cv::INTER_LINEAR);
	//warpPerspective(src, dst, trans_points, src.size(), cv::INTER_LINEAR);

}
