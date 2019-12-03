#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main()
{
    Mat img=imread(".\\lenna.png");
    imshow("image",img);
    waitKey();
    return 0;
}
