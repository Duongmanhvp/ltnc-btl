// g++ snake.cpp -o snake -lSDL2 -lSDL2_image
#include "BaseInit.h"
#include "LoadTexture.h"
#include "SnakeMove.h"
#include "Target.h"

int main(int argc, char *argv[])
{
     // The window we'll be rendering to
     SDL_Window *gWindow = NULL;

     // The window renderer
     SDL_Renderer *gRenderer = NULL;

     // Crete seed random
     srand(time(NULL));

     init(gWindow, gRenderer);

     SnakeClass snake;
     Target target;

     bool quit = false;
     long long loop = 0;

     while (!quit)
     {
          loop++;
          SDL_Event e;

          // Handle events on queue
          while (SDL_PollEvent(&e) != 0)
          {
               // User requests quit
               if (e.type == SDL_QUIT || snake.gameOver() == true)
               {
                    quit = true;
               }
               snake.handleMove(e);
          }

          if (loop % 5 == 0)
               snake.snakeMove(target.point);

          // Clear screen
          SDL_SetRenderDrawColor(gRenderer, 0, 191, 255, 0);
          SDL_RenderClear(gRenderer);

          snake.renderSnake(gRenderer);
          target.renderTarget(gRenderer);

          // The TextColor
          SDL_Color gColor = {255, 0, 0};
          renderTextTexture(gRenderer, "VeraMoBd.ttf", "Your Scores: ", 30, gColor, 50, 50);

          SDL_RenderPresent(gRenderer);
     }

     QuitSDL(gWindow, gRenderer);
     return 0;
}
