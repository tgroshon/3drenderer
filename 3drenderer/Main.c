#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Global statics;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *color_buffer_texture = NULL;
bool is_running = false;
uint32_t *color_buffer = NULL;

// TODO: make named constants with #define
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }

  // Create and set the global static window
  window = SDL_CreateWindow(NULL, // No title because going borderless
                            SDL_WINDOWPOS_CENTERED, // position x
                            SDL_WINDOWPOS_CENTERED, // position y
                            WINDOW_WIDTH,           // width
                            WINDOW_HEIGHT,          // height
                            SDL_WINDOW_BORDERLESS   // additional flags
  );

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

  return true;
}

void render_color_buffer() {
  SDL_UpdateTexture(color_buffer_texture, // texture
                    NULL,         // rectangle for getting subset of buffer
                    color_buffer, // our color buffer
                    (int)(WINDOW_WIDTH * sizeof(uint32_t))); // size of each row
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void setup() {
  // allocate memory of color buffer to fill one 32-bit number for every pixel
  // for window dimensions; returns NULL if malloc fails
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);

  if (color_buffer == NULL) {
    fprintf(stderr, "Failed to initialize memory for color buffer.\n");
    is_running = false;
    return;
  }

  color_buffer_texture = SDL_CreateTexture(
      renderer,                    // renderer
      SDL_PIXELFORMAT_ARGB8888,    // Alpha-Red-Green-Blue 8-bits each
      SDL_TEXTUREACCESS_STREAMING, // continuous updating because we update each
                                   // frame
      WINDOW_WIDTH, WINDOW_HEIGHT);
}

/**
 * Tear-down everything we created
 * NOTE: kill in reverse order of initialization
 */
void destroy_window() {
  // NOTE: avoid freeing a NULL pointer
  if (color_buffer != NULL) {
    free(color_buffer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      is_running = false;
    }
    break;
  }
}

void update() {
  // TODO: implement
}

/**
 * @brief Sets every pixel of the color buffer to a new color
 */
void clear_color_buffer(uint32_t new_color) {
  for (int row = 0; row < WINDOW_HEIGHT; row++) {
    for (int column = 0; column < WINDOW_WIDTH; column++) {
      color_buffer[(WINDOW_WIDTH * row) + column] = new_color;
    }
  }
}

void render() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_color_buffer();
  clear_color_buffer(0xFFFFFF00);

  SDL_RenderPresent(renderer);
}

int main(int argc, char *args[]) {
  printf("Program starting...\n");
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  printf("finished.\n");
  return 0;
}
