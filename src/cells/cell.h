#pragma once

#include <stdint.h>
#include "../constants.h"
#include "raylib.h"

typedef enum CellType
{
    EMPTY,
    SAND,
} cellType_t;

typedef struct cell
{
    bool updated;
    int8_t velocity;
    int8_t lifetime;
    Color color;
    enum CellType type;
    void (*update_function)(struct cell**, int16_t, int16_t);
} cell_t;

cell_t create_empty_cell(int row, int col);
void empty_update_function(struct cell** cell_pp, int16_t row, int16_t col);
