#include "utils.h"
#include <stdbool.h>
#include "constants.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

bool out_of_bounds(int16_t row, int16_t col)
{
    return row < 0 || row >= WORLD_SIZE || col < 0 || col >= WORLD_SIZE;
}