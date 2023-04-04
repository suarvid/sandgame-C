#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "cells/sand/sand.h"
#include "cells/water/water.h"
#include "cells/cell.h"
#include "raylib.h"
// Note to self: Raylib origin in top-left corner (as usual)

typedef void (*insert_cell_function_t)(cell_t ***, int16_t, int16_t);

cell_t ***init_world();
void draw_world(cell_t ***world, int height, int width);
void update_cells(cell_t ***world, int height, int width);
insert_cell_function_t update_selected_cell_type(void (*insert_function)(cell_t ***, int16_t, int16_t));
void print_cursor_position();
int translate_to_world(float num);

int main(void)
{

    cell_t ***world = init_world();
    void (*insert_function)(cell_t ***, int16_t, int16_t) = insert_sand;

    Vector2 mouse_pos = {0.0, 0.0};
    InitWindow(WORLD_RENDER_SIZE, WORLD_RENDER_SIZE, "Window");
    SetTargetFPS(30);
    int aligned_x = 0;
    int aligned_y = 0;

    while (!WindowShouldClose())
    {
        update_cells(world, WORLD_SIZE, WORLD_SIZE);
        insert_function = update_selected_cell_type(insert_function);

        if (IsKeyDown(KEY_SPACE))
        {
            mouse_pos = GetMousePosition();
            aligned_x = translate_to_world(mouse_pos.x);
            aligned_y = translate_to_world(mouse_pos.y);
            insert_function(world, aligned_y, aligned_x);
        }

        BeginDrawing();

        draw_world(world, WORLD_SIZE, WORLD_SIZE);

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}

cell_t ***init_world()
{

    cell_t ***world = malloc(WORLD_SIZE * sizeof(cell_t **));
    for (int row = 0; row < WORLD_SIZE; row++)
    {
        world[row] = malloc(WORLD_SIZE * sizeof(cell_t));
        for (int col = 0; col < WORLD_SIZE; col++)
        {
            world[row][col] = create_empty_cell(row, col);
        }
    }

    fprintf(stderr, "Initiated World\n");
    return world;
}

void draw_world(cell_t ***world, int height, int width)
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            cell_t *cell = world[row][col];
            DrawRectangle(CELL_RENDER_SIZE * col, CELL_RENDER_SIZE * row, CELL_RENDER_SIZE, CELL_RENDER_SIZE, cell->color);
        }
    }
}

void update_cells(cell_t ***world, int height, int width)
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            world[row][col]->update_function(world, world[row][col], row, col);
        }
    }
}

insert_cell_function_t update_selected_cell_type(void (*insert_function)(cell_t ***, int16_t, int16_t))
{
    if (IsKeyDown(KEY_S))
    {
        // insert_function = insert_sand;
        printf("Sand Selected\n");
        return insert_sand;
    }
    if (IsKeyDown(KEY_W))
    {
        // insert_function = insert_water;
        printf("Water Selected\n");
        return insert_water;
    }

    return insert_function;
}

void print_cursor_position()
{
    Vector2 mouse_pos = GetMousePosition();
    fprintf(stderr, "Mouse Position: %f, %f\n", mouse_pos.x, mouse_pos.y);
}

int translate_to_world(float num)
{
    return (int)(num / CELL_RENDER_SIZE);
}