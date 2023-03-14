#pragma once
#include "../../constants.h"
#include "../cell.h"

cell_t* create_water_cell();
void insert_water(cell_t ***world, int16_t row, int16_t col);
void update_water(cell_t ***world, cell_t *self, int16_t row, int16_t col);