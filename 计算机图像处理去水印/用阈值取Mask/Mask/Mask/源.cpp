
#include <imgproc\imgproc.hpp>
#include <highgui\highgui.hpp>
#include <photo\photo.hpp>

using namespace cv;


int main()
{
	Mat img;
	Mat dst=Mat(img.size(), CV_8UC1, Scalar::all(0)); 
	Mat dst1 = Mat(img.size(), CV_8UC1, Scalar::all(0));
	img = imread("��˹�˲���.jpg");
	threshold(img, dst, 200, 255, 0);
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(dst, dst1, Kernel);
	if (!img.data)
	{
		return -1;
	}
	imshow("ԭͼ", img);
	
	imshow("dst", dst);
	imshow("dst1", dst);
	imwrite("����.jpg", dst1);
	//imwrite("��ֵ�����ͼ.jpg", dst);
	
	waitKey(0);
}

	//if (event == EVENT_RBUTTONDOWN)
	//{
	//	imageSourceCopy = ROI.clone();
	//	Mat imageGray;
	//	cvtColor(ROI, imageGray, COLOR_BGR2GRAY); //ת��Ϊ�Ҷ�ͼ
	//	Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));

	//	//ͨ����ֵ��������Mask
	//	threshold(imageGray, imageMask, 240, 255, THRESH_OTSU);
	//	Mat Kernel = getStructuringElement(MORPH_RECT, Size(1, 1));
	//	dilate(imageMask, imageMask, Kernel);  //��Mask���ʹ���
	//	inpaint(ROI, imageMask, ROI, 1, INPAINT_NS);  //ͼ���޸�
	//	imshow("Mask", imageMask);
	//	imshow("�޸���", imageSource);
	//}


