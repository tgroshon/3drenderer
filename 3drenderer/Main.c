#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "display.h"
#include "vector.h"

// Testing vectors with a Cube
vec3_t cube_points[729];

bool is_running = false;

void setup() {
  // allocate memory of color buffer to fill one 32-bit number for every pixel
  // for window dimensions; returns NULL if malloc fails
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

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
      window_width, window_height);

  // Testing 3D vector point cloud.
  int point_count = 0;
  for (float x = -1; x <= 1; x += 0.25) {
    for (float y = -1; y <= 1; y += 0.25) {
      for (float z = -1; z <= 1; z += 0.25) {
        vec3_t new_point = {.x = x, .y = y, .z = z};
        cube_points[point_count] = new_point;
        point_count++;
      }
    }
  }
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

  draw_dotted_grid();
  draw_rect(900, 500, 100, 200, 0xFFCD19F9);
  draw_rect(400, 900, 500, 200, 0xFFDCF918);

  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}


int main(int argc, char *args[]) {
  printf("Program starting...\n");
  is_running = initialize_window();

  setup();

  // Testing vectors
  vec3_t myvector = {2.0, 3.0, 4.0};

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  printf("finished.\n");
  return 0;
}
