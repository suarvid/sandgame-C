#pragma once
#include "cell.h"
#include "../../constants.h"

# define FIRE_SPREAD_RAND_CONST 250

void insert_fire(cell_t ***world, int16_t row, int16_t col);
void update_fire(cell_t ***world, cell_t *self, int16_t row, int16_t col);