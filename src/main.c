#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "cells/sand/sand.h"
#include "cells/water/water.h"
#include "cells/cell.h"
#include "raylib.h"
// Note to self: Raylib origin in top-left corner (as usual)

typedef void (*insert_cell_function_t)(cell_t***, int16_t, int16_t);

cell_t*** init_world();
void draw_world(cell_t*** world, int height, int width);
void update_cells(cell_t*** world, int height, int width);
insert_cell_function_t update_selected_cell_type(void (*insert_function)(cell_t***, int16_t, int16_t));

int main(void)
{

    cell_t ***world = init_world();
    void (*insert_function)(cell_t***, int16_t, int16_t) = insert_sand;

    Vector2 insert_pos = {0.0, 0.0};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        update_cells(world, WORLD_SIZE, WORLD_SIZE);
        insert_function = update_selected_cell_type(insert_function);

        if (IsKeyDown(KEY_SPACE)) {
            insert_pos = GetMousePosition();
            //insert_sand(world, (int) insert_pos.y, insert_pos.x);
            insert_function(world, (int) insert_pos.y, insert_pos.x);
        }

        BeginDrawing();

        draw_world(world, WORLD_SIZE, WORLD_SIZE);

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}

cell_t*** init_world()
{

  cell_t ***world = malloc(WORLD_SIZE * sizeof(cell_t**));
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

void draw_world(cell_t*** world, int height, int width)
{
    for (int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            cell_t *cell = world[row][col];
            DrawRectangle(col, row, CELL_SIDE_SIZE, CELL_SIDE_SIZE, cell->color);

        }
    }

}

void update_cells(cell_t*** world, int height, int width)
{
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            world[row][col]->update_function(world, world[row][col], row, col);
        }
    }
}

insert_cell_function_t update_selected_cell_type(void (*insert_function)(cell_t***, int16_t, int16_t)) 
{
    if (IsKeyDown(KEY_S))
    {
        //insert_function = insert_sand;
        printf("Sand Selected\n");
        return insert_sand;
    }
    if (IsKeyDown(KEY_W))
    {
        //insert_function = insert_water;
        printf("Water Selected\n");
        return insert_water;
    }

    return insert_function;
}