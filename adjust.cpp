#include "opencv2/opencv.hpp"
#include <iostream>
/*
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
*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <thread>

using namespace std;
using namespace cv;

void rconversion(Mat& src, Mat& dst);
void gconversion(Mat& src, Mat& dst);
void bconversion(Mat& src, Mat& dst);


void rconversion(Mat& src, Mat& dst)
{
	int in[2];
	in[0] = 204;
	in[1] = 230;
	int out[2];
	out[0] = 0;
	out[1] = 255;
	Mat1b SRC = src;
	Mat1b DST;
	DST = SRC.clone();
	float scale = float(out[1] - out[0]) / float(in[1] - in[0]);
	for (int r = 0; r < src.rows; ++r)
	{
		for (int c = 0; c < src.cols; ++c)
		{
			int vs = max(SRC(r, c) - in[0], 0);
			int vd = min(int(vs * scale + 0.5f) + out[0], out[1]);
			DST(r, c) = saturate_cast<uchar>(vd);
		}
	}
	dst = DST;

}

void gconversion(Mat& src, Mat& dst)
{
	int in[2];
	in[0] = 128;
	in[1] = 204;
	int out[2];
	out[0] = 0;
	out[1] = 255;
	Mat1b SRC = src;
	Mat1b DST;
	DST = SRC.clone();
	float scale = float(out[1] - out[0]) / float(in[1] - in[0]);
	for (int r = 0; r < src.rows; ++r)
	{
		for (int c = 0; c < src.cols; ++c)
		{
			int vs = max(SRC(r, c) - in[0], 0);
			int vd = min(int(vs * scale + 0.5f) + out[0], out[1]);
			DST(r, c) = saturate_cast<uchar>(vd);
		}
	}
	dst = DST;
}

void bconversion(Mat& src, Mat& dst)
{
	int in[2];
	in[0] = 0;
	in[1] = 51;
	int out[2];
	out[0] = 0;
	out[1] = 255;
	Mat1b SRC = src;
	Mat1b DST;
	DST = SRC.clone();
	float scale = float(out[1] - out[0]) / float(in[1] - in[0]);
	for (int r = 0; r < src.rows; ++r)
	{
		for (int c = 0; c < src.cols; ++c)
		{
			int vs = max(SRC(r, c) - in[0], 0);
			int vd = min(int(vs * scale + 0.5f) + out[0], out[1]);
			DST(r, c) = saturate_cast<uchar>(vd);
		}
	}
	dst = DST;
}


void imadjust(cuda::GpuMat& src, cuda::GpuMat& dst)//void imadjust(Mat& src, Mat& dst)
{
	/*Mat imager, imageg, imageb, outr, outg, outb;
	cuda::GpuMat channels_device[3], channels_device_dest[3];
	cuda::split(src, channels_device);
	channels_device[2].download(imager);
	channels_device[1].download(imageg);
	channels_device[0].download(imageb);
	//thread Rt(rconversion, imager, outr);
	//thread Gt(gconversion, imageg, outg);
	//thread Bt(bconversion, imageb, outb);
	rconversion(imager, outr);
	gconversion(imageg, outg);
	bconversion(imageb, outb);
	//Rt.join();
	//Gt.join();
	//Bt.join();
	
	channels_device_dest[2].upload(outr);
	channels_device_dest[1].upload(outg);
	channels_device_dest[0].upload(outb);
	cuda::merge(channels_device_dest, 3, dst);*/
	
}

