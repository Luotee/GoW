#include "search_algorithm.h"

void Search::find_best_move(uint_fast8_t chessboard[8][8])
{
    int direction_x[2]={ 1, 0};
    int direction_y[2]={ 0, 1};
    uint_fast8_t nx, ny;
    uint_fast8_t i, j, k;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            for(k=0;k<2;k++)
            {
                nx = j + direction_x[k];
                ny = i + direction_y[k];
                //printf("nx = %u, ny = %u\n",nx,ny);
                if(nx>=8 || ny>=8) continue;
                swap_runestone(&chessboard[j][i], &chessboard[nx][ny]);
                score = 0;
                runestone_match(chessboard);
                //print_board(copy_board);
                if(score>best.score)
                {
                    best.x = j;
                    best.y = i;
                    best.direction = k;
                    best.score = score;
                }
                swap_runestone(&chessboard[j][i], &chessboard[nx][ny]);
            }
        }
    }
}

void Search::runestone_match(uint_fast8_t chessboard[8][8])
{
    uint_fast8_t x,y,i,j;
    uint_fast8_t runestone;
    uint_fast8_t combo_without_drop=0;

    //memcpy(copy_board, chessboard, sizeof(copy_board));
    memcpy(temp_board, chessboard, sizeof(temp_board));
    memcpy(bomb_board, chessboard, sizeof(bomb_board));

    for(i=0;i<=7;i++)
    {
        for(j=0;j<=7;j++)
        {
            if(temp_board[j][i]=='7') temp_board[j][i]='0';            
        }
    }
    memcpy(copy_board, temp_board, sizeof(copy_board));

    for(i=0;i<=7;i++)
    {
        for(j=0;j<=7;j++)
        {
            if(copy_board[j][i]=='.') continue; //if this coordinate already matched : skip
            uint_fast8_t same_color_runestone = 0;
            runestone = temp_board[j][i]; //take this color 
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
                //print_board(copy_board);
            }
            if(same_color_runestone>=3)
            {

                combo++;
                combo_without_drop++;
                if(same_color_runestone>=4)
                {
                    if(runestone=='0') score+=100;
                    else score+=10;
                }
                else
                {
                    if(runestone=='0') score+=5;
                    else score+=1;
                }
                
                /*switch(runestone)
                {
                    case '0' : head     += 1; break;
                    case '1' : blue     += 1; break;
                    case '2' : Green    += 1; break;
                    case '3' : red      += 1; break;
                    case '4' : yellow   += 1; break;
                    case '5' : purple   += 1; break;
                    case '6' : brown    += 1; break;
                    case '7' : bomb     += 1; break;
                }*/
            }
        }
    }
    for(i=0;i<=7;i++)
    {
        for(j=0;j<=7;j++)
        {
            if(copy_board[j][i]=='.' && bomb_board[j][i]=='7')
            {
                bomb_board[j][i]='.';
                printf("first area = %d %d\n",j,i);
                bomb_area(j, i);
            }
        }
    }
    for(i=0;i<=7;i++) for(j=0;j<=7;j++) if(copy_board[j][i]!='.' && bomb_board[j][i]=='7') copy_board[j][i]=='7';
    if(combo_without_drop)
    {
        //print_board(copy_board);
        drop_board(); //drop function call
        runestone_match(copy_board);
    }
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

void Search::print_board(uint_fast8_t chessboard[8][8])
{
    printf("========\n");
    uint_fast8_t i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%c ",chessboard[j][i]);
        }
        putchar(10);
    }
}

void Search::drop_board()
{
    //copy previous match board
    //memcpy(copy_board_2, copy_board, sizeof(copy_board));
    uint_fast8_t x, y;
    for(x=0;x<=7;x++)
    {
        uint_fast8_t buffer[8], runes_in_the_air=0;
        for(y=0;y<=7;y++)
        {
            if(copy_board[x][y]!='.')
            {
                buffer[runes_in_the_air]=copy_board[x][y];
                copy_board[x][y] = '.';
                runes_in_the_air++;
            }
        }
        switch(runes_in_the_air)
        {
            case 1 : memcpy(copy_board[x]+7,buffer,sizeof(uint_fast8_t[1])); break;
            case 2 : memcpy(copy_board[x]+6,buffer,sizeof(uint_fast8_t[2])); break;
            case 3 : memcpy(copy_board[x]+5,buffer,sizeof(uint_fast8_t[3])); break;
            case 4 : memcpy(copy_board[x]+4,buffer,sizeof(uint_fast8_t[4])); break;
            case 5 : memcpy(copy_board[x]+3,buffer,sizeof(uint_fast8_t[5])); break;
            case 6 : memcpy(copy_board[x]+2,buffer,sizeof(uint_fast8_t[6])); break;
            case 7 : memcpy(copy_board[x]+1,buffer,sizeof(uint_fast8_t[7])); break;
            case 8 : memcpy(copy_board[x],buffer,sizeof(uint_fast8_t[8])); break;
        }
    }
    //print_board(copy_board);
    memcpy(temp_board, copy_board, sizeof(copy_board));

}

void Search::bomb_area(uint_fast8_t x, uint_fast8_t y)
{
    int direction_x[8]={-1, 0, 1,-1, 1,-1, 0, 1};
    int direction_y[8]={-1,-1,-1, 0, 0, 1, 1, 1};
    int i,j,k;
    uint_fast8_t nx, ny;

    for(i=0;i<8;i++)
    {
        nx = x + direction_x[i];
        ny = y + direction_y[i];
        if(nx>=8 || ny>=8) continue;
        copy_board[nx][ny]='.';
        if(copy_board[nx][ny]=='.' && bomb_board[nx][ny]=='7')
        {
            printf("area = %u %u\n",nx,ny);
            bomb_board[nx][ny]='.';
            bomb_area(nx, ny);
        }
    }
}

void Search::swap_runestone(uint_fast8_t *pos1, uint_fast8_t *pos2)
{
    uint_fast8_t t = *pos1;
    *pos1 = *pos2;
    *pos2 = t;
}