#pragma once

#include <stdint.h>
#include "vector.h"
#include "texture.h"

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
  // indices of vertices in the mesh
  int a;
  int b;
  int c;
  // UV coordinate mappings to the texture
  tex2_t a_uv;
  tex2_t b_uv;
  tex2_t c_uv;
  // Solid color if texture not used
  uint32_t color;
} face_t;

/**
* Defines a struct for dynamically sized meshes containing vertices, faces, and rotation
*/
typedef struct {
  vec3_t *vertices;   // dynamic array
  face_t *faces;      // dynamic array
  vec3_t rotation;    // euler angles with x, y, z denoting axis of rotation
  vec3_t scale;       // scale with x, y, z
  vec3_t translation; // translation with x, y, z
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data();
void load_obj_file_data();
