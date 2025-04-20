/* (c) copyright 2025 Lawrence D. Kern /////////////////////////////////////// */

#include <stdlib.h>
#include "raynder.h"

static void render_scene_to_backbuffer(render_context *context)
{
   context->red += 0.01;
   if(context->red > 1.0f) context->red -= 1.0f;

   context->blue += 0.005;
   if(context->blue > 1.0f) context->blue -= 1.0f;

   u32 r = (u32)(255.0f * context->red)   << 24;
   u32 g = (u32)(255.0f * context->green) << 16;
   u32 b = (u32)(255.0f * context->blue)  << 8;
   u32 a = 0xFF;

   u32 color = r|g|b|a;

   int pixel_count = context->width * context->height;
   if(!context->backbuffer)
   {
      size_t size = pixel_count * sizeof(*context->backbuffer);
      context->backbuffer = calloc(1, size);
   }

   for(int index = 0; index < pixel_count; ++index)
   {
      context->backbuffer[index] = color;
   }
}

int main(void)
{
   render_context context = {.width = 1920>>1, .height = 1080>>1};

   if(create_window(context.width, context.height, "Raynder"))
   {
      do render_scene_to_backbuffer(&context);
      while(render_backbuffer_to_window(&context));
   }

   return(0);
}
