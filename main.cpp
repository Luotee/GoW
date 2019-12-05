#include <cstdio>
#include "capture_img.h"
//#include "img_to_2D_array.h"

using namespace std;

int main()
{
    //capture the game screen
    CaptureImg *capture_screen = new CaptureImg();
    capture_screen->capture();
    delete capture_screen;

    //convert the img to array
    //OpencvHp *convert_img_to_array = new OpencvHp();
    //convert_img_to_array->img2array();
    //delete convert_img_to_array;

    //test
    //printf("test121432321\n");
}