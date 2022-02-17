#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Global statics;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
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

  // Set the global static window
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

void render() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

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
