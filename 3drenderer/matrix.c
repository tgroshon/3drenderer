#include <math.h>
#include "matrix.h"
#include "vector.h"

mat4_t mat4_identity(void) {
  // clang-format off
  mat4_t result = {{
    {1, 0, 0, 0}, 
    {0, 1, 0, 0}, 
    {0, 0, 1, 0}, 
    {0, 0, 0, 1}
  }};
  // clang-format on
  return result;
}

mat4_t mat4_make_scale(float sx, float sy, float sz) {
  mat4_t result = mat4_identity();

  result.m[0][0] = sx;
  result.m[1][1] = sy;
  result.m[2][2] = sz;

  return result;
}


mat4_t mat4_make_translation(float tx, float ty, float tz) {
  mat4_t result = mat4_identity();

  result.m[0][3] = tx;
  result.m[1][3] = ty;
  result.m[2][3] = tz;

  return result;
}

mat4_t mat4_make_rotation_z(float angle) { 
  float c = cos(angle);
  float s = sin(angle);
  mat4_t res = mat4_identity();

  res.m[0][0] = c;
  res.m[0][1] = -s;
  res.m[1][0] = s;
  res.m[1][1] = c;

  return res; 
}

mat4_t mat4_make_rotation_x(float angle) { 
  float c = cos(angle);
  float s = sin(angle);
  mat4_t res = mat4_identity();

  res.m[1][1] = c;
  res.m[1][2] = -s;
  res.m[2][1] = s;
  res.m[2][2] = c;

  return res; 
}

mat4_t mat4_make_rotation_y(float angle) { 
  float c = cos(angle);
  float s = sin(angle);
  mat4_t res = mat4_identity();

  res.m[0][0] = c;
  res.m[0][2] = s;
  res.m[2][0] = -s;
  res.m[2][2] = c;

  return res; 
}

/**
* @brief Create a combined 4x4 rotation matrix around all 3D axises
*/
mat4_t mat4_make_rotation_all(float angle_x, float angle_y, float angle_z) {
  mat4_t all_rotations = mat4_identity();

  all_rotations = mat4_mul_mat4(mat4_make_rotation_x(angle_x), all_rotations);
  all_rotations = mat4_mul_mat4(mat4_make_rotation_y(angle_y), all_rotations);
  all_rotations = mat4_mul_mat4(mat4_make_rotation_z(angle_z), all_rotations);

  return all_rotations;
}

mat4_t mat4_make_world_matrix(mat4_t scale, mat4_t rotation, mat4_t translation) {
  mat4_t world = mat4_identity();

  /// NOTE: Order matters! (a) matrix multiplcation is noncommutative and (b) applying 
  /// transformations have different results in different orders. Always:
  ///   1. Scale
  ///   2. Rotate
  ///   3. Translate
  world = mat4_mul_mat4(scale, world);
  world = mat4_mul_mat4(rotation, world);
  world = mat4_mul_mat4(translation, world);

  return world;
}

vec4_t mat4_mul_vec4(mat4_t m, vec4_t v) {
  vec4_t result;

  result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
  result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
  result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
  result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;

  return result;
}

mat4_t mat4_mul_mat4(mat4_t ma, mat4_t mb) {
  mat4_t res;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      res.m[i][j] = ma.m[i][0] * mb.m[0][j] + ma.m[i][1] * mb.m[1][j] + ma.m[i][2] * mb.m[2][j] +
                    ma.m[i][3] * mb.m[3][j];
    }
  }

  return res;
}

