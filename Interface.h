#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

class Interface
{
private:
	void Set(Mat mat, int posX, int posY);
	void SetNResize(Mat mat, int posX, int posY, int resX, int resY);
public:
	Mat resultImage = Mat(1, 1, CV_8UC4);
	void Frame(int width, int height);
};