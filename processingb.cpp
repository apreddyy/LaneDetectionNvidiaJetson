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
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "processedout.h"
#include "unwrap.h"
#include "processedout_emxAPI.h"
#include "processedout_types.h"
#include "LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic.h"
#include <thread>
#include "Rightprocessing.h"
#include "Leftprocessing.h"
#include "processb.h"

using namespace std;
using namespace cv;




void processingb_frame(Mat& frame, cuda::GpuMat& src, double PointsA[720], double PointsB[720], int AlertSide, double center_data[], cuda::GpuMat& dst)//void processingb_frame(Mat& frame, Mat& src, double PointsA[720], double PointsB[720], int AlertSide, double center_data[], Mat& dst)
{
	cuda::GpuMat unwrap_framein, unwrap_frameout, merge_frameout, sobel_frameout;
	int AlertOut;
	LaneLogicModelClass LaneLogicModel;
	LaneLogicModel.initialize();
	LaneLogicModel.LaneLogic_U.Distance = center_data[0];
	LaneLogicModel.step();
	LaneLogicModel.step();
	AlertOut = int(LaneLogicModel.LaneLogic_Y.Alert);
	int mL = 360;
	int	mR = 360;
	int nL = 2;
	int	nR = 2;
	int dataL[720];
	int dataR[720];
	int Multithreading = 1;
	if (Multithreading == 0)
	{
		thread tL(leftprocessing, PointsA, dataL);
		thread tR(rightprocessing, PointsB, dataR);
		tL.join();
		tR.join();
	}
	else
	{
		int ii, jj;
		for (ii = 0; ii < nL; ii++)
			for (jj = 0; jj < mL; jj++)
			{
				dataL[ii + nL * jj] = (int)PointsA[ii*mL + jj];
			}
		int ir, jr;
		for (ir = 0; ir < nR; ir++)
			for (jr = 0; jr < mR; jr++)
			{
				dataR[ir + nR * jr] = (int)PointsB[ir*mR + jr];
			}
	}
	Mat Lpoint = Mat(mL, nL, CV_32SC1, dataL);
	Mat Rpoint = Mat(mR, nR, CV_32SC1, dataR);
	Mat maskImage = Mat(frame.size(), CV_8UC3, Scalar(0));
	vector<Point2i>TestPoint;
	for (int r = 0; r < mL; r++)
	{
		Point2i L = (Point2i(Lpoint.at <int>(r, 0), Lpoint.at <int>(r, 1)));
		TestPoint.push_back(L);
		drawMarker(maskImage, L, Scalar(0, 0, 255), MARKER_SQUARE, 30, 1, 8);

	}
	for (int rp = 359; rp >= 0; rp--)
	{
		Point2i R = (Point2i(Rpoint.at <int>(rp, 0), Rpoint.at <int>(rp, 1)));
		TestPoint.push_back(R);
		drawMarker(maskImage, R, Scalar(0, 0, 255), MARKER_SQUARE, 30, 1, 8);
	}
	const Point *pts = (const cv::Point*)Mat(TestPoint).data;
	int npts = Mat(TestPoint).rows;
	if (AlertOut == 3)
	{
		fillPoly(maskImage, &pts, &npts, 1, Scalar(0, 255, 0), 8);
	}
	else
	{
		fillPoly(maskImage, &pts, &npts, 1, Scalar(255, 0, 10), 8);
	}
	unwrap_framein.upload(maskImage);
	unwrap_frame(unwrap_framein, unwrap_frameout);
	cuda::addWeighted(src, 1, unwrap_frameout, 0.5, -1, dst);
}

