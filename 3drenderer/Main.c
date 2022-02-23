#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "display.h"
#include "vector.h"

bool is_running = false;
float fov_factor = 640; // magic number to scale 3D space
vec3_t camera_position = {.x = 0, .y = 0, .z = -5};
int previous_frame_time = 0;

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

/**
 * @brief Convert 3D model space to perspective view of 2D screen space
 * @details project to show thigns from the side adjusting for Z
 * distance by implementing basic "perspective divide"; also applies FOV scaling
 */
vec2_t perspective_project(vec3_t point) {
  vec2_t projected_point = {.x = point.x * fov_factor / point.z,
                            .y = point.y * fov_factor / point.z};
  return projected_point;
}

/**
 * @brief Project the 3D model to 2D screenspace
 * and apply other transformations
 */
void update() {
  for (int i = 0; i < 729; i++) {
  }
}

/**
 * @brief draws our projected poitns to the screen
 * @details before drawing projected points, translate to center cooridinate
 * frame because that's how we decided to do our coordinates instead of from the
 * top-left.
 */
void render() {
  draw_dotted_grid();

  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

/**
 * @brief Game loop
 */
void game_loop() {
  while (is_running) {
    process_input();

    // Constant Delta-Time; good but if FPS is set to higher, animations will execute quicker
    // TODO: implement "variable delta-time"
    int time_to_wait =
        FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
      SDL_Delay(FRAME_TARGET_TIME);
    }
    previous_frame_time = SDL_GetTicks();

    update();
    render();
  }
}

int main(int argc, char *args[]) {
  printf("Program starting...\n");
  is_running = initialize_window();

  setup();

  game_loop();

  destroy_window();

  printf("finished.\n");
  return 0;
}
