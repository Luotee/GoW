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
    /*
    Search *best_path = new Search();
    best_path->find_best_move(chessboard);
    delete best_path;
    printf("Best move is (%u, %u) go ", best_path->best.x, best_path->best.y);
    switch(best_path->best.direction)
    {
        case 0 : printf("right, "); break;
        case 1 : printf("down, "); break;
    }
    printf("score is %d\n", best_path->best.score);
   
    //convert the img to array
    OpencvHp *draw_arrow = new OpencvHp();
    draw_arrow->show_answer(best_path->best.x, best_path->best.y, best_path->best.direction);
    delete draw_arrow;
    */
    return 0;
}