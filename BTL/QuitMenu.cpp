#include "QuitMenu.h"

bool outside(int x, int y, SDL_Rect a)
{
     if (x < a.x || y < a.y || x > a.x + a.w || y > a.y + a.h)
          return false;
     return true;
}

bool QuitGame(SDL_Renderer* &gRenderer)
{
     SDL_Texture *Texture = loadTexture("images.png", gRenderer);
     while (true)
     {
          SDL_RenderClear(gRenderer);
          SDL_Rect desrect = {0, 0, 800, 800};
          SDL_RenderCopy(gRenderer, Texture, NULL, &desrect);
          SDL_Color gColor = {255, 255, 0};
          SDL_Rect playRect = renderTextTexture(gRenderer, "VeraMoBd.ttf", "PLAY AGAIN", 30, gColor, 330, 660);
          SDL_Rect endRect = renderTextTexture(gRenderer, "VeraMoBd.ttf", "EXIT", 30, gColor, 380, 690);
          SDL_Event e;

          if (SDL_PollEvent(&e) != 0)
          {
               if (e.type == SDL_QUIT)
                    return 0;

               if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
               {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    if (outside(x, y, playRect) == true)
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
                    if (outside(x, y, endRect) == true)
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
