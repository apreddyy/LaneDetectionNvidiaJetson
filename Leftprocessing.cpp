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
#include "Leftprocessing.h"

using namespace std;
using namespace cv;

void leftprocessing(double PointA[720],  int dataL[720])
{
	int mL = 360;
	int nL = 2;
	int ii, jj;
	for (ii = 0; ii < nL; ii++)
		for (jj = 0; jj < mL; jj++)
		{
			dataL[ii + nL * jj] = (int)PointA[ii*mL + jj];
		}
}
