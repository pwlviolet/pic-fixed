
#include <imgproc\imgproc.hpp>
#include <highgui\highgui.hpp>
#include <photo\photo.hpp>

using namespace cv;


int main()
{
	Mat img;
	Mat dst=Mat(img.size(), CV_8UC1, Scalar::all(0)); 
	Mat dst1 = Mat(img.size(), CV_8UC1, Scalar::all(0));
	img = imread("高斯滤波后.jpg");
	threshold(img, dst, 200, 255, 0);
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(dst, dst1, Kernel);
	if (!img.data)
	{
		return -1;
	}
	imshow("原图", img);
	
	imshow("dst", dst);
	imshow("dst1", dst);
	imwrite("膨胀.jpg", dst1);
	//imwrite("阈值处理后图.jpg", dst);
	
	waitKey(0);
}

	//if (event == EVENT_RBUTTONDOWN)
	//{
	//	imageSourceCopy = ROI.clone();
	//	Mat imageGray;
	//	cvtColor(ROI, imageGray, COLOR_BGR2GRAY); //转换为灰度图
	//	Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));

	//	//通过阈值处理生成Mask
	//	threshold(imageGray, imageMask, 240, 255, THRESH_OTSU);
	//	Mat Kernel = getStructuringElement(MORPH_RECT, Size(1, 1));
	//	dilate(imageMask, imageMask, Kernel);  //对Mask膨胀处理
	//	inpaint(ROI, imageMask, ROI, 1, INPAINT_NS);  //图像修复
	//	imshow("Mask", imageMask);
	//	imshow("修复后", imageSource);
	//}


