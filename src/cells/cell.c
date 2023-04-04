#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "raylib.h"
#include "cell.h"

cell_t *create_empty_cell(int row, int col)
{

    cell_t *empty_cell = malloc(sizeof(cell_t));
    empty_cell->updated = false;
    empty_cell->velocity = 0;
    empty_cell->color = BLACK;
    empty_cell->lifetime = -1,
    empty_cell->type = EMPTY;
    empty_cell->update_function = empty_update_function;
    empty_cell->density = -1;

    return empty_cell;
}

void empty_update_function(struct cell*** world, cell_t *self, int16_t row, int16_t col)
{
}
