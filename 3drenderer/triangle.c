#include "triangle.h"
#include "vector.h"

triangle_t create_triangle(int x0, int y0, int x1, int y1, int x2, int y2){
  triangle_t tri;

  vec2_t point_a = {.x = x0, .y = y0};
  vec2_t point_b = {.x = x1, .y = y1};
  vec2_t point_c = {.x = x2, .y = y2};

  tri.points[0] = point_a;
  tri.points[1] = point_b;
  tri.points[2] = point_c;

  return tri;
}

void tri_int_swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

triangle_t sort_tri_points_top_down(triangle_t tri) {
  int x0 = tri.points[0].x;
  int y0 = tri.points[0].y;
  int x1 = tri.points[1].x;
  int y1 = tri.points[1].y;
  int x2 = tri.points[2].x;
  int y2 = tri.points[2].y;

  // Step 1: sort points into flat-top+flat-bottom order: xy0 (top), xy1 (middle), xy2
  if (y0 > y1) {
    tri_int_swap(&y0, &y1);
    tri_int_swap(&x0, &x1);
  }
  if (y1 > y2) {
    tri_int_swap(&y1, &y2);
    tri_int_swap(&x1, &x2);
  }
  if (y0 > y1) {
    tri_int_swap(&y0, &y1);
    tri_int_swap(&x0, &x1);
  }
  triangle_t tri_result;

  vec2_t point0 = {.x = x0, .y = y0};
  vec2_t point1 = {.x = x1, .y = y1};
  vec2_t point2 = {.x = x2, .y = y2};
  tri_result.points[0] = point0;
  tri_result.points[1] = point1;
  tri_result.points[2] = point2;

  return tri_result;
}

vec2_t find_triangle_midpoint(triangle_t tri) {
  // NOTE: triangle must have points already sorted down into flat-top+flat-bottom order: xy0 (top), xy1 (middle), xy2 (bottom)

  int x0 = tri.points[0].x;
  int y0 = tri.points[0].y;
  int x1 = tri.points[1].x;
  int y1 = tri.points[1].y;
  int x2 = tri.points[2].x;
  int y2 = tri.points[2].y;

  // Step 2: Y component of xy1 is the midpoint.y
  int my = y1;

  // Step 3: Find midpoint x using triangle similarity, "two triangles of the same shape
  // but different size always have the same ratio between sides as eachother"
  int mx = ((float)((x2 - x0) * (y1 - y0)) / (float)(y2 - y0)) + x0;

  vec2_t midpoint = {.x = mx, .y = my};

  return midpoint;
}
