#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


struct cell{
    int x;
    int y;
    int glucose;
    char* name;
    struct cell* next_cell;
    int index;//yadet bashe ke ino har dafe ke ye chizi jadid be list ezafe ya hazf mikoni bayad set koni
};



char* give_name_rand(int size_name);//ye esm ba size gofte shode behet mide

char* give_your_name(int size_name);//ye esm ba size gofte shode behet mide

void print_my_cells(struct cell* head_list, int player, int colors[6]);

struct cell* mitosis();
struct cell* create_n_cells(int num_cells, int create_name, int player_num,int size_game,int**map_bin, int** game_board);
//tabeye bala ro bayad bad az map handler seda kard chon ke bayd game_board 0 bashe hameye khunehash az unjayi ke in tabe
// x va y cell hayi ke misze ro ham tuye game_board vared mikone
void check_move(int index_cell, struct cell* head_of_list, int direction, int player, int size_game,  int** game_board, int** map_bin);
void Move(int index_cell, struct cell* head_of_list, int player, int size_game, int** game_board,int** map_bin);
void delete(struct cell** pointer_head, struct cell* be_remove);
void refresh_game_board(struct cell* head1, struct cell* head2, int** game_board, int size_game);
void refresh_indexes(struct cell* head);
void Split(int index_cell, struct cell** head_of_list, int player, int** map_bin, int size_game, int**game_board);
void BoostEnergy(int index_cell, struct cell* head_of_list, int player, int**map_bin, int** game_board, int num_boost_blocks, int** boostup_blocks);