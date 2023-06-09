#pragma once
#include "../../constants.h"
#include "../cell.h"
#include <stdbool.h>

void insert_wood(cell_t ***world, int16_t row, int16_t col);
void update_wood(cell_t ***world, cell_t *self, int16_t row, int16_t col);