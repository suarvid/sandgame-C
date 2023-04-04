#pragma once
#include "../../constants.h"
#include "../cell.h"
#include <stdbool.h>

cell_t* create_sand_cell();
void insert_sand(cell_t ***world, int16_t row, int16_t col);
void update_sand(cell_t ***world, cell_t *self, int16_t row, int16_t col);
bool try_add_down_left(cell_t ***world, cell_t *self, int16_t row, int16_t col);
bool try_add_down_right(cell_t ***world, cell_t *self, int16_t row, int16_t col);