#ifndef IMG_TO_2D_ARRAY_H
#define IMG_TO_2D_ARRAY_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class OpencvHp {

    public:
        void img2array();

    private:
        void showimg(string windowname, const Mat &img, int x, int y);
        uint_fast8_t knn(uint_fast8_t b, uint_fast8_t g, uint_fast8_t r);

};


#endif /* IMG_TO_2D_ARRAY_H */