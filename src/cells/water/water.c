#include "water.h"
#include "../cell.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

cell_t *create_water_cell()
{
  cell_t *cell_p = malloc(sizeof(struct cell));

  cell_p->color = BLUE;
  cell_p->lifetime = -1;
  cell_p->velocity = 1;
  cell_p->type = WATER;
  cell_p->updated = false;
  cell_p->update_function = update_water;

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
  if (row + 1 < WORLD_SIZE)
  {
    if (world[row + 1][col]->type == EMPTY) // Check down
    {
      world[row + 1][col] = self;
      world[row][col] = create_empty_cell(row, col);
      return;
    }

    if (col - 1 >= 0 && world[row + 1][col - 1]->type == EMPTY) // Check down-left
    {
      world[row + 1][col - 1] = self;
      world[row][col] = create_empty_cell(row, col);
      return;
    }

    if (col + 1 < WORLD_SIZE && world[row + 1][col + 1]->type == EMPTY) // Check down-right
    {
      world[row + 1][col + 1] = self;
      world[row][col] = create_empty_cell(row, col);
      return;
    }
  }
}
