#include "water.h"
#include "../cell.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void update_water_falling(cell_t ***world, cell_t *self, int16_t row, int16_t col);
void update_water_on_ground(cell_t ***world, cell_t *self, int16_t row, int16_t col);
static bool move_down_left(cell_t ***world, cell_t *self, int16_t row, int16_t col);
static bool move_down_right(cell_t ***world, cell_t *self, int16_t row, int16_t col);
static bool move_down(cell_t ***world, cell_t *self, int16_t row, int16_t col);

cell_t *create_water_cell()
{
    cell_t *cell_p = malloc(sizeof(struct cell));

    cell_p->color = BLUE;
    cell_p->lifetime = -1;
    cell_p->velocity = 1;
    cell_p->type = WATER;
    cell_p->updated = false;
    cell_p->update_function = update_water;
    cell_p->density = 1;
    return cell_p;
}

void insert_water(cell_t ***world, int16_t row,
                  int16_t col)
{
    cell_t *new_water_cell = create_water_cell();
    world[row][col] = new_water_cell;
}

void update_water(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
    if (row + 1 == WORLD_SIZE || (row + 1 < WORLD_SIZE && world[row + 1][col]->density >= self->density))
    {
        update_water_on_ground(world, self, row, col);
    } else {
        update_water_falling(world, self, row, col);
    }
}

void update_water_falling(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
    // Check down
    if (row + 1 < WORLD_SIZE)
    {
        if (!move_down(world, self, row, col))
        {
            int r = rand() % 2;

            if (r == 0)
            {
                if (!move_down_left(world, self, row, col))
                {
                    move_down_right(world, self, row, col);
                }
            }
            else
            {
                if (!move_down_right(world, self, row, col))
                {
                    move_down_left(world, self, row, col);
                }
            }
        }
    }
}

static bool move_down_left(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
    if (col - 1 >= 0)
    {
        cell_t *down_left = world[row + 1][col - 1];
        if (down_left->type == EMPTY || down_left->density < self->density) // Check down-left
        {
            world[row + 1][col - 1] = self;
            world[row][col] = create_empty_cell(row, col);
            return true;
        }
    }

    return false;
}

static bool move_down_right(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
    if (col + 1 < WORLD_SIZE)
    {
        cell_t *down_right = world[row + 1][col + 1];
        if (down_right->type == EMPTY || down_right->density < self->density) // Check down-right
        {
            world[row + 1][col + 1] = self;
            world[row][col] = create_empty_cell(row, col);
            return true;
        }
    }

    return false;
}

static bool move_down(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
    cell_t *down = world[row + 1][col];
    if (down->type == EMPTY || down->density < self->density) // Check down
    {
        world[row + 1][col] = self;
        world[row][col] = create_empty_cell(row, col);
        return true;
    }

    return false;
}

void update_water_on_ground(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
    // Check Right
    if (col + 1 < WORLD_SIZE && world[row][col + 1]->type == EMPTY)
    {
        world[row][col + 1] = self;
        world[row][col] = create_empty_cell(row, col);
    }

    // Check Left
    else if (col - 1 >= 0 && world[row][col - 1]->type == EMPTY)
    {
        world[row][col - 1] = self;
        world[row][col] = create_empty_cell(row, col);
    }
}