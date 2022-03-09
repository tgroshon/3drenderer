#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "array.h"
#include "display.h"
#include "mesh.h"
#include "vector.h"

enum cull_method { CULL_NONE, CULL_BACKFACE } cull_method;
enum render_method {
  RENDER_WIRE,
  RENDER_WIRE_VERTEX,
  RENDER_FILL_TRIANGLE,
  RENDER_FILL_TRIANGLE_WIRE
} render_method;

bool is_running = false;
float fov_factor = 640; // magic number to scale 3D space
vec3_t camera_position = {.x = 0, .y = 0, .z = 0};
int previous_frame_time = 0;

/// Array of triangles for mesh
triangle_t *triangles_to_render = NULL;

void setup() {
  // initialize render mode and triangle culling method
  render_method = RENDER_WIRE;
  cull_method = CULL_BACKFACE;

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
  // load_obj_file_data();
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
    if (event.key.keysym.sym == SDLK_1) {
      render_method = RENDER_WIRE_VERTEX;
    } 
    if (event.key.keysym.sym == SDLK_2) {
      render_method = RENDER_WIRE;
    }
    if (event.key.keysym.sym == SDLK_3) {
      render_method = RENDER_FILL_TRIANGLE;
    }
    if (event.key.keysym.sym == SDLK_4) {
      render_method = RENDER_FILL_TRIANGLE_WIRE;
    }
    if (event.key.keysym.sym == SDLK_c) {
      cull_method = CULL_BACKFACE;
    }
    if (event.key.keysym.sym == SDLK_d) {
      cull_method = CULL_NONE;
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
  // NOTE: flipping Z because monkey obj is showing upside-down
  vec2_t projected_point = {.x = (point.x * fov_factor) / point.z,
                            .y = (point.y * fov_factor) / point.z};
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

    vec3_t transformed_vertices[3];

    // loop all three vertices of the face and apply transformations
    for (int j = 0; j < 3; j++) {
      vec3_t transformed_point = face_vertices[j];
      transformed_point = vec3_rotate_x(transformed_point, mesh.rotation.x);
      transformed_point = vec3_rotate_y(transformed_point, mesh.rotation.y);
      transformed_point = vec3_rotate_z(transformed_point, mesh.rotation.z);

      // translate the vertex away from the camera Z by a static offset
      transformed_point.z += 5;

      transformed_vertices[j] = transformed_point;
    }

    if (cull_method == CULL_BACKFACE) {
      /////////////////////////////////////////
      // cull backfaces
      /////////////////////////////////////////
      vec3_t vector_a = transformed_vertices[0];
      vec3_t vector_b = transformed_vertices[1];
      vec3_t vector_c = transformed_vertices[2];
      vec3_t vector_ab = vec3_sub(vector_b, vector_a);
      vec3_t vector_ac = vec3_sub(vector_c, vector_a);
      // When length (magnitude) of a vector is irrelevant, normalize it.
      vec3_normalize(&vector_ab);
      vec3_normalize(&vector_ac);

      // Face normal is calculated by cross product of B-A and C-A
      // NOTE: Cross product is not commutative; order matters; we go counter-clockwise
      vec3_t normal = vec3_cross(vector_ab, vector_ac);

      // "Normalize your normals"
      vec3_normalize(&normal);

      // Ray between a triangle point and the camera
      vec3_t camera_ray = vec3_sub(camera_position, vector_a);

      // If dot product between normal and cam is negative, the normal is facing away
      // from the camera and should be culled
      if (vec3_dot(normal, camera_ray) < 0) {
        continue;
      }
    }

    triangle_t projected_triangle;
    projected_triangle.color = mesh_face.color;

    // loop all three transformed vertices of the face and project them to screen space
    for (int j = 0; j < 3; j++) {
      // project point and perspective divide
      vec2_t projected_point = perspective_project(transformed_vertices[j]);
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
  SDL_RenderClear(renderer);

  draw_dotted_grid();

  int triangle_count = array_length(triangles_to_render);

  for (int i = 0; i < triangle_count; i++) {
    triangle_t tri = triangles_to_render[i];

    if (render_method == RENDER_FILL_TRIANGLE ||
        render_method == RENDER_FILL_TRIANGLE_WIRE) {
      draw_filled_triangle(tri, tri.color);
    }
    if (render_method == RENDER_FILL_TRIANGLE_WIRE || render_method == RENDER_WIRE || render_method == RENDER_WIRE_VERTEX) {
      draw_wireframe_triangle(tri, 0xFF444444);
    }
    if (render_method == RENDER_WIRE_VERTEX) {
      draw_rect(tri.points[0].x - 3, tri.points[0].y - 3, 6, 6, 0xFFFF0000);
      draw_rect(tri.points[1].x - 3, tri.points[1].y - 3, 6, 6, 0xFFFF0000);
      draw_rect(tri.points[2].x - 3, tri.points[2].y - 3, 6, 6, 0xFFFF0000);
    }
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
