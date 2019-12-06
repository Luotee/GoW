#include "img_to_2D_array.h"

#define RESIZE_SCALING 2.4
#define GRID_SIZE 108.3/RESIZE_SCALING
#define CHESSBOARD_X 535/RESIZE_SCALING
#define CHESSBOARD_Y 117/RESIZE_SCALING

/*
void img2array();
void showimg(string windowname, const Mat &img, int x, int y);
uint_fast8_t knn(uint_fast8_t b, uint_fast8_t g, uint_fast8_t r);
*/

void OpencvHp::img2array(uint_fast8_t chessboard[8][8])
{
    //讀取圖片
    Mat img = imread(".\\screen.bmp");

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
    char *text;
    
    uint_fast8_t g, b, r;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            x=GRID_SIZE/2+CHESSBOARD_X+j*GRID_SIZE;
            y=GRID_SIZE/2+CHESSBOARD_Y+i*GRID_SIZE;
            //circle(img, Point2f(x, y), 3, Scalar(0,0,255), 2);
            
            b = img.at<Vec3b>(Point(x,y))[0];
            g = img.at<Vec3b>(Point(x,y))[1];
            r = img.at<Vec3b>(Point(x,y))[2];

            chessboard[j][i] = knn(b,g,r);

            switch(chessboard[j][i])
            {
                case '0' : rectangle(img, Point2f(x-GRID_SIZE/3, y-GRID_SIZE/3), Point(x+GRID_SIZE/3,y+GRID_SIZE/3), Scalar(255,255,255), 3); break;
                case '1' : circle(img, Point2f(x, y), 10, Scalar(255,0,0), 5); break;
                case '2' : circle(img, Point2f(x, y), 10, Scalar(0,255,0), 5); break;
                case '3' : circle(img, Point2f(x, y), 10, Scalar(0,0,255), 5); break;
                case '4' : circle(img, Point2f(x, y), 10, Scalar(0,255,255), 5); break;
                case '5' : circle(img, Point2f(x, y), 10, Scalar(255,0,255), 5); break;
                case '6' : circle(img, Point2f(x, y), 10, Scalar(21,0,136), 5); break;
                case '7' : rectangle(img, Point2f(x-GRID_SIZE/3, y-GRID_SIZE/3), Point(x+GRID_SIZE/3,y+GRID_SIZE/3), Scalar(150,150,255), 3); break;
                default : putText(img, "?", Point2f(x, y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, LINE_AA);
            }
        }
    }
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%c ",chessboard[j][i]);
        }
        putchar(10);
    }
    //putText(img, "X", Point2f(CHESSBOARD_X+GRID_SIZE/3, CHESSBOARD_Y+GRID_SIZE/1.5), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, LINE_AA);
    namedWindow("mark", WINDOW_NORMAL);
    resizeWindow("mark", img.cols, img.rows);
    imshow("mark", img);
    
    waitKey();
}

void OpencvHp::showimg(string windowname, const Mat &img, int x, int y)
{
	namedWindow(windowname, WINDOW_NORMAL);
	imshow(windowname, img);
	resizeWindow(windowname, 480, 270);
	moveWindow(windowname, x, y);
}

uint_fast8_t OpencvHp::knn(uint_fast8_t b, uint_fast8_t g, uint_fast8_t r)
{
    uint_fast8_t b_arr[8]={187,235,55,52,130,160,66,160};
    uint_fast8_t g_arr[8]={195,207,183,50,223,14,69,176};
    uint_fast8_t r_arr[8]={202,74,78,217,251,78,107,225};
    int i;
    uint_fast8_t min_target;
    double min_distance = 1000.0;
    double distance;
    double x=1/3.0;

    for(i=0;i<8;i++)
    {
        distance = pow(
            (
                (b-b_arr[i])*(b-b_arr[i])+
                (g-g_arr[i])*(g-g_arr[i])+
                (r-r_arr[i])*(r-r_arr[i])
            ),
            x
        );
        if(distance < min_distance)
        {
            min_distance = distance;
            min_target = i+'0';
        }
    }
    return min_target;
}