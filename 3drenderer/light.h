#pragma once

#include "vector.h"
#include <stdint.h>

typedef struct {
  vec3_t direction;
} light_t;

extern light_t global_light;

/**
* @brief Change color based on a percentage factor to represent light intensity
* 
* @details black * percentage_factor == some gray
*/
uint32_t light_apply_intensity(uint32_t original_color, float percentage_factor);
