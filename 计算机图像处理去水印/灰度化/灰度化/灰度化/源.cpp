#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/video/background_segm.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;
int main()
{
	Mat img = imread("1.jpg");
	//resize(img, img, Size(200, 200));
	Mat dst(img.rows, img.cols, img.type());
	cvtColor(img, dst, COLOR_BGR2GRAY);
	imshow("img", img);
	imshow("dst", dst);
	imwrite("ԭͼ.jpg", img);
	imwrite("�Ҷ�ͼ.jpg", dst);
	waitKey(0);
	}


