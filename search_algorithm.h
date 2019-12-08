#ifndef SEARCH_ALGORITHM_H
#define SEARCH_ALGORITHM_H

#include <iostream>
#include <cstdio>

using namespace std;

class Search {

    public:
        void runestone_match(uint_fast8_t chessboard[8][8]);
        typedef struct queue
        {
            uint_fast8_t x;
            uint_fast8_t y;
            struct queue *next;
        }Queue;
        Queue *que_head, *que_front, *que_back;

        uint_fast8_t copy_board[8][8];
        uint_fast8_t temp_board[8][8];

        uint_fast8_t combo  =0;
        uint_fast8_t head   =0;
        uint_fast8_t blue   =0;
        uint_fast8_t Green  =0;
        uint_fast8_t red    =0;
        uint_fast8_t yellow =0;
        uint_fast8_t purple =0;
        uint_fast8_t brown  =0;
        uint_fast8_t bomb   =0;

    private:
        void Queue_init(uint_fast8_t x, uint_fast8_t y);
        void Queue_push(uint_fast8_t x, uint_fast8_t y);
        void Queue_pop();
        void print_board(uint_fast8_t chessboard[8][8]);
        void swap_runestone(uint_fast8_t *pos1, uint_fast8_t *pos2);
        void drop_board();

};





#endif /* SEARCH_ALGORITHM_H */