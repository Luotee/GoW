#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main()
{
    //讀取圖片
    Mat img=imread(".\\hp.bmp");
    //因windows scaling
    resize(img, img, Size(800, 450), 0, 0, INTER_LINEAR);
    namedWindow("image");
	moveWindow("image", 0, 0);
    imshow("image",img);
    waitKey();
    return 0;
}
