#include "triangle.h"
#include "vector.h"

vec2_t find_triangle_midpoint(triangle_t tri) {
  // Step 1: sort points into flat-top+flat-bottom order: xy0 (top), xy1 (middle), xy2 (bottom)

  // Step 2: Y component of xy1 is the midpoint.y

  // Step 3: Find midpoint x using triangle similarity, "two triangles of the same shape but different size always have the same ratio between sides as eachother"


  vec2_t midpoint = {
    .x = 0,
    .y = 0
  };

  return midpoint;
}
