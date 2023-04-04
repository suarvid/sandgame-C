#include "wood.h"
#include <stdlib.h>
#include <stdbool.h>
#include "../cell.h"

cell_t *create_wood_cell()
{
    cell_t *cell_p = malloc(sizeof(struct cell));

    cell_p->color = BROWN;
    cell_p->lifetime = -1;
    cell_p->velocity = 0;
    cell_p->type = WOOD;
    cell_p->updated = false;
    cell_p->update_function = update_wood;
    cell_p->density = 2;

    return cell_p;
}

void insert_wood(cell_t ***world, int16_t row, int16_t col)
{
    cell_t *new_wood_cell = create_wood_cell();
    world[row][col] = new_wood_cell;
}

void update_wood(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
    // if adjacent cell is fire, burn
}