#pragma once

typedef struct {
  float x;
  float y;
} vec2_t;

typedef struct {
  float x;
  float y;
  float z;
} vec3_t;

typedef struct {
  float x;
  float y;
  float z;
  float w;
} vec4_t;

/////////////////////////
/// Vector 2D Functions
/////////////////////////

/**
 * Find the mathematical length of a 2d vector
 */
float vec2_length(vec2_t v);

/**
 * Add two 2d vectors together
 */
vec2_t vec2_add(vec2_t a, vec2_t b);

/**
 * Subtract two 2d vectors
 */
vec2_t vec2_sub(vec2_t a, vec2_t b);

/**
 * Multiply a 2d vector by a float scalar
 */
vec2_t vec2_mul(vec2_t v, float s);

/**
 * Divide a 2d vector by a float scalar
 */
vec2_t vec2_div(vec2_t v, float s);

/**
 * Find dot product of two 2d vectors
 *
 * @note The dot product of a and b gives the projection of b to a
 * @note Commutative (order doesn't matter)
 * @note positive = perfectly aligned vectors; 0 = perpendicular vectors; negative =
 * opposite aligned vectors
 */
float vec2_dot(vec2_t a, vec2_t b);

/////////////////////////
/// Vector 3D Functions
/////////////////////////

/**
 * Find the mathematical length of a 3d vector
 */
float vec3_length(vec3_t v);

/**
 * Add two 3d vectors together
 */
vec3_t vec3_add(vec3_t a, vec3_t b);

/**
 * Subtract two 3d vectors; great for finding the ray between two vectors
 * @note subtracting two vectors gives a ray between them
 */
vec3_t vec3_sub(vec3_t a, vec3_t b);

/**
 * Multiply a 3d vector by a float scalar
 */
vec3_t vec3_mul(vec3_t v, float s);

/**
 * Divide a 3d vector by a float scalar
 */
vec3_t vec3_div(vec3_t v, float s);

/**
 * Find cross product of two vectors
 *
 * @note The cross product between two vectors gives a perpendicular vector; i.e. normal
 * 
 * @note Non-commutative (order matters); our system uses clock-wise vectors to denote
 * positive normal so choose the appropriate point by it's handedness.
 * 
 * @note Cross-product gives the area of the parallelogram made by two vectors
 */
vec3_t vec3_cross(vec3_t a, vec3_t b);

/**
 * Find dot product of two 3d vectors
 *
 * @note The dot product of a and b gives the projection of b to a
 * @note Commutative (order doesn't matter)
 * @note positive = perfectly aligned vectors; 0 = perpendicular vectors; negative =
 * opposite aligned vectors
 */
float vec3_dot(vec3_t a, vec3_t b);

/**
 * Convert vector of any length to a unit vector (length = 1)
 *
 * @note Useful for vectors where length is meaningless, only direction matters
 */
void vec3_normalize(vec3_t *v);

/**
 * Rotate the vector about the X axis by given angle
 */
vec3_t vec3_rotate_x(vec3_t v, float angle);

/**
 * Rotate the vector about the Y axis by given angle
 */
vec3_t vec3_rotate_y(vec3_t v, float angle);

/**
 * Rotate the vector about the Z axis by given angle
 */
vec3_t vec3_rotate_z(vec3_t v, float angle);

/**
 * Get unit normal for a triangle of Vec3s
 */
vec3_t vec3_normal(vec3_t a, vec3_t b, vec3_t c);

/**
* @brief Calculate barycentric weights used for calculating Barycentric coords
* 
* @note Useful for texture mapping
*/
vec3_t barycentric_weights(vec2_t a, vec2_t b, vec2_t c, vec2_t p);

/////////////////////////
/// Vector 4 Functions
/////////////////////////

vec4_t vec4_from_vec3(vec3_t v);
vec3_t vec3_from_vec4(vec4_t v);



