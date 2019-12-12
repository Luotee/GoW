#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;
using namespace cv;



int main(int argc, char** argv)
{
    // Read image from file 
    Mat img = imread("cane.png",-1);
    resize(img, img, Size(img.cols/1.5, img.rows/1.5));

    //if fail to read the image
    if ( img.empty() ) 
    { 
        cout << "Error loading the image" << endl;
        return -1; 
    }
    /*Mat mask;
    vector<Mat> rgbLayer;
    split(img,rgbLayer);
    Mat cs[3] = { rgbLayer[0],rgbLayer[1],rgbLayer[2] };
    merge(cs,3,img);
    mask = rgbLayer[3];
    img.copyTo(img(cv::Rect(0,0,img.cols, img.rows)),mask);*/

    //Create a window
    namedWindow("Image", WINDOW_NORMAL);
    resizeWindow("Image", img.cols/1.5, img.rows/1.5);
    moveWindow("Image", 0, 0);

    //show the image
    imshow("Image", img);

    //Create a window
    namedWindow("Image2", WINDOW_NORMAL);
    resizeWindow("Image2", img.cols/1.5, img.rows/1.5);
    moveWindow("Image2", 100, 0);

    //show the image
    imshow("Image2", img);


    HWND hwnd = FindWindow(0, "Image");
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    long winLong = GetWindowLong(hwnd, GWL_EXSTYLE);
    style &= ~WS_OVERLAPPEDWINDOW;
    //style |= WS_POPUP;
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowLong(hwnd, GWL_EXSTYLE, winLong | WS_EX_LAYERED);

    SetLayeredWindowAttributes(hwnd, RGB(255,255,255), 0, LWA_COLORKEY);
    //HWND hwnd = FindWindow(0, "Image2");
    //SetLayeredWindowAttributes(hwnd, 0, (255*50)/100, LWA_ALPHA);
    printf("channel=%d",img.channels());
    waitKey(0);

    return 0;

}