#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

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
void draw_pixel(int x, int y, uint32_t color);
void draw_grid(void);
void draw_dotted_grid(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);
