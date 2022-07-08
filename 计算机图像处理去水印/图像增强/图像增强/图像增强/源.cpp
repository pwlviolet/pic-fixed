#include <opencv2/highgui/highgui.hpp>      
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
	Mat image = imread("�Ҷ�ͼ.jpg");
	if (image.empty())
	{
		cout << "û������ͼ" <<endl;
		return -1;
	}
	imshow("img", image);
	Mat imageRGB[3];
	split(image, imageRGB);
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(imageRGB[i], imageRGB[i]);
	}
	merge(imageRGB, 3, image);
	imshow("��ǿ��", image);
	imwrite("ͼƬ��ǿ��.jpg", image);
	waitKey(0);
	return 0;
}