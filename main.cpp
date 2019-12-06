#include <iostream>
#include <cstdio>
#include "capture_img.h"
#include "img_to_2D_array.h"
#include "search_algorithm.h"

using namespace std;

uint_fast8_t chessboard[8][8];

int main()
{
    //capture the game screen
    CaptureImg *capture_screen = new CaptureImg();
    capture_screen->capture();
    delete capture_screen;

    //convert the img to array
    OpencvHp *convert_img_to_array = new OpencvHp();
    convert_img_to_array->img2array(chessboard);
    delete convert_img_to_array;

    //DFS or BFS algorithm
    Search *best_path = new Search();
    


    //test
    printf("=========main function=========\n");
    int i, j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%c ",chessboard[j][i]);
        }
        putchar(10);
    }
    

}