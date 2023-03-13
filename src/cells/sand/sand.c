#include "sand.h"
#include "../cell.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

cell_t *create_sand_cell() {
  cell_t *cell_p = malloc(sizeof(struct cell));

  cell_p->color = MAROON;
  cell_p->lifetime = -1;
  cell_p->velocity = 1;
  cell_p->type = SAND;
  cell_p->updated = false;
  cell_p->update_function = NULL;

  return cell_p;
}

void insert_sand(cell_t world[WORLD_SIZE][WORLD_SIZE], int16_t row,
                 int16_t col) {
  cell_t insert_point = world[row][col];

  if (insert_point.type == EMPTY) {
    cell_t *new_sand_cell = create_sand_cell();
    insert_point = *new_sand_cell;
    printf("Inserted Sand at row: %d, col: %d", row, col);
  }
}

void update_sand(cell_t **world, int16_t row, int16_t col) {
  // TODO: Move sand here
}
