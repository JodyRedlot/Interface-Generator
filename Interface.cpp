#include "Interface.h"

void Interface::Set(Mat mat, int posX, int posY)
{
	Point startPosition = Point(posX, posY);
	Size size = mat.size();
	Rect subImageRect = Rect(startPosition, size);
	Mat outputSubImage = resultImage(subImageRect);
	mat.copyTo(outputSubImage);
}

void Interface::SetNResize(Mat mat, int posX, int posY, int resX, int resY)
{
	try { resize(mat, mat, Size(resX, resY)); }
	catch (cv::Exception & e) { cerr << e.msg << endl; }

	Set(mat, posX, posY);
}