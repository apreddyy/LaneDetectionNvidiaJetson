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

using namespace std;
using namespace cv;

void calibration_on(int calibration)
{
int numBoards = 17;
int numCornersHor = 9;
int numCornersVer = 6;

	if (calibration == 1)
	{
		int numSquares = numCornersHor * numCornersVer;
		Size board_sz = Size(numCornersHor, numCornersVer);
		VideoCapture capture;
		capture.open("/home/nvidia/Documents/Laneoutput/camera_cal/%02d.jpg");

		vector<vector<Point3f>> object_points;
		vector<vector<Point2f>> image_points;

		vector<Point2f> corners;
		int successes = 0;
		Mat image;
		Mat gray_image;

		capture >> image;

		vector<Point3f> obj;
		for (int j = 0; j < numSquares; j++)
			obj.push_back(Point3f(float(j / numCornersHor), float(j%numCornersHor), 0.0f));

		while (successes < numBoards)
		{
			cvtColor(image, gray_image, CV_BGR2GRAY);

			bool found = findChessboardCorners(image, board_sz, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

			if (found)
			{
				cornerSubPix(gray_image, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
				drawChessboardCorners(gray_image, board_sz, corners, found);
			}

			capture >> image;
			int key = waitKey(1);

			if (found != 0)
			{
				image_points.push_back(corners);
				object_points.push_back(obj);
				cout << "Snap stored!" << endl;
				successes++;
				if (successes >= numBoards)
					break;
			}
		}

		VideoCapture capt;
		capt.open("/home/nvidia/Documents/Laneoutput/camera_cal/%02d.jpg");
		capt >> image;
		Mat intrinsic = Mat(3, 3, CV_32FC1);
		Mat distCoeffs;
		vector<Mat> rvecs;
		vector<Mat> tvecs;

		intrinsic.ptr<float>(0)[0] = 1;
		intrinsic.ptr<float>(1)[1] = 1;

		calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);

		cv::FileStorage fs("calibration.yml", cv::FileStorage::WRITE);
		fs << "intrinsic" << intrinsic;
		fs << "distCoeffs" << distCoeffs;
		fs.release();
	}

	else
	{
		Mat intrinsicn = Mat(3, 3, CV_32FC1);
		Mat distCoeffsn = Mat(3, 3, CV_32FC1);
		int num = 17;
		cv::FileStorage fs2("calibration.yml", cv::FileStorage::READ);
		fs2["intrinsic"] >> intrinsicn;
		fs2["distCoeffs"] >> distCoeffsn;
		fs2.release();
		Mat image;
		VideoCapture capt;
		capt.open("/home/nvidia/Documents/Laneoutput/camera_cal/%02d.jpg");
		int cntr = 0;
		Mat imageUndistorted;
		while (num > cntr)
		{
			capt >> image;
			undistort(image, imageUndistorted, intrinsicn, distCoeffsn);
			std::string savingName = "/home/nvidia/Documents/Laneoutput/camera_cal/output/" + std::to_string(++cntr) + ".jpg";
			imwrite(savingName, imageUndistorted);
			waitKey(1);
		}
		capt.release();
	}
}
