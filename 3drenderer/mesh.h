#pragma once
#include "vector.h"
#include "triangle.h"

/// <summary>
/// Defines a struct for dynamically sized meshes containing vertices, faces, and rotation
/// </summary>
typedef struct {
  vec3_t *vertices; // dynamic array
  face_t *faces;    // dynamic array
  vec3_t rotation;  // euler angles with x, y, z denoting axis of rotation
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data();
