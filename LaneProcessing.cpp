#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/cudaarithm.hpp"
#include "opencv2/cudacodec.hpp"
#include "opencv2/cudaimgproc.hpp"
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
#include "processedout_emxAPI.h"
#include "processedout_types.h"
#include "processa.h"
#include "processb.h"
#include "LaneLogic/ADVANCELANE/LaneLogic_grt_rtw/LaneLogic.h"


using namespace std;
using namespace cv;



void processinga_frame(cuda::GpuMat& src, cuda::GpuMat& resize, cuda::GpuMat& dst);
void processingb_frame(Mat& frame, cuda::GpuMat& src, double PointsA[720], double PointsB[720], int AlertSide, double center_data[], cuda::GpuMat& dst);


/*void processinga_frame(Mat& src, Mat& resize, Mat& dst);
void processingb_frame(Mat& frame, Mat& src, double PointsA[720], double PointsB[720], int AlertSide, double center_data[], Mat& dst);*/


int main(int, const char * const[])
{
	setenv("DISPLAY", ":0", 0);
	VideoCapture cap("openv.mp4");
	if (!cap.isOpened())
	{
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
	while (1)
	{
		Mat frame,  cudaout_frame, frame_out;
		//Mat process_framein, process_frame, process_frameout, resize_frame;
		cuda::GpuMat process_framein, process_frame, process_frameout, resize_frame;
		int Width;
		int Height;
		Width = 640;
		Height = 360;
		int AlertSide;
		double center_data[1];
		int center_size[1];
		double left_curvature;
		double right_curveature;
		double curvature;
		static int iv0[2] = { Height, Width };
		emxArray_uint8_T   *imageInput;
		imageInput = emxCreateND_uint8_T(2, *(int(*)[2])&iv0[0]);
		emxArray_uint8_T   *imageInputout;
		imageInputout = emxCreateND_uint8_T(2, *(int(*)[2])&iv0[0]);
		processedout_initialize();
		double PointsA[720];
		double PointsB[720];
		/*VideoWriter video("/path/test_video.avi", CV_FOURCC('P','I','M','1'), 25, Size(640, 360), true);*/
		for (;;)
		{
			cap >> frame;
			if (frame.empty())
				break;
			process_framein.upload(frame);
			processinga_frame(process_framein, resize_frame, process_frame);
			process_frame.download(cudaout_frame);
			int i, j;
			for (i = 0; i < Width; i++)
				for (j = 0; j < Height; j++)
					imageInput->data[i*Height+ j] = (uint8_T)cudaout_frame.data[i+ Width * j];
			processedout(imageInput, PointsA, PointsB, &AlertSide, center_data, center_size, &left_curvature, &right_curveature); 
			processingb_frame(cudaout_frame, resize_frame, PointsA, PointsB, AlertSide, center_data, process_frameout);
			LaneLogicModelClass LaneLogicModel;
			LaneLogicModel.initialize();
			LaneLogicModel.LaneLogic_U.LeftCurvature = left_curvature;
			LaneLogicModel.LaneLogic_U.RightCurvature = right_curveature;
			LaneLogicModel.step();
			LaneLogicModel.step();
			curvature = double(LaneLogicModel.LaneLogic_Y.CenterCurvature);
			cout << left_curvature << ";" << curvature << ";" << right_curveature << endl;
			process_frameout.download(frame_out);
			/*video.write(process_frameout);*/
			imshow("FrameL", frame_out);
			if (waitKey(10) >= 0)break;				
		}
		return 0;
	}
}
