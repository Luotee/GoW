#ifndef SEARCH_ALGORITHM_H
#define SEARCH_ALGORITHM_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Search {

    public:
        void find_best_move(uint_fast8_t chessboard[8][8]);
        void runestone_match(uint_fast8_t chessboard[8][8]);
        typedef struct queue
        {
            uint_fast8_t x;
            uint_fast8_t y;
            struct queue *next;
        }Queue;
        Queue *que_head, *que_front, *que_back;

        typedef struct process
        {
            uint_fast8_t x=0;
            uint_fast8_t y=0;
            uint_fast8_t direction=0;
            int score=0;
            int enemy_score=0;
        }Process;

        uint_fast8_t copy_board[8][8];
        uint_fast8_t temp_board[8][8];
        uint_fast8_t bomb_board[8][8];
        uint_fast8_t next_board[8][8];

        uint_fast8_t combo  =0;
        uint_fast8_t head   =0;
        uint_fast8_t blue   =0;
        uint_fast8_t Green  =0;
        uint_fast8_t red    =0;
        uint_fast8_t yellow =0;
        uint_fast8_t purple =0;
        uint_fast8_t brown  =0;
        uint_fast8_t bomb   =0;

        int score =0;
        Process current_path;
        vector<Process> all_path;

    private:
        void Queue_init(uint_fast8_t x, uint_fast8_t y);
        void Queue_push(uint_fast8_t x, uint_fast8_t y);
        void Queue_pop();
        void print_board(uint_fast8_t chessboard[8][8]);
        void swap_runestone(uint_fast8_t *pos1, uint_fast8_t *pos2);
        void drop_board();
        void bomb_area(uint_fast8_t x, uint_fast8_t y);
        static bool compare_score(Process x, Process y);
};





#endif /* SEARCH_ALGORITHM_H */