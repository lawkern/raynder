/* (c) copyright 2025 Lawrence D. Kern /////////////////////////////////////// */

#include <stdint.h>
typedef uint32_t u32;

// Renderer API
typedef struct {
   int width;
   int height;
   u32 *backbuffer;

   float red, green, blue;
} render_context;

// Platform API
_Bool create_window(int width, int height, char *title);
_Bool render_backbuffer_to_window(render_context *context);
