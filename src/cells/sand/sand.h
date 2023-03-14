#pragma once
#include "../../constants.h"
#include "../cell.h"

void insert_sand(cell_t ***world, int16_t row, int16_t col);

cell_t* create_sand_cell();
void update_sand(cell_t ***world, cell_t *self, int16_t row, int16_t col);