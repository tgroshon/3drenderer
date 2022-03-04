#include "display.h"
#include <stdio.h>

// defined the externs declared in display.h
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *color_buffer_texture = NULL;
uint32_t *color_buffer = NULL;
int window_width = 800;
int window_height = 600;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }

  // query dimensions of full screen max width and height
  // "fake fullscreen"
  SDL_DisplayMode display_mode;
  if (SDL_GetCurrentDisplayMode(0, &display_mode) >= 0) {
    window_width = display_mode.w;
    window_height = display_mode.h;
  }

  // Create and set the global static window
  window = SDL_CreateWindow(NULL,                   // No title because going borderless
                            SDL_WINDOWPOS_CENTERED, // position x
                            SDL_WINDOWPOS_CENTERED, // position y
                            window_width,           // width
                            window_height,          // height
                            SDL_WINDOW_BORDERLESS); // additional flags

  if (!window) {
    fprintf(stderr, "Error creating the SDL window.\n");
    return false;
  }

  renderer = SDL_CreateRenderer(window, // window object
                                -1, // display device code; -1 for default visual device
                                0   // additional flags
  );

  if (!renderer) {
    fprintf(stderr, "Error creating the SDL renderer.\n");
    return false;
  }

  // "real fullscreen"
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  return true;
}

/**
 * Tear-down everything we created
 * NOTE: kill in reverse order of initialization
 */
void destroy_window(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void render_color_buffer() {
  SDL_UpdateTexture(color_buffer_texture, // texture
                    NULL,                 // rectangle for getting subset of buffer
                    color_buffer,         // our color buffer
                    (int)(window_width * sizeof(uint32_t))); // size of each row
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

/**
 * @brief Sets every pixel of the color buffer to a new color
 */
void clear_color_buffer(uint32_t new_color) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      draw_pixel(x, y, new_color);
    }
  }
}

/**
 * @brief safely set a a pixel at coordinates (x, y) to color
 */
void draw_pixel(int x, int y, uint32_t color) {
  if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
    color_buffer[(window_width * y) + x] = color;
  }
}

/**
 * @brief Example drawing a grid across the screen
 */
void draw_grid() {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      if (x % 20 == 0 || y % 20 == 0) {
        draw_pixel(x, y, 0xFF333333);
      }
    }
  }
}

/**
 * @brief Example drawing a dotted grid across the screen
 */
void draw_dotted_grid() {
  for (int y = 0; y < window_height; y += 20) {
    for (int x = 0; x < window_width; x += 20) {
      draw_pixel(x, y, 0xFF333333);
    }
  }
}

/**
 * @brief Example of drawing a rectangle on the screen
 */
void draw_rect(int x, int y, int width, int height, uint32_t color) {
  for (int w = 0; w < width; w++) {
    for (int h = 0; h < height; h++) {
      draw_pixel(x + w, y + h, color);
    }
  }
}

/**
 * @brief Rasterize a line between two points
 *
 * @details implements a basic DDA line rasterization algorithm
 */
void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
  int delta_x = (x1 - x0);
  int delta_y = (y1 - y0);

  // use the largest largest delta length
  int side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

  // Find how much we should increment in both x and y each step
  // casting to float so that we don't throw away the decimal.
  // Using float division is the reason DDA is slower than bresenham
  float x_inc = delta_x / (float)side_length;
  float y_inc = delta_y / (float)side_length;

  float current_x = x0;
  float current_y = y0;

  for (int i = 0; i < side_length; i++) {
    draw_pixel(round(current_x), round(current_y), color);
    current_x += x_inc;
    current_y += y_inc;
  }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
  draw_line(x0, y0, x1, y1, color);
  draw_line(x1, y1, x2, y2, color);
  draw_line(x2, y2, x0, y0, color);
}

void draw_flat_bottom(int x0, int y0, int x1, int y2, int mx, int my) {

}

void draw_flat_top(int x1, int y1, int mx, int my, int x2, int y2){

}
