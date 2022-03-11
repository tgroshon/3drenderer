#include "vector.h"
#include <math.h>

/////////////////////////
/// Vector 2D Functions
/////////////////////////

float vec2_length(vec2_t v) { return sqrt(v.x * v.x + v.y * v.y); }

vec2_t vec2_add(vec2_t a, vec2_t b) {
  vec2_t result = {.x = a.x + b.x, .y = a.y + b.y};
  return result;
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
  vec2_t result = {.x = a.x - b.x, .y = a.y - b.y};
  return result;
}

vec2_t vec2_mul(vec2_t v, float scalar) {
  vec2_t result = {.x = v.x * scalar, .y = v.y * scalar};
  return result;
}

vec2_t vec2_div(vec2_t v, float scalar) {
  vec2_t result = {.x = v.x / scalar, .y = v.y / scalar};
  return result;
};

float vec2_dot(vec2_t a, vec2_t b) { return a.x * b.x + a.y * b.y; }

/////////////////////////
/// Vector 3D Functions
/////////////////////////

float vec3_length(vec3_t v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

vec3_t vec3_add(vec3_t a, vec3_t b) {
  vec3_t result = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
  return result;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
  vec3_t result = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
  return result;
}

vec3_t vec3_mul(vec3_t v, float scalar) {
  vec3_t result = {.x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar};
  return result;
}

vec3_t vec3_div(vec3_t v, float scalar) {
  vec3_t result = {.x = v.x / scalar, .y = v.y / scalar, .z = v.z / scalar};
  return result;
};

vec3_t vec3_cross(vec3_t a, vec3_t b) {
  // clang-format off
  vec3_t result = {
      .x = a.y * b.z - a.z * b.y, 
      .y = a.z * b.x - a.x * b.z, 
      .z = a.x * b.y - a.y * b.x
  };
  // clang-format on

  return result;
}

float vec3_dot(vec3_t a, vec3_t b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

void vec3_normalize(vec3_t *vec) {
  float len = vec3_length(*vec);
  vec->x /= len;
  vec->y /= len;
  vec->z /= len;
}

vec3_t vec3_rotate_x(vec3_t v, float angle) {
  vec3_t rotate_vector = {.x = v.x,
                          .y = v.y * cos(angle) - v.z * sin(angle),
                          .z = v.y * sin(angle) + v.z * cos(angle)};

  return rotate_vector;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
  vec3_t rotate_vector = {.x = v.x * cos(angle) - v.z * sin(angle),
                          .y = v.y,
                          .z = v.x * sin(angle) + v.z * cos(angle)};

  return rotate_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
  vec3_t rotate_vector = {.x = v.x * cos(angle) - v.y * sin(angle),
                          .y = v.x * sin(angle) + v.y * cos(angle),
                          .z = v.z};

  return rotate_vector;
}



vec4_t vec4_from_vec3(vec3_t v) {
  vec4_t res = {.x = v.x, .y = v.y, .z = v.z, .w = 1};
  return res;
}

vec3_t vec3_from_vec4(vec4_t v) {
  vec3_t res = {.x = v.x, .y = v.y, .z = v.z};
  return res;
}
