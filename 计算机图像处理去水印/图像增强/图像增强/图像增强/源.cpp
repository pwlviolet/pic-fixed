#include <opencv2/highgui/highgui.hpp>      
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
	Mat image = imread("灰度图.jpg");
	if (image.empty())
	{
		cout << "没有这张图" <<endl;
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
	imshow("增强后", image);
	imwrite("图片增强后.jpg", image);
	waitKey(0);
	return 0;
}