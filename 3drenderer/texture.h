#pragma once

#include <stdint.h>

typedef struct {
  float u;
  float v;
} tex2_t;

// The resolution of the texture object/file
extern int texture_width;
extern int texture_height;

// Future texture pointer
extern uint32_t* mesh_texture;

// Placeholder Texture before we start reading from PNG files
extern const uint8_t REDBRICK_TEXTURE[];
