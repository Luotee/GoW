#include <cstdio>
#include "capture_img.h"

using namespace std;

int main()
{
    //capture the game screen
    CaptureImg *save_screen = new CaptureImg();
    save_screen->capture();
    delete save_screen;

    //test
    printf("test121432321\n");
}