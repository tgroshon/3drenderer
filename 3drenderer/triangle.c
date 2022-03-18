#include <stdint.h>

#include "triangle.h"
#include "vector.h"
#include "swap.h"

triangle_t sort_tri_points_top_down(triangle_t *tri) {
  int x0 = tri->points[0].x;
  int y0 = tri->points[0].y;
  int z0 = tri->points[0].z;
  int w0 = tri->points[0].w;
  float u0 = tri->texcoords[0].u;
  float v0 = tri->texcoords[0].v;
  int x1 = tri->points[1].x;
  int y1 = tri->points[1].y;
  int z1 = tri->points[1].z;
  int w1 = tri->points[1].w;
  float u1 = tri->texcoords[1].u;
  float v1 = tri->texcoords[1].v;
  int x2 = tri->points[2].x;
  int y2 = tri->points[2].y;
  int z2 = tri->points[2].z;
  int w2 = tri->points[2].w;
  float u2 = tri->texcoords[2].u;
  float v2 = tri->texcoords[2].v;

  // Step 1: sort points into flat-top+flat-bottom order: xy0 (top), xy1 (middle), xy2
  if (y0 > y1) {
    int_swap(&y0, &y1);
    int_swap(&x0, &x1);
    float_swap(&z0, &z1);
    float_swap(&w0, &w1);
    float_swap(&u0, &u1);
    float_swap(&v0, &v1);
  }
  if (y1 > y2) {
    int_swap(&y1, &y2);
    int_swap(&x1, &x2);
    float_swap(&z1, &z2);
    float_swap(&w1, &w2);
    float_swap(&u1, &u2);
    float_swap(&v1, &v2);
  }
  if (y0 > y1) {
    int_swap(&y0, &y1);
    int_swap(&x0, &x1);
    float_swap(&z0, &z1);
    float_swap(&w0, &w1);
    float_swap(&u0, &u1);
    float_swap(&v0, &v1);
  }
  triangle_t tri_result;

  vec4_t point0 = {.x = x0, .y = y0, .z = z0, .w = w0};
  vec4_t point1 = {.x = x1, .y = y1, .z = z1, .w = w1};
  vec4_t point2 = {.x = x2, .y = y2, .z = z2, .w = w2};
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
