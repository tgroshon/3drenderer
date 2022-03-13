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
* @brief Create a 4x4 identity matrix
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
* @brief Create a 4x4 translation matrix
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
* @brief Create a 4x4 rotation matrix about Z axis
* 
* @details Shaped thusly:
* |  c -s  0  0 |
* |  s  c  0  0 |
* |  0  0  0  0 |
* |  0  0  0  1 |
* 
* @param angle Angle of rotation about Z axis
* 
* @return rotation transformation matrix
*/
mat4_t mat4_make_rotation_z(float angle);

/**
* @brief Create a 4x4 rotation matrix about X axis
* 
* @details Shaped thusly:
* |  1  0  0  0 |
* |  0  c -s  0 |
* |  0  s  c  0 |
* |  0  0  0  1 |
* 
* @param angle Angle of rotation about x axis
* 
* @return rotation transformation matrix
*/
mat4_t mat4_make_rotation_x(float angle);

/**
* @brief Create a 4x4 rotation matrix about Y axis
* 
* @details Shaped thusly:
* |  c  0  s  0 |
* |  0  1  0  0 |
* | -s  0  c  0 |
* |  0  0  0  1 |
* 
* @note: inverts the +/- of sin so that direction of rotation
* is consistent with our coordinate system orientation (handedness)
* 
* @param angle Angle of rotation about Y axis
* 
* @return rotation transformation matrix
*/
mat4_t mat4_make_rotation_y(float angle);


/**
* @brief Create a combined 4x4 rotation matrix around all 3D axises
*/
mat4_t mat4_make_rotation_all(float angle_x, float angle_y, float angle_z);

/**
* @brief Create a 4x4 matrix that combines transformations into single world matrix
*/
mat4_t mat4_make_world_matrix(mat4_t scale, mat4_t rotation, mat4_t translation);


/**
* @brief Create a 4x4 projection matrix
* 
* @details Normalizes all vectors to image space between -1 and 1;
* 
* @note Holds an operation to store an unchanged Z-value in the Vec4 result's W position
* so that perspective divide can happen in a separate step.
* 
*/
mat4_t mat4_make_perspective(float fov, float aspect, float znear, float zfar);

/**
* @brief Apply projection matrix to Vec4 and apply perspective divide
* 
* @returns Vec4 Normalized Device Coordinates (NDC) or "image space"
*/
vec4_t mat4_mul_vec4_project(mat4_t projection_matrix, vec4_t v);

/**
* @brief Multiply a 4x4 matrix by a 4x1 vector
* 
* @param m Matrix
* @param v Vec4
* 
* @return result Vec4
*/
vec4_t mat4_mul_vec4(mat4_t m, vec4_t v);

/**
* @brief Multiply a 4x4 matrix by a 4x4 matrix
* 
* @param ma Mat4
* @param mb Mat4
* 
* @return result Mat4
*/
mat4_t mat4_mul_mat4(mat4_t ma, mat4_t mb);
