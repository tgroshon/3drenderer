#include <stdint.h>

#include "triangle.h"
#include "vector.h"
#include "swap.h"

triangle_t create_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color,
                           float avg_depth) {
  triangle_t tri;
  tri.color = color;
  tri.avg_depth = avg_depth;
  tri.light_intensity_factor = 1.0;

  vec2_t point_a = {.x = x0, .y = y0};
  vec2_t point_b = {.x = x1, .y = y1};
  vec2_t point_c = {.x = x2, .y = y2};

  tri.points[0] = point_a;
  tri.points[1] = point_b;
  tri.points[2] = point_c;

  return tri;
}

triangle_t sort_tri_points_top_down(triangle_t *tri) {
  int x0 = tri->points[0].x;
  int y0 = tri->points[0].y;
  float u0 = tri->texcoords[0].u;
  float v0 = tri->texcoords[0].v;
  int x1 = tri->points[1].x;
  int y1 = tri->points[1].y;
  float u1 = tri->texcoords[1].u;
  float v1 = tri->texcoords[1].v;
  int x2 = tri->points[2].x;
  int y2 = tri->points[2].y;
  float u2 = tri->texcoords[2].u;
  float v2 = tri->texcoords[2].v;

  // Step 1: sort points into flat-top+flat-bottom order: xy0 (top), xy1 (middle), xy2
  if (y0 > y1) {
    int_swap(&y0, &y1);
    int_swap(&x0, &x1);
    float_swap(&u0, &u1);
    float_swap(&v0, &v1);
  }
  if (y1 > y2) {
    int_swap(&y1, &y2);
    int_swap(&x1, &x2);
    float_swap(&u1, &u2);
    float_swap(&v1, &v2);
  }
  if (y0 > y1) {
    int_swap(&y0, &y1);
    int_swap(&x0, &x1);
    float_swap(&u0, &u1);
    float_swap(&v0, &v1);
  }
  triangle_t tri_result;

  vec2_t point0 = {.x = x0, .y = y0};
  vec2_t point1 = {.x = x1, .y = y1};
  vec2_t point2 = {.x = x2, .y = y2};
  tex2_t texcoord0 = {
      .u = u0,
      .v = v0,
  };
  tex2_t texcoord1 = {
      .u = u1,
      .v = v1,
  };
  tex2_t texcoord2 = {
      .u = u2,
      .v = v2,
  };

  tri_result.points[0] = point0;
  tri_result.points[1] = point1;
  tri_result.points[2] = point2;
  tri_result.texcoords[0] = texcoord0;
  tri_result.texcoords[1] = texcoord1;
  tri_result.texcoords[2] = texcoord2;
  tri_result.avg_depth = tri->avg_depth;
  tri_result.color = tri->color;
  tri_result.light_intensity_factor = tri->light_intensity_factor;

  return tri_result;
}

vec2_t find_triangle_midpoint(triangle_t *tri) {
  // NOTE: triangle must have points already sorted down into flat-top+flat-bottom order:
  // xy0 (top), xy1 (middle), xy2 (bottom)

  int x0 = tri->points[0].x;
  int y0 = tri->points[0].y;
  int x1 = tri->points[1].x;
  int y1 = tri->points[1].y;
  int x2 = tri->points[2].x;
  int y2 = tri->points[2].y;

  // Step 2: Y component of xy1 is the midpoint.y
  int my = y1;

  // Step 3: Find midpoint x using triangle similarity, "two triangles of the same shape
  // but different size always have the same ratio between sides as eachother"
  int mx = ((float)((x2 - x0) * (y1 - y0)) / (float)(y2 - y0)) + x0;

  vec2_t midpoint = {.x = mx, .y = my};

  return midpoint;
}
