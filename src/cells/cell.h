#pragma once

#include <stdint.h>
#include "../constants.h"
#include "raylib.h"

typedef enum CellType
{
    EMPTY,
    SAND,
    WATER,
    WOOD,
    FIRE,
} cellType_t;

typedef struct cell
{
    bool updated;
    int8_t velocity;
    int8_t lifetime;
    int8_t density;
    Color color;
    enum CellType type;
    void (*update_function)(struct cell***, struct cell*, int16_t, int16_t);
} cell_t;

cell_t* create_empty_cell(int row, int col);
void empty_update_function(struct cell*** world, cell_t *self, int16_t row, int16_t col);
