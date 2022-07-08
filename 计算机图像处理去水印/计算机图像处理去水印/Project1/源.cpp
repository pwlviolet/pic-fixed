
#include <imgproc\imgproc.hpp>
#include <highgui\highgui.hpp>
#include <photo\photo.hpp>

using namespace cv;
using namespace std;

Point ptL, ptR; //鼠标画出矩形框的起点和终点
Mat imageSource, imageSourceCopy;
Mat ROI; //原图需要修复区域的ROI

//鼠标回调函数
void OnMouse(int event, int x, int y, int flag, void *ustg);

//鼠标圈定区域

void OnMouse(int event, int x, int y, int flag, void *ustg)
{
	if (event == EVENT_LBUTTONDOWN)//左键
	{
		ptL = Point(x, y);
		ptR = Point(x, y);
	}
	if (flag == EVENT_FLAG_LBUTTON)//左键拖拽
	{
		ptR = Point(x, y);
		imageSourceCopy = imageSource.clone();
		rectangle(imageSourceCopy, ptL, ptR, Scalar(255, 0, 0));
		imshow("原图", imageSourceCopy);
	}
	if (event == EVENT_LBUTTONUP)//松开
	{
		if (ptL != ptR)
		{
			ROI = imageSource(Rect(ptL, ptR));
			imshow("ROI", ROI);
			imwrite("roi.jpg", ROI);
			waitKey();
		}
	}
	//单击鼠标右键开始图像修复
	if (event == EVENT_RBUTTONDOWN)
	{
		imageSourceCopy = ROI.clone();
		Mat imageGray;

		cvtColor(ROI, imageGray, COLOR_BGR2GRAY); //转换为灰度图

		GaussianBlur(imageGray, imageGray, Size(3, 3), 3, 3);//高斯滤波
		Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));


		//通过阈值处理生成Mask
		threshold(imageGray, imageMask, 240, 255, THRESH_OTSU);
		Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imageMask, imageMask, Kernel);  //对Mask膨胀处理
		inpaint(ROI, imageMask, ROI, 1, INPAINT_NS);  //图像修复
		imshow("Mask", imageMask);
		imshow("修复后", imageSource);
		imwrite("Mask.jpg", imageMask);
		imwrite("修复后.jpg", imageSource);
	}

}
int main()
{
	imageSource = imread("la1.jpg");
//	Mat imageRGB[3];
//split(imageSource, imageRGB);
//for (int i = 0; i < 3; i++)
//{
//	equalizeHist(imageRGB[i], imageRGB[i]);
//}
//merge(imageRGB, 3, imageSource);//图片增强
	if (!imageSource.data)
	{
		return -1;
	}
	imshow("原图", imageSource);
	setMouseCallback("原图", OnMouse);
	waitKey();
}


//全区域阈值处理+Mask膨胀处理
//int main()
//{
//	Mat imageSource = imread("1.jpg");
//	if (!imageSource.data)
//	{
//		return -1;
//	}
//	imshow("原图", imageSource);
//	Mat imageGray;
//	//转换为灰度图
//	cvtColor(imageSource, imageGray, COLOR_BGR2GRAY, 0);
//	Mat imageMask = Mat(imageSource.size(), CV_8UC1, Scalar::all(0));
//
//	//通过阈值处理生成Mask
//	threshold(imageGray, imageMask, 250, 255, 0);
//	Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//	//对Mask膨胀处理，增加Mask面积
//	dilate(imageMask, imageMask, Kernel);
//
//	//图像修复
//	inpaint(imageSource, imageMask, imageSource, 10, INPAINT_NS);
//	imshow("Mask", imageMask);
//	imshow("修复后", imageSource);
//	waitKey(0);
//}
