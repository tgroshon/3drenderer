#pragma once

#include "texture.h"
#include "vector.h"
#include <stdint.h>

typedef struct {
  vec4_t points[3];
  tex2_t texcoords[3];
  uint32_t color;
  float light_intensity_factor;
  float avg_depth;
} triangle_t;

/**
 * @brief Sort the triangle points top down in prep for flat-top;flat-bottom algorithm
 */
triangle_t sort_tri_points_top_down(triangle_t *tri);
