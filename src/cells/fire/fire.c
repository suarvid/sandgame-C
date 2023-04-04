#include "fire.h"
#include <stdlib.h>
#include "../cell.h"
#include "../../utils.h"

cell_t *create_fire_cell()
{
    cell_t *cell_p = malloc(sizeof(struct cell));

    int r = rand() % 3;
    if (r == 0)
        cell_p->color = RED;
    else if (r == 1)
        cell_p->color = ORANGE;
    else
        cell_p->color = YELLOW;

    cell_p->lifetime = 25;
    cell_p->velocity = 0;
    cell_p->type = FIRE;
    cell_p->updated = false;
    cell_p->update_function = update_fire;
    cell_p->density = 0;

    return cell_p;
}

void update_fire(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (out_of_bounds(row + r - 1, col + c - 1))
                continue;

            // if adjacent cell is wood, burn
            if (world[row + r - 1][col + c - 1]->type == WOOD)
            {
                free(world[row + r - 1][col + c - 1]);
                cell_t *new_fire_cell = create_fire_cell();
                insert_fire(world, row + r - 1, col + c - 1);
                // this should also create a smoke cell
            }

            // if adjacent cell is empty, spread
            if (world[row + r -1][col + c - 1]->type == EMPTY)
            {
                int r = rand() % FIRE_SPREAD_RAND_CONST;
                if (r == 0)
                {
                    free(world[row + r - 1][col + c - 1]);
                    cell_t *new_fire_cell = create_fire_cell();
                    insert_fire(world, row + r - 1, col + c - 1);
                }
            }

            if (world[row + r -1][col + c - 1]->type == WATER)
            {
                world[row][col]->lifetime = 0;
                break;
                // should also create a steam cell?
            }
            // if adjacent cell is water, evaporate
            // if adjacent cell is fire, spread
            // should spread upwards, then left, then right, then down
        }
    }
}

void insert_fire(cell_t ***world, int16_t row, int16_t col)
{
    cell_t *new_fire_cell = create_fire_cell();
    world[row][col] = new_fire_cell;
}