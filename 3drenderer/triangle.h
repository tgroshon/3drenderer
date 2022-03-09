#pragma once
#include <stdint.h>
#include "vector.h"

typedef struct {
  vec2_t points[3];
  uint32_t color;
  float avg_depth;
} triangle_t;


triangle_t sort_tri_points_top_down(triangle_t tri);
vec2_t find_triangle_midpoint(triangle_t tri);
triangle_t create_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color, float avg_depth);
