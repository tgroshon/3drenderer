#pragma once

#include <stdint.h>
#include "vector.h"
#include "texture.h"

typedef struct {
  vec2_t points[3];
  tex2_t texcoords[3];
  uint32_t color;
  float avg_depth;
} triangle_t;


/**
* @brief Sort the triangle points top down in prep for flat-top;flat-bottom algorithm
*/
triangle_t sort_tri_points_top_down(triangle_t tri);

/**
* @brief Find the bisecting midpoint for a flat-top;flat-bottom algorithm
*/
vec2_t find_triangle_midpoint(triangle_t tri);

/**
* @brief Factory function to create a triangle; Useful for testing.
*/
triangle_t create_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color, float avg_depth);
