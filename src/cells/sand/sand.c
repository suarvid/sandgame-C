#include "sand.h"
#include "../cell.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

cell_t *create_sand_cell()
{
  cell_t *cell_p = malloc(sizeof(struct cell));

  cell_p->color = YELLOW;
  cell_p->lifetime = -1;
  cell_p->velocity = 1;
  cell_p->type = SAND;
  cell_p->updated = false;
  cell_p->update_function = update_sand;

  return cell_p;
}

void insert_sand(cell_t ***world, int16_t row,
                 int16_t col)
{
  cell_t *new_sand_cell = create_sand_cell();
  world[row][col] = new_sand_cell;
}

void update_sand(cell_t ***world, cell_t *self, int16_t row, int16_t col)
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
