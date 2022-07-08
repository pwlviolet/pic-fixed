
#include <imgproc\imgproc.hpp>
#include <highgui\highgui.hpp>
#include <photo\photo.hpp>

using namespace cv;
using namespace std;

Point ptL, ptR; //��껭�����ο�������յ�
Mat imageSource, imageSourceCopy;
Mat ROI; //ԭͼ��Ҫ�޸������ROI

//���ص�����
void OnMouse(int event, int x, int y, int flag, void *ustg);

//���Ȧ������

void OnMouse(int event, int x, int y, int flag, void *ustg)
{
	if (event == EVENT_LBUTTONDOWN)//���
	{
		ptL = Point(x, y);
		ptR = Point(x, y);
	}
	if (flag == EVENT_FLAG_LBUTTON)//�����ק
	{
		ptR = Point(x, y);
		imageSourceCopy = imageSource.clone();
		rectangle(imageSourceCopy, ptL, ptR, Scalar(255, 0, 0));
		imshow("ԭͼ", imageSourceCopy);
	}
	if (event == EVENT_LBUTTONUP)//�ɿ�
	{
		if (ptL != ptR)
		{
			ROI = imageSource(Rect(ptL, ptR));
			imshow("ROI", ROI);
			imwrite("roi.jpg", ROI);
			waitKey();
		}
	}
	//��������Ҽ���ʼͼ���޸�
	if (event == EVENT_RBUTTONDOWN)
	{
		imageSourceCopy = ROI.clone();
		Mat imageGray;

		cvtColor(ROI, imageGray, COLOR_BGR2GRAY); //ת��Ϊ�Ҷ�ͼ

		GaussianBlur(imageGray, imageGray, Size(3, 3), 3, 3);//��˹�˲�
		Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));


		//ͨ����ֵ��������Mask
		threshold(imageGray, imageMask, 240, 255, THRESH_OTSU);
		Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imageMask, imageMask, Kernel);  //��Mask���ʹ���
		inpaint(ROI, imageMask, ROI, 1, INPAINT_NS);  //ͼ���޸�
		imshow("Mask", imageMask);
		imshow("�޸���", imageSource);
		imwrite("Mask.jpg", imageMask);
		imwrite("�޸���.jpg", imageSource);
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
//merge(imageRGB, 3, imageSource);//ͼƬ��ǿ
	if (!imageSource.data)
	{
		return -1;
	}
	imshow("ԭͼ", imageSource);
	setMouseCallback("ԭͼ", OnMouse);
	waitKey();
}


//ȫ������ֵ����+Mask���ʹ���
//int main()
//{
//	Mat imageSource = imread("1.jpg");
//	if (!imageSource.data)
//	{
//		return -1;
//	}
//	imshow("ԭͼ", imageSource);
//	Mat imageGray;
//	//ת��Ϊ�Ҷ�ͼ
//	cvtColor(imageSource, imageGray, COLOR_BGR2GRAY, 0);
//	Mat imageMask = Mat(imageSource.size(), CV_8UC1, Scalar::all(0));
//
//	//ͨ����ֵ��������Mask
//	threshold(imageGray, imageMask, 250, 255, 0);
//	Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//	//��Mask���ʹ�������Mask���
//	dilate(imageMask, imageMask, Kernel);
//
//	//ͼ���޸�
//	inpaint(imageSource, imageMask, imageSource, 10, INPAINT_NS);
//	imshow("Mask", imageMask);
//	imshow("�޸���", imageSource);
//	waitKey(0);
//}
