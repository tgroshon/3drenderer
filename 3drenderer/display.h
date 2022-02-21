#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

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
void safe_set_color_buffer(int address, uint32_t color);
void clear_color_buffer(uint32_t new_color);
void draw_pixel(int x, int y, uint32_t color);
void draw_grid(void);
void draw_dotted_grid(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);
