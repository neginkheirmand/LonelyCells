#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

typedef enum {
 ENERGY = 1,
 MITOSIS,
 FORBIDDEN,
 NORMAL
} blocks;


void print_block_energies(int** boostup_blocks, int num_boostup_blocks);

void print_energy_line(int line, int j, int energy_left, int num_digit);

int energy_left(int i, int j, int num_boostup_blocks, int** boostup_blocks);

void print(int size_game, int**map_bin, int**game_board, int colors[6], int num_boostup_blocks, int** boostup_blocks);

int millisleep(unsigned ms);
