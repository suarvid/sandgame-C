#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "cells/sand/sand.h"
#include "cells/cell.h"
#include "raylib.h"

cell_t** init_world();
void draw_world(cell_t** world, int height, int width);

int main(void)
{
    cell_t **world = init_world();


    //insert_sand(world, 100, 100);

    Vector2 insert_pos = {0.0, 0.0};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            insert_pos = GetMousePosition();
            insert_sand(world, (int) insert_pos.y, insert_pos.x);
            printf("Inserted Sand!");
        }

        BeginDrawing();

        draw_world(world, WORLD_SIZE, WORLD_SIZE);

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}

cell_t** init_world()
{

  cell_t **world = malloc(WORLD_SIZE * sizeof(cell_t*));
  for (int row = 0; row < WORLD_SIZE; row++)
  {
    world[row] = malloc(WORLD_SIZE * sizeof(cell_t));
    for (int col = 0; col < WORLD_SIZE; col++)
    {
        world[row][col] = create_empty_cell(row, col);

    }
  }

  return world;
}

void draw_world(cell_t** world, int height, int width)
{
    for (int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            cell_t cell = world[row][col];
            if (cell.type == SAND)
            {
                printf("FOUND SAND!\n");

            }
            DrawRectangle(row, col, 1, 1, cell.color);

        }
    }

}
