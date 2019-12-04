#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define RESIZE_SCALING 2.4
#define GRID_SIZE 108.3/RESIZE_SCALING
#define CHESSBOARD_X 535/RESIZE_SCALING
#define CHESSBOARD_Y 117/RESIZE_SCALING


void showimg(string windowname, const Mat &img, int x, int y);

int main()
{
    //讀取圖片
    Mat img = imread(".\\hp.bmp");
    imwrite(".\\hp_png.png", img);
    img = imread(".\\hp_png.png");
    //因windows scaling，將圖片縮小
    resize(img, img, Size(img.cols/RESIZE_SCALING, img.rows/RESIZE_SCALING));
    namedWindow("image", WINDOW_NORMAL);
    resizeWindow("image", img.cols, img.rows);
	moveWindow("image", 0, 0);
    imshow("image", img);

    //標示棋盤
    line(//top line
        img, 
        Point2f(CHESSBOARD_X, CHESSBOARD_Y),
        Point2f((CHESSBOARD_X+8*GRID_SIZE), CHESSBOARD_Y), 
        Scalar(0,255,0), 1
    );
    line(//left line
        img, 
        Point2f(CHESSBOARD_X, CHESSBOARD_Y), 
        Point2f(CHESSBOARD_X, (CHESSBOARD_Y+8*GRID_SIZE)), 
        Scalar(0,255,0), 1
    );
    line(//bottom line
        img, 
        Point2f(CHESSBOARD_X, (CHESSBOARD_Y+8*GRID_SIZE)), 
        Point2f((CHESSBOARD_X+8*GRID_SIZE), (CHESSBOARD_Y+8*GRID_SIZE)), 
        Scalar(0,255,0), 1
    );
    line(//right line
        img, 
        Point2f((CHESSBOARD_X+8*GRID_SIZE), CHESSBOARD_Y), 
        Point2f((CHESSBOARD_X+8*GRID_SIZE), (CHESSBOARD_Y+8*GRID_SIZE)), 
        Scalar(0,255,0), 1
    );
    int i, j;
    float x, y;
    /*for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            circle(img, Point2f(CHESSBOARD_X+j*GRID_SIZE, CHESSBOARD_Y+i*GRID_SIZE), 3, Scalar(0,0,255), 2);
        }
    }*/
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            x=GRID_SIZE/2+CHESSBOARD_X+j*GRID_SIZE;
            y=GRID_SIZE/2+CHESSBOARD_Y+i*GRID_SIZE;
            circle(img, Point2f(x, y), 3, Scalar(0,0,255), 2);
            printf("%d : %u\n",i*8+j+1,img.at<Vec3b>(Point(x,y))[0]);
        }
    }
    //circle(img, Point2f(CHESSBOARD_X+GRID_SIZE/3, CHESSBOARD_Y+GRID_SIZE/1.5), 3, Scalar(0,0,0), 2);
    //putText(img, "X", Point2f(CHESSBOARD_X+GRID_SIZE/3, CHESSBOARD_Y+GRID_SIZE/1.5), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, LINE_AA);
    namedWindow("test", WINDOW_NORMAL);
    resizeWindow("test", img.cols, img.rows);
    imshow("test", img);
    
    //showimg("test2",img,0,0);

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