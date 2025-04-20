/* (c) copyright 2025 Lawrence D. Kern /////////////////////////////////////// */

#include <SDL3/SDL.h>
#include "raynder.h"

static SDL_Window   *the_window;
static SDL_Renderer *the_renderer;
static SDL_Texture  *the_texture;

_Bool create_window(int width, int height, char *title)
{
   _Bool success = false;

   if(SDL_CreateWindowAndRenderer(title, width, height, SDL_WINDOW_HIGH_PIXEL_DENSITY, &the_window, &the_renderer))
   {
      if(!SDL_SetRenderVSync(the_renderer, 1))
      {
         SDL_Log("WARNING: Failed to set vsync.");
      }

      the_texture = SDL_CreateTexture(the_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
      if(the_texture)
      {
         success = true;
      }
      else
      {
         SDL_Log("ERROR: Failed to create texture.");
      }
   }
   else
   {
      SDL_Log("ERROR: Failed to create window/renderer.");
   }

   return(success);
}

_Bool render_backbuffer_to_window(render_context *context)
{
   _Bool keep_renderering = true;

   SDL_Event event;
   while(SDL_PollEvent(&event))
   {
      switch(event.type)
      {
         case SDL_EVENT_QUIT: keep_renderering = false; break;
         case SDL_EVENT_KEY_DOWN: if(event.key.key == SDLK_ESCAPE) keep_renderering = false; break;
      }
   }

   SDL_SetRenderDrawColor(the_renderer, 0x28, 0x28, 0x28, 0xFF);
   SDL_RenderClear(the_renderer);

   SDL_UpdateTexture(the_texture, 0, context->backbuffer, context->width * sizeof(*context->backbuffer));
   SDL_RenderTexture(the_renderer, the_texture, 0, 0);

   SDL_RenderPresent(the_renderer);

   return(keep_renderering);
}
