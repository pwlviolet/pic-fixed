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

Mat	myConv(Mat img, float k[3][3])
{
	Mat dst(img.rows - 2, img.cols - 2, img.type());
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int v = 0;
			for (int m = 0; m < 3; m++)
			{
				for (int n = 0; n < 3; n++)
				{
					v += img.at<uchar>(i + m, j + n)*k[m][n];

				}
			}
			dst.at<uchar>(i, j) = abs(v);
		}

	}
	return dst;
}
Mat	meanConv(Mat img, float k[3][3])
{
	Mat dst(img.rows - 2, img.cols - 2, img.type());
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int v = 0;
			for (int m = 0; m < 3; m++)
			{
				for (int n = 0; n < 3; n++)
				{
					v += img.at<uchar>(i + m, j + n)*k[m][n];

				}
			}
			dst.at<uchar>(i, j) = v / 9;
		}

	}
	return dst;
}
uchar Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5,
	uchar n6, uchar n7, uchar n8, uchar n9) {
	uchar arr[9];
	arr[0] = n1;
	arr[1] = n2;
	arr[2] = n3;
	arr[3] = n4;
	arr[4] = n5;
	arr[5] = n6;
	arr[6] = n7;
	arr[7] = n8;
	arr[8] = n9;
	for (int gap = 9 / 2; gap > 0; gap /= 2)
		for (int i = gap; i < 9; ++i)
			for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)
				swap(arr[j], arr[j + gap]);
	return arr[4];
}
void MedianFlitering(const Mat &src, Mat &dst) {
	if (!src.data)return;
	Mat _dst(src.size(), src.type());
	for (int i = 0; i < src.rows; ++i)
		for (int j = 0; j < src.cols; ++j) {
			if ((i - 1) > 0 && (i + 1) < src.rows && (j - 1) > 0 && (j + 1) < src.cols) {
				_dst.at<uchar>(i, j) = Median(src.at<uchar>(i, j), src.at<uchar>(i + 1, j + 1),
					src.at<uchar>(i + 1, j), src.at<uchar>(i, j + 1), src.at<uchar>(i + 1, j - 1),
					src.at<uchar>(i - 1, j + 1), src.at<uchar>(i - 1, j), src.at<uchar>(i, j - 1),
					src.at<uchar>(i - 1, j - 1));
			}
			else
				_dst.at<uchar>(i, j) = src.at<uchar>(i, j);
		}
	_dst.copyTo(dst);//拷贝
}


//Mat	medConv(Mat img, float k[3][3])
//{
//	Mat dst(img.rows - 2, img.cols - 2, img.type());
//	for (int i = 0; i<dst.rows; i++)
//	{
//		for (int j = 0; j<dst.cols; j++)
//		{
//			vector<int>n9;
//			for (int m = 0; m<3; m++)
//			{
//				for (int n = 0; n<3; n++)
//				{
//					
//
//				}
//			}
//			dst.at<uchar>(i, j) =  ;
//		}
//
//	}
//	return dst;
//}
Mat addNoise(Mat img, float rate = 0.05)
{
	int r10000 = rate * 10000;
	Mat dst;
	img.copyTo(dst);
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int r = rand() % 10000;
			if (r < r10000 / 2)
				dst.at<uchar>(i, j) = 0;
			else if (r < r10000)
				dst.at<uchar>(i, j) = 255;
			else
				;
		}
	}
	return dst;
}
Mat addSaltNoise(const Mat srcImage, int n)
{
	Mat dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{

		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;

		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 255;
			dstImage.at<Vec3b>(i, j)[1] = 255;
			dstImage.at<Vec3b>(i, j)[2] = 255;
		}
	}
	for (int k = 0; k < n; k++)
	{

		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;

		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 0;
			dstImage.at<Vec3b>(i, j)[1] = 0;
			dstImage.at<Vec3b>(i, j)[2] = 0;
		}
	}
	return dstImage;
}

int main()
{
	Mat img = imread("图片增强后.jpg");
	Mat dstgs_3; //Mat dstgs_5;
	//Mat img1 = addNoise(img);
	/*Mat img1 = addSaltNoise(img, 3000);
	Mat dstjz_3; Mat dstjz_5;
	Mat dstzz_3; Mat dstzz_5;
	
	blur(img1, dstjz_3, Size(3, 3));
	blur(img1, dstjz_5, Size(5, 5));
	medianBlur(img1, dstzz_3, 3);
	medianBlur(img1, dstzz_5, 5);*/
	GaussianBlur(img, dstgs_3, Size(3, 3), 3, 3);
	//GaussianBlur(img, dstgs_5, Size(5, 5), 5, 5);
	/*putText(img, "org_23", Point(30, 30), 1, 2, Scalar(255, 0, 255), 3);
	putText(img1, "add_23", Point(30, 30), 1, 2, Scalar(255, 0, 255), 3);
	putText(dstjz_3, "jz33_23", Point(30, 30), 1, 2, Scalar(255, 0, 255), 3);
	putText(dstjz_5, "jz55_23", Point(30, 30), 1, 2, Scalar(255, 0, 255), 3);


	putText(dstzz_3, "zz33_23", Point(30, 30), 1, 2, Scalar(255, 0, 255), 3);
	putText(dstzz_5, "zz55_23", Point(30, 30), 1, 2, Scalar(255, 0, 255), 3);

	putText(dstgs_3, "gs33_23", Point(30, 30), 1, 2, Scalar(255, 0, 255), 3);
	putText(dstgs_5, "gs55_23", Point(30, 30), 1, 2, Scalar(255, 0, 255), 3);
	imshow("img", img);
	imshow("add", img1);
	imshow("jz_3", dstjz_3);
	imshow("jz_5", dstjz_5);
	imshow("zz_3", dstzz_3);
	imshow("zz_5", dstzz_5);
	imshow("gs_3", dstgs_3);
	imshow("gs_5", dstgs_5);
	imshow("img", img);
	imwrite("add.jpg", img1);
	imwrite("img.jpg", img);
	imwrite("jz_3.jpg", dstjz_3);
	imwrite("jz_5.jpg", dstjz_5);
	imwrite("zz_3.jpg", dstzz_3);
	imwrite("zz_5.jpg", dstzz_5);
	imwrite("gs_3.jpg", dstgs_3);
	imwrite("gs_5.jpg", dstgs_5);

*/

	//Mat imgNoise = addNoise(img);
	//float k[3][3] = { 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11 };
	//Mat imgConv = myConv(imgNoise, k);
	////Mat medConv1 = medConv(imgNoise, k);
	//Mat zz;
	////medianBlur(imgNoise, zz, 3);
	//MedianFlitering(imgNoise, zz);
	//imshow("1", img);
	//imshow("imgNoise", imgNoise);
	//imshow("imgConv", imgConv);
	//imshow("zz", zz);
	//imwrite("1.jpg", img);
	//imwrite("imgNoise.jpg", imgNoise);
	//imwrite("imgConv.jpg", imgConv);
	//imwrite("medConv.jpg", zz);





	//float k1[3][3]={0,0.125,0,0.125,0.5,0.125,0,0.125,0};
	//Mat dst1=myConv(img,k1);
	//float k2[3][3]={0,0.125,0,0.125,0.5,0.125,0,0.125,0};
	//Mat dst2=myConv(img,k2);
	//float k3[3][3]={1,1,0,-1,1,0,0,0,0};

	//Mat dst3=myConv(img,k3);
	//imshow("img",img);
	//imshow("dst1",dst1);
	//imshow("dst3",dst3);
	imshow("dstgs_3", dstgs_3);
	imwrite("高斯滤波后.jpg", dstgs_3);
	waitKey(0);
	return 0;
}
