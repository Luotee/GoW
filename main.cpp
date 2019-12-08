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
    
    FILE *file_in;
    file_in = fopen("test.txt","r");
    uint_fast8_t board[8][8], runestone;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            fscanf(file_in," %c",&runestone);//" %c" : the space means ignore [\n,tab,space]
            board[j][i] = runestone;
        }
    }
    
    
    Search *best_path = new Search();
    best_path->runestone_match(board);
    delete best_path;
    printf("%8s%8s%8s%8s%8s%8s%8s%8s | %8s\n","head","blue","Green","red","yellow","purple","brown","bomb","combo");
    printf("%8d%8d%8d%8d%8d%8d%8d%8d | %8d\n",best_path->head,best_path->blue,best_path->Green,best_path->red,best_path->yellow,best_path->purple,best_path->brown,best_path->bomb,best_path->combo);

    /*for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            printf("%c ", board[j][i]);//" %c" : the space means ignore [\n,tab,space]
        }
        putchar(10);
    }*/
    //test
    /*printf("=========main function=========\n");
    int i, j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%c ",chessboard[j][i]);
        }
        putchar(10);
    }*/
    

}