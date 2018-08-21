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
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "processedout.h"
#include "processedout_emxAPI.h"
#include "processedout_types.h"
#include "processedout_initialize.h"
#include "all_header.h"
#include "constants.h"

bool do_calib;

using namespace std;
using namespace cv;


int main(int, const char * const[])
{
	
	VideoCapture cap("openv.avi");
	if (!cap.isOpened())
	{
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
	Mat mapa, mapb;
	calibration_on();
	Mat intrinsicn = Mat(3, 3, CV_32FC1);
	Mat distCoeffsn =  Mat(3, 3, CV_32FC1);;
	cv::FileStorage fs2("calibration.yml", cv::FileStorage::READ);
	fs2["intrinsic"] >> intrinsicn;
	fs2["distCoeffs"] >> distCoeffsn;
	initUndistortRectifyMap(intrinsicn, distCoeffsn, cv::Mat::eye(3, 3, CV_32FC1), intrinsicn, cv::Size(640, 360), CV_32FC1, mapa, mapb);
	while (1)
	{
		Mat frame, cudaout_frame, frame_out, undisort_frame;
		cuda::GpuMat process_frame, process_frameout, resize_frame, process_framein, gpu_mapa, gpu_mapb;
		int Width;
		int Height;
		Width = 640;
		Height = 360;
		double AlertSide;
		double center_data[1];
		int center_size[1];
		double left_curvature;
		double right_curveature;
		static int iv0[2] = { Height, Width };
		emxArray_uint8_T   *imageInput;
		imageInput = emxCreateND_uint8_T(2, *(int(*)[2])&iv0[0]);
		emxArray_uint8_T   *imageInputout;
		imageInputout = emxCreateND_uint8_T(2, *(int(*)[2])&iv0[0]);
		processedout_initialize();
		double PointsA[720];
		double PointsB[720];		
		for (;;)
		{
			cap >> frame;
			if (frame.empty())
				break;
			gpu_mapa.upload(mapa);
			gpu_mapb.upload(mapb);
			process_framein.upload(frame);			
			processinga_frame(process_framein, resize_frame, process_frame, gpu_mapa, gpu_mapb);
			process_frame.download(cudaout_frame);
			int i, j;
			for (i = 0; i < Width; i++)
				for (j = 0; j < Height; j++)
					imageInput->data[i*Height+ j] = (uint8_T)cudaout_frame.data[i+ Width * j];
			processedout(imageInput, PointsA, PointsB, &AlertSide, center_data, center_size, &left_curvature, &right_curveature); 
			processingb_frame(cudaout_frame, resize_frame, PointsA, PointsB, AlertSide, center_data, process_frameout);
			process_frameout.download(frame_out);
			imshow("FrameL", frame_out);
			if (waitKey(10) >= 0)break;				
		}
		return 0;
	}
}
