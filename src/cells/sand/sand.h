#pragma once
#include "../../constants.h"
#include "../cell.h"

void insert_sand(cell_t world[WORLD_SIZE][WORLD_SIZE], int16_t row, int16_t col);

cell_t* create_sand_cell();