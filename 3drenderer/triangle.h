#pragma once
#include <stdint.h>
#include "vector.h"

/**
 * Face represents the indexes of 3 points in a corresponding mesh point array.
 *
 * @details The ordering of which point you place in which field is significant
 * because a clockwise ordering of points determines the forward side (normal)
 * of the face; counter-clockwise denotes the back of the face.
 *
 * @note each field is base 1 instead of base 0
 */
typedef struct {
  int a;
  int b;
  int c;
  uint32_t color;
} face_t;

typedef struct {
  vec2_t points[3];
  uint32_t color;
} triangle_t;


triangle_t sort_tri_points_top_down(triangle_t tri);
vec2_t find_triangle_midpoint(triangle_t tri);
triangle_t create_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
