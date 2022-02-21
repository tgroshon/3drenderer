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
  window = SDL_CreateWindow(NULL, // No title because going borderless
                            SDL_WINDOWPOS_CENTERED, // position x
                            SDL_WINDOWPOS_CENTERED, // position y
                            window_width,           // width
                            window_height,          // height
                            SDL_WINDOW_BORDERLESS); // additional flags

  if (!window) {
    fprintf(stderr, "Error creating the SDL window.\n");
    return false;
  }

  renderer = SDL_CreateRenderer(
      window, // window object
      -1,     // display device code; -1 for default visual device
      0       // additional flags
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
  // NOTE: avoid freeing a NULL pointer
  if (color_buffer != NULL) {
    free(color_buffer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void render_color_buffer() {
  SDL_UpdateTexture(color_buffer_texture, // texture
                    NULL,         // rectangle for getting subset of buffer
                    color_buffer, // our color buffer
                    (int)(window_width * sizeof(uint32_t))); // size of each row
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}


void safe_set_color_buffer(int address, uint32_t color) {
  int max_address = window_width * window_height;
  if (address > max_address) {
    return;
  }
  color_buffer[address] = color;
}

/**
 * @brief Sets every pixel of the color buffer to a new color
 */
void clear_color_buffer(uint32_t new_color) {
  for (int row = 0; row < window_height; row++) {
    for (int column = 0; column < window_width; column++) {
      safe_set_color_buffer((window_width * row) + column, new_color);
    }
  }
}

/**
 * @brief Example drawing a grid across the screen
 */
void draw_grid() {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      if (x % 20 == 0 || y % 20 == 0) {
        safe_set_color_buffer((window_width * y) + x, 0xFF333333);
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
      safe_set_color_buffer((window_width * y) + x, 0xFF333333);
    }
  }
}

/**
 * @brief Example of drawing a rectangle on the screen
 */
void draw_rect(int x, int y, int width, int height, uint32_t color) {
  int starting_position = (window_width * y) + x;
  for (int w = 0; w < width; w++) {
    for (int h = 0; h < height; h++) {
      safe_set_color_buffer(starting_position + (window_width * h) + w, color);
    }
  }
}
