#include "search_algorithm.h"

void Search::runestone_match(uint_fast8_t chessboard[8][8])
{
    uint_fast8_t x,y,i,j;
    uint_fast8_t runestone;
    uint_fast8_t combo_without_drop=0;

    memcpy(copy_board, chessboard, sizeof(copy_board));
    memcpy(temp_board, chessboard, sizeof(temp_board));

    for(i=0;i<=8;i++)
    {
        for(j=0;j<=8;j++)
        {
            if(copy_board[j][i]=='.') continue; //if this coordinate already matched : skip
            uint_fast8_t same_color_runestone = 0;
            runestone = temp_board[j][i]; //take this coordinate 
            Queue_init(j,i); //put first member in to the que
            while(que_front!=NULL)
            {
                x = que_front->x; //take first member x
                y = que_front->y; //take first member y
                if(copy_board[x][y]=='.') //skip the repeat
                {
                    Queue_pop();
                    continue;
                }
                bool passport=0;
                //judge this runestone : 1 case met then pass other
                if(x-1>=0 && temp_board[x-1][y]==runestone && x-2>=0 && temp_board[x-2][y]==runestone) { copy_board[x][y]='.'; passport=1; }
                else if(x+1<=7 && temp_board[x+1][y]==runestone && x+2<=7 && temp_board[x+2][y]==runestone) { copy_board[x][y]='.'; passport=1; }
                else if(y-1>=0 && temp_board[x][y-1]==runestone && y-2>=0 && temp_board[x][y-2]==runestone) { copy_board[x][y]='.'; passport=1; }
                else if(y+1<=7 && temp_board[x][y+1]==runestone && y+2<=7 && temp_board[x][y+2]==runestone) { copy_board[x][y]='.'; passport=1; }
                else if(x-1>=0 && x+1<=7 && temp_board[x-1][y]==runestone && temp_board[x+1][y]==runestone) { copy_board[x][y]='.'; passport=1; }
                else if(y-1>=0 && y+1<=7 && temp_board[x][y-1]==runestone && temp_board[x][y+1]==runestone) { copy_board[x][y]='.'; passport=1; }
                //push possible match to que 
                if(passport)
                {
                    same_color_runestone++;
                    if(x-1>=0 && copy_board[x-1][y]==runestone) { Queue_push(x-1,y); }
                    if(x+1<=7 && copy_board[x+1][y]==runestone) { Queue_push(x+1,y); }
                    if(y-1>=0 && copy_board[x][y-1]==runestone) { Queue_push(x,y-1); }
                    if(y+1<=7 && copy_board[x][y+1]==runestone) { Queue_push(x,y+1); }
                }
                //remove first member
                Queue_pop();
            }
            if(same_color_runestone>=3)
            {
                combo++;
                switch(runestone)
                {
                    case '0' : head     += 1; break;
                    case '1' : blue     += 1; break;
                    case '2' : Green    += 1; break;
                    case '3' : red      += 1; break;
                    case '4' : yellow   += 1; break;
                    case '5' : purple   += 1; break;
                    case '6' : brown    += 1; break;
                    case '7' : bomb     += 1; break;
                }
            
            }
        }
    }

    /*if(combo_without_drop)
    {
        //print_board(copy_board);
        drop_board(); //drop function call
    }
    runestone_drop_match();*/

    
    
}

void Search::Queue_init(uint_fast8_t x, uint_fast8_t y)
{
    free(que_head);//very impotant!!! free last head memory
    Queue *first_member;
    que_head = (Queue*)malloc(sizeof(Queue));
    first_member = (Queue*)malloc(sizeof(Queue));
    first_member->x = x;
    first_member->y = y;
    first_member->next = NULL;
    que_head->next = first_member;
    que_front = first_member;
    que_back = first_member;
}
void Search::Queue_push(uint_fast8_t x, uint_fast8_t y)
{
    Queue *new_que_member; //declare a new que member
    new_que_member = (Queue*)malloc(sizeof(Queue));
    new_que_member->x = x;
    new_que_member->y = y;
    new_que_member->next = NULL;
    que_back->next = new_que_member;
    que_back = new_que_member;
}
void Search::Queue_pop()
{
    Queue *del_que_member;
    del_que_member = que_front;
    que_front = que_front->next;
    free(del_que_member);
}