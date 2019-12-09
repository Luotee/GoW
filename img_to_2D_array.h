#ifndef IMG_TO_2D_ARRAY_H
#define IMG_TO_2D_ARRAY_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define RESIZE_SCALING 2.4
#define GRID_SIZE (108.5/RESIZE_SCALING)
#define CHESSBOARD_X (533/RESIZE_SCALING)
#define CHESSBOARD_Y (113/RESIZE_SCALING)
#define circle_thickness (GRID_SIZE/10.0)
#define circle_radius (GRID_SIZE/4.5)

//int mouseInputs;

class OpencvHp {

    public:
        void img2array(uint_fast8_t chessboard[8][8]);
        void show_answer(uint_fast8_t x, uint_fast8_t y, int direction);

    private:
        void showimg(string windowname, const Mat &img, int x, int y);
        uint_fast8_t knn(uint_fast8_t b, uint_fast8_t g, uint_fast8_t r);
        static void CallBackFunc(int event, int x, int y, int flags, void* userdata);//must be static
        void user_modify_board(int mouse_x, int mouse_y, uint_fast8_t chessboard[8][8], const Mat &img);

};


#endif /* IMG_TO_2D_ARRAY_H */