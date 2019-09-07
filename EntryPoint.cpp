#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

int w, h, type, additional;
Mat result(1,1, CV_8UC4);
char fileName[256];

void Set(Mat mat, int posX, int posY)
{
	Point startPosition = Point(posX, posY);
	Size size = mat.size();
	Rect subImageRect = Rect(startPosition, size);
	Mat outputSubImage = result(subImageRect);
	mat.copyTo(outputSubImage);
}

void SetNResize(Mat mat, int posX, int posY, int resX, int resY)
{
	try	{ resize(mat, mat, Size(resX, resY)); }
	catch (cv::Exception & e){ cerr << e.msg << endl; }

	Set(mat, posX, posY);
}

void ResizeCanvas(int w, int h)
{
	try	{ resize(result, result, Size(w, h)); }
	catch (cv::Exception & e) { cerr << e.msg << endl; }
}

int main(int argc, char* argv[])
{
	type = atoi(argv[1]), w = atoi(argv[2]);
	if(argc == 4) h = atoi(argv[3]);
	if(argc == 5) additional = atoi(argv[4]);

	if(type == 0 || type == 1 || type == 2)
	{
		Mat image[9];
		string folder;

		if (type == 0)	folder = "Frame/";
		else if (type == 1) folder = "FrameDehilight/";
		else if (type == 2) folder = "SelectedDisable/";

		image[0] = imread(folder + "lt.png", -1);
		image[1] = imread(folder + "ct.png", -1);
		image[2] = imread(folder + "rt.png", -1);
		image[3] = imread(folder + "lc.png", -1);
		image[4] = imread(folder + "cc.png", -1);
		image[5] = imread(folder + "rc.png", -1);
		image[6] = imread(folder + "lb.png", -1);
		image[7] = imread(folder + "cb.png", -1);
		image[8] = imread(folder + "rb.png", -1);

		ResizeCanvas(w, h);

		Set(image[0], 0, 0);

		SetNResize(image[1], image[0].size().width, 0, 
			w - (image[0].size().width + image[2].size().width), image[1].size().height);

		Set(image[2], w - image[2].size().width, 0);

		SetNResize(image[3], 0, image[0].size().height, image[3].size().width, 
			h - (image[0].size().height + image[6].size().height));

		SetNResize(image[4], image[0].size().width, image[0].size().height,
			w - (image[3].size().width + image[5].size().width),
			h - (image[1].size().height + image[7].size().height));

		SetNResize(image[5], w - image[5].size().width, image[2].size().height, 
			image[5].size().width, h - (image[2].size().height + image[8].size().height));

		Set(image[6], 0, h - image[6].size().height);

		SetNResize(image[7], image[6].size().width, h - image[7].size().height,
			w - (image[6].size().width + image[7].size().height), image[5].size().width);

		Set(image[8], w - image[8].size().width, h - image[8].size().height);

		sprintf(fileName, "%dx%dkey%d.png", w, h, type);
		cv::imwrite(fileName, result);
	}
	else if (type == 3 || type == 4)
	{
		Mat image[9];
		string folder;

		if (type == 3)	folder = "Button/";
		else if (type == 4)	folder = "ButtonGlow/";

		image[0] = imread(folder + "ln.png", -1);
		image[1] = imread(folder + "lo.png", -1);
		image[2] = imread(folder + "lc.png", -1);
		image[3] = imread(folder + "cn.png", -1);
		image[4] = imread(folder + "co.png", -1);
		image[5] = imread(folder + "cc.png", -1);
		image[6] = imread(folder + "rn.png", -1);
		image[7] = imread(folder + "ro.png", -1);
		image[8] = imread(folder + "rc.png", -1);
		
		ResizeCanvas(w, image[0].size().height);

		for (int a = -1; a < 2; a++)
		{
			Set(image[a + 1], 0, 0);

			SetNResize(image[a + 4], image[a + 1].size().width, 0,
				w - (image[a + 1].size().width + image[a + 7].size().width), image[a + 1].size().height);

			Set(image[a + 7], w - image[a + 7].size().width, 0);

			if(a == -1)	sprintf(fileName, "%dx%dkey%dN.png", w, image[a + 1].size().height, type);
			else if (a == 0)	sprintf(fileName, "%dx%dkey%dO.png", w, image[a + 1].size().height, type);
			else if (a == 1)	sprintf(fileName, "%dx%dkey%dC.png", w, image[a + 1].size().height, type);

			cv::imwrite(fileName, result);
		}
	}
 	
	return 1;
}