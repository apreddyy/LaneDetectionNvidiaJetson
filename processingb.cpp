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
#include "all_header.h"
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "processedout.h"
#include "processedout_emxAPI.h"
#include "processedout_types.h"
#include "imagewrap.h"


using namespace std;
using namespace cv;




void processingb_frame(Mat& frame, cuda::GpuMat& src, double PointsA[720], double PointsB[720], double AlertSide, double center_data[], cuda::GpuMat& dst)
{
	cuda::GpuMat unwrap_framein, unwrap_frameout, merge_frameout, sobel_frameout;
	cv::Point2f src_points[4];
	cv::Point2f dst_points[4];

	src_points[0] = cv::Point2f(290, 230);
	src_points[1] = cv::Point2f(350, 230);
	src_points[2] = cv::Point2f(520, 340);
	src_points[3] = cv::Point2f(130, 340);

	dst_points[0] = cv::Point2f(130, 0);
	dst_points[1] = cv::Point2f(520, 0);
	dst_points[2] = cv::Point2f(520, 360);
	dst_points[3] = cv::Point2f(130, 360);

	wrapframe unwrapout;

	//cout << " Away Fromcenter :" << abs(center_data[0]) << " ;" << "AlertOut :" << AlertOut <<endl;

	int m = 360;
	int n = 2;
	int dataL[720];
	int dataR[720];

	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
		{
			dataL[i + n * j] = (int)PointsA[i*m + j];
			dataR[i + n * j] = (int)PointsB[i*m + j];
		}
	
	Mat Lpoint = Mat(m, n, CV_32SC1, dataL);
	Mat Rpoint = Mat(m, n, CV_32SC1, dataR);
	Mat maskImage = Mat(frame.size(), CV_8UC3, Scalar(0));
	vector<Point2i>PointLeft;
	vector<Point2i>PointRight;


	for (int r = 0; r < m; r++)
	{
		int c = 359 - r;
		Point2i L = (Point2i(Lpoint.at <int>(r, 0), Lpoint.at <int>(r, 1)));
		PointLeft.push_back(L);
		drawMarker(maskImage, L, Scalar(0, 0, 255), MARKER_SQUARE, 30, 1, 8);
		Point2i R = (Point2i(Rpoint.at <int>(c, 0), Rpoint.at <int>(c, 1)));
		PointRight.push_back(R);
		drawMarker(maskImage, R, Scalar(0, 0, 255), MARKER_SQUARE, 30, 1, 8);
	}

	vector<Point2i>PointLeftRight;
	PointLeft.insert(PointLeft.end(), PointRight.begin(), PointRight.end());
	PointLeftRight = PointLeft;

	const Point *pts = (const cv::Point*)Mat(PointLeftRight).data;
	int npts = Mat(PointLeftRight).rows;
	if (AlertSide == 3)
	{
		fillPoly(maskImage, &pts, &npts, 1, Scalar(0, 255, 0), 8);
	}
	else
	{
		fillPoly(maskImage, &pts, &npts, 1, Scalar(255, 0, 10), 8);
	}

	unwrap_framein.upload(maskImage);
	unwrapout.wrap_frame(unwrap_framein, unwrap_frameout, dst_points, src_points);

	cuda::addWeighted(src, 1, unwrap_frameout, 0.5, -1, dst);
}

