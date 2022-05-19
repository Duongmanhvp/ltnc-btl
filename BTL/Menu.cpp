#include "Menu.h"

bool inside(int x, int y, SDL_Rect a)
{
     if (x < a.x || y < a.y || x > a.x + a.w || y > a.y + a.h)
          return false;
     return true;
}

bool MenuGame(SDL_Renderer *&gRenderer)
{
     SDL_Texture *Texture = loadTexture("start.png", gRenderer);
     while (true)
     {
          SDL_RenderClear(gRenderer);
          SDL_Rect desrect = {0, 0, 800, 800};
          SDL_RenderCopy(gRenderer, Texture, NULL, &desrect);
          SDL_Color gColor = {255, 255, 0};
          SDL_Rect playRect = renderTextTexture(gRenderer, "VeraMoBd.ttf", "PLAY", 60, gColor, 300, 500);
          SDL_Rect endRect = renderTextTexture(gRenderer, "VeraMoBd.ttf", "EXIT", 60, gColor, 300, 560);
          SDL_Event e;

          if (SDL_PollEvent(&e) != 0)
          {
               if (e.type == SDL_QUIT)
                    return 0;

               if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
               {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    if (inside(x, y, playRect) == true)
                    {
                         switch (e.type)
                         {
                         case SDL_MOUSEMOTION:
                              break;
                         case SDL_MOUSEBUTTONDOWN:
                              return 1;
                         default:
                              break;
                         }
                    }
                    if (inside(x, y, endRect) == true)
                    {
                         switch (e.type)
                         {
                         case SDL_MOUSEMOTION:
                              break;
                         case SDL_MOUSEBUTTONDOWN:
                              return 0;
                         default:
                              break;
                         }
                    }
               }
          }
          SDL_RenderPresent(gRenderer);
     }
}
