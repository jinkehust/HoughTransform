#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
using namespace std;
using namespace cv;

int main()
{
	Mat Image = imread("picture.jpg");
	Mat CannyImage, GrayImage,GaussImage;
	cvtColor(Image, GrayImage, CV_RGB2GRAY);
	GaussianBlur(GrayImage, GaussImage, Size(3, 3), 0, 0);

	Canny(GaussImage, CannyImage, 60, 175);

	//霍夫变换
	vector<Vec2f> lines;
	HoughLines(CannyImage, lines, 1, CV_PI / 360, 100);  // 返回直线坐标对
	for (int i = 0; i<lines.size(); i++) 
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = rho*a;
		double y0 = rho*b;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * a);
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * a);
		line(GaussImage, pt1, pt2, Scalar(255, 0, 0), 4);
	}



	namedWindow("CannyImage");
	imshow("CannyImage", GaussImage);

	waitKey();
	return 0;
}
