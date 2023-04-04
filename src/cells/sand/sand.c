#include "sand.h"
#include "../cell.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static bool move_down_left(cell_t ***world, cell_t *self, int16_t row, int16_t col);
static bool move_down_right(cell_t ***world, cell_t *self, int16_t row, int16_t col);
static bool move_down(cell_t ***world, cell_t *self, int16_t row, int16_t col);

cell_t *create_sand_cell()
{
  cell_t *cell_p = malloc(sizeof(struct cell));

  cell_p->color = YELLOW;
  cell_p->lifetime = -1;
  cell_p->velocity = 1;
  cell_p->type = SAND;
  cell_p->updated = false;
  cell_p->update_function = update_sand;
  cell_p->density = 2;

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
  for (int move = 0; move < self->velocity; move++)
  {

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

static bool move_down_left(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
  cell_t *down_left = world[row + 1][col - 1];
  if (col - 1 >= 0 && down_left->type == EMPTY || down_left->density < self->density) // Check down-left
  {
    world[row + 1][col - 1] = self;
    world[row][col] = create_empty_cell(row, col);
    return true;
  }

  return false;
}

static bool move_down_right(cell_t ***world, cell_t *self, int16_t row, int16_t col)
{
  cell_t *down_right = world[row + 1][col + 1];
  if (col + 1 < WORLD_SIZE && down_right->type == EMPTY || down_right->density < self->density) // Check down-right
  {
    world[row + 1][col + 1] = self;
    world[row][col] = create_empty_cell(row, col);
    return true;
  }

  return false;
}