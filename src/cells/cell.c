#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "raylib.h"
#include "cell.h"

cell_t create_empty_cell(int row, int col)
{

    cell_t empty_cell = {.updated = false, .velocity = 0, .lifetime = -1, .color = BLACK, .type = EMPTY, empty_update_function};

    return empty_cell;
}

void empty_update_function(struct cell** cell_pp, int16_t row, int16_t col)
{
}
