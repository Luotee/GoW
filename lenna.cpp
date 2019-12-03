#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define RESIZE_SCALING 2.4
#define GRID_SIZE 113
#define CHESSBOARD_X 553
#define CHESSBOARD_Y 121


void showimg(string windowname, const Mat &img, int x, int y);

int main()
{
    //讀取圖片
    Mat img = imread(".\\hp.bmp");
    //因windows scaling，將圖片縮小
    resize(img, img, Size(img.cols/RESIZE_SCALING, img.rows/RESIZE_SCALING));
    namedWindow("image");
	moveWindow("image", 0, 0);
    imshow("image", img);

    //灰階
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    showimg("1_gray", gray, 0, 0);

    //平滑
	Mat Gaussianblur;
	GaussianBlur(gray, Gaussianblur, Size(5,5), 0, 0);
	showimg("2_Gaussianblur", Gaussianblur, 480, 0);

    //邊緣
	Mat canny;
	Canny(gray, canny, 75, 200);
	showimg("3_canny", canny, 0, 270);

    //test
    Mat test_img(400, 400, CV_8UC3, Scalar(255,255,255));
    line(test_img, Point(20,40), Point(120,140), Scalar(255,0,0), 3);
    rectangle(test_img, Point(150,40), Point(250,140), Scalar(0,0,255), -1);
    circle(test_img, Point(330,90), 50, Scalar(0,255,0), -1);
    ellipse(test_img, Point(80,280), Size(60,40), 45, 0, 360, Scalar(255,255,0), 2);

    showimg("4_test", test_img, 480, 270);

    waitKey();
    return 0;
}

void showimg(string windowname, const Mat &img, int x, int y)
{
	namedWindow(windowname, WINDOW_NORMAL);
	imshow(windowname, img);
	resizeWindow(windowname, 480, 270);
	moveWindow(windowname, x, y);
}