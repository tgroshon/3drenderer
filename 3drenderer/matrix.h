#pragma once

#include "vector.h"

/**
* 4x4 Matrix
* Implemented as array of arrays
*/
typedef struct {
  float m[4][4];
} mat4_t;


/**
* @brief Return a 4x4 identity matrix
* 
* @return 4x4 square identity matrix
*/
mat4_t mat4_identity(void);

/**
* @brief Return a 4x4 scaling matrix
* 
* @description Shaped thusly:
* | sx  0  0  0 |
* |  0 sy  0  0 |
* |  0  0 sz  0 |
* |  0  0  0  1 |
* 
* @param sx Scale by X
* @param sy Scale by Y
* @param sz Scale by Z
* 
* @return scaling transformation matrix
*/
mat4_t mat4_make_scale(float sx, float sy, float sz);

/**
* @brief Return a 4x4 translation matrix
* 
* @details Shaped thusly:
* |  0  0  0 tx |
* |  0  0  0 ty |
* |  0  0  0 tz |
* |  0  0  0  1 |
* 
* @param tx Translate by X
* @param ty Translate by Y
* @param tz Translate by Z
* 
* @return translation transformation matrix
*/
mat4_t mat4_make_translation(float tx, float ty, float tz);

/**
* @brief Multiply a 4x4 matrix by a 4x1 vector
* 
* @param m Matrix
* @param v Vec4
* 
* @return result Vec4
*/
vec4_t mat4_mul_vec4(mat4_t m, vec4_t v);


