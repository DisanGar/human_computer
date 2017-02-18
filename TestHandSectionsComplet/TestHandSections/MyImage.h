#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class MyImage
{
public:

	Mat srcLR;
	Mat src;
	Mat bw;

	vector<Mat> bwList;

	VideoCapture cap;

	int cameraSrc;

	MyImage(int webCam);
	MyImage();
 
	void initWebCamera(int i);

};

