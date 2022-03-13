#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "triangle.h"

// Define a consistent time step for animations
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

// "extern" because declared here but not defined here
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *color_buffer_texture;
extern uint32_t *color_buffer;
extern int window_width;
extern int window_height;

bool initialize_window(void);
void destroy_window(void);

void render_color_buffer(void);
void clear_color_buffer(uint32_t new_color);

void draw_grid(void);
void draw_dotted_grid(void);

void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);

// void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_wireframe_triangle(triangle_t triangle, uint32_t color);
void draw_filled_triangle(triangle_t triangle, uint32_t color);

/**
* @brief Change color based on a percentage factor to represent light intensity
* 
* @details black * percentage_factor == some gray
*/
uint32_t light_apply_intensity(uint32_t original_color, float percentage_factor);
