#include "BaseInit.h"
#include "LoadTexture.h"
#include "SnakeMove.h"
#include "Target.h"
#include "Menu.h"

int main(int argc, char *argv[])
{
     // The window we'll be rendering to
     SDL_Window *gWindow = NULL;

     // The window renderer
     SDL_Renderer *gRenderer = NULL;

     // The Texture
     SDL_Texture *gTexture = NULL;

     // Crete seed random
     srand(time(NULL));

     init(gWindow, gRenderer);

     if (MenuGame(gRenderer) == true)
     {
          gTexture = loadTexture("image.png", gRenderer);

          SnakeClass snake;
          Target target;

          bool quit = false;
          long long loop = 0;

          while (!quit)
          {
               loop++;
               SDL_Event e;

               for (int i = 0; i < SnakeClass().snakeBodyLength; i++)
               {
                    if (SnakeClass().snakeHead.x == SnakeClass().snakeBody[i].x && SnakeClass().snakeHead.y == SnakeClass().snakeBody[i].y)
                    {
                         quit = true;
                         break;
                    }
               }

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

               // The Image Background
               SDL_Rect desrect = {0, 0, 800, 800};
               SDL_RenderCopy(gRenderer, gTexture, NULL, &desrect);

               snake.renderSnake(gRenderer);
               target.renderTarget(gRenderer);

               // The Scores
               render_scores(gRenderer, snake.snakeBodyLength);

               SDL_RenderPresent(gRenderer);
          }
     }

     QuitSDL(gWindow, gRenderer);
     return 0;
}