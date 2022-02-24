#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "array.h"
#include "display.h"
#include "mesh.h"
#include "vector.h"

bool is_running = false;
float fov_factor = 640; // magic number to scale 3D space
vec3_t camera_position = {.x = 0, .y = 0, .z = -5};
int previous_frame_time = 0;

/// Array of triangles for mesh
triangle_t* triangles_to_render = NULL;

void setup() {
  // allocate memory of color buffer to fill one 32-bit number for every pixel
  // for window dimensions; returns NULL if malloc fails
  color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  if (color_buffer == NULL) {
    fprintf(stderr, "Failed to initialize memory for color buffer.\n");
    is_running = false;
    return;
  }

  color_buffer_texture =
      SDL_CreateTexture(renderer,                    // renderer
                        SDL_PIXELFORMAT_ARGB8888,    // Alpha-Red-Green-Blue 8-bits each
                        SDL_TEXTUREACCESS_STREAMING, // continuous updating because we
                                                     // update each frame
                        window_width, window_height);

  load_cube_mesh_data();
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

void increment_mesh_rotation() {
  mesh.rotation.x += 0.01;
  mesh.rotation.y += 0.01;
  mesh.rotation.z += 0.01;
}

/**
 * @brief Project the 3D model to 2D screenspace
 * and apply other transformations
 */
void update() {
  // re-initialize array of triangles 
  triangles_to_render = NULL;

  increment_mesh_rotation();

  int num_faces = array_length(mesh.faces);

  for (int i = 0; i < num_faces; i++) {
    face_t mesh_face = mesh.faces[i];
    vec3_t face_vertices[3];

    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    triangle_t projected_triangle;
    for (int j = 0; j < 3; j++) {
      vec3_t transformed_point = face_vertices[j];
      transformed_point = vec3_rotate_x(transformed_point, mesh.rotation.x);
      transformed_point = vec3_rotate_y(transformed_point, mesh.rotation.y);
      transformed_point = vec3_rotate_z(transformed_point, mesh.rotation.z);

      // translate the vertex away from the camera Z
      transformed_point.z -= camera_position.z;

      // project point and perspective divide
      vec2_t projected_point = perspective_project(transformed_point);
      projected_point.x += (window_width / 2);
      projected_point.y += (window_height / 2);

      projected_triangle.points[j] = projected_point;
    }

    // FIXME: dynamically allocating memory inside the game loop isn't great;
    // fix later.
    array_push(triangles_to_render, projected_triangle);
  }
}

/**
 * @brief draws our projected poitns to the screen
 * 
 * @details before drawing projected points, translate to center cooridinate
 * frame because that's how we decided to do our coordinates instead of from the
 * top-left.
 */
void render() {
  draw_dotted_grid();

  int triangle_count = array_length(triangles_to_render);

  for (int i = 0; i < triangle_count; i++) {
    triangle_t tri = triangles_to_render[i];

    // draw vertex points
    draw_rect(tri.points[0].x, tri.points[0].y, 3, 3, 0xFF00FFFF);
    draw_rect(tri.points[1].x, tri.points[1].y, 3, 3, 0xFF00FFFF);
    draw_rect(tri.points[2].x, tri.points[2].y, 3, 3, 0xFF00FFFF);

    // draw wireframe triangle faces
    draw_triangle(tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y,
                  tri.points[2].x, tri.points[2].y, 0xFF00FFFF);
  }

  array_free(triangles_to_render);

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

    // Constant Delta-Time; good but if FPS is set to higher, animations will
    // execute quicker
    // TODO: implement "variable delta-time"
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
      SDL_Delay(FRAME_TARGET_TIME);
    }
    previous_frame_time = SDL_GetTicks();

    update();
    render();
  }
}

/**
* @brief Free memory that was dynamically allocated
*/
void free_resources() {
  // NOTE: avoid freeing a NULL pointer
  if (color_buffer != NULL) {
    free(color_buffer);
  }

  array_free(mesh.faces);
  array_free(mesh.vertices);
}

int main(int argc, char *args[]) {
  printf("Program starting...\n");
  is_running = initialize_window();

  setup();

  game_loop();

  destroy_window();
  free_resources();

  printf("finished.\n");
  return 0;
}
