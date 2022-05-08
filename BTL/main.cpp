// g++ snake.cpp -o snake -lSDL2 -lSDL2_image
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Current displayed texture
SDL_Texture *gTexture = NULL;

int step = 20;
int snakeBodyLength = 1;

enum
{
     RIGHT,
     LEFT,
     UP,
     DOWN
};

void snakeMove(SDL_Rect &snakeHead, SDL_Rect *snakeBody, SDL_Rect &point, int &snakeBodyLength, int direction);
SDL_Texture *loadTexture(std::string path);

int main(int argc, char *argv[])
{
     gWindow = SDL_CreateWindow("snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
     gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
     gTexture = loadTexture("images.png");
     // tạo phần đầu
     SDL_Rect snakeHead;
     snakeHead.x = SCREEN_HEIGHT / 2;
     snakeHead.y = SCREEN_WIDTH / 2;
     snakeHead.w = 20;
     snakeHead.h = 20;
     SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
     SDL_RenderFillRect(gRenderer, &snakeHead);

     // tạo phần thân
     int snakeMaxLength = SCREEN_HEIGHT * SCREEN_WIDTH / 100;
     SDL_Rect snakeBody[snakeMaxLength];
     for (int i = 0; i < snakeMaxLength; i++)
     {
          snakeBody[i].w = 20;
          snakeBody[i].h = 20;
     }

     snakeBody[0].x = snakeHead.x - 20;
     snakeBody[0].y = snakeHead.y;
     snakeBody[1].x = snakeHead.x - 40;
     snakeBody[1].y = snakeHead.y;
     snakeBody[2].x = snakeHead.x - 60;
     snakeBody[2].y = snakeHead.y;
     SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
     SDL_RenderFillRect(gRenderer, &snakeBody[0]);
     SDL_RenderFillRect(gRenderer, &snakeBody[1]);
     SDL_RenderFillRect(gRenderer, &snakeBody[2]);

     // tạo điểm ngẫu nhiên để ăn
     SDL_Rect point;
     point.w = 20;
     point.h = 20;
     srand(time(NULL));
     point.x = (rand() % (SCREEN_HEIGHT / 20 + 1)) * 20;
     point.y = (rand() % (SCREEN_WIDTH / 20 + 1)) * 20;

     SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 0xFF);
     SDL_RenderFillRect(gRenderer, &point);

     SDL_RenderPresent(gRenderer);

     int direction = RIGHT;

     bool quit = false;
     SDL_Event e;
     while (!quit)
     {
          snakeMove(snakeHead, snakeBody, point, snakeBodyLength, direction);

          // nếu đâm vào đuôi
          for (int i = 0; i < snakeBodyLength; i++)
          {
               if (snakeHead.x == snakeBody[i].x && snakeHead.y == snakeBody[i].y)
               {
                    quit = true;
                    break;
               }
          }

          // Handle events on queue
          while (SDL_PollEvent(&e) != 0)
          {

               // User requests quit
               if (e.type == SDL_QUIT)
               {
                    quit = true;
               }
               else if (e.type == SDL_KEYDOWN)
               {
                    // dua phan truoc ve vi tri sau
                    for (int i = snakeBodyLength - 1; i > 0; i--)
                    {
                         snakeBody[i].x = snakeBody[i - 1].x;
                         snakeBody[i].y = snakeBody[i - 1].y;
                    }
                    snakeBody[0].x = snakeHead.x;
                    snakeBody[0].y = snakeHead.y;
                    if (direction == LEFT)
                    {
                         if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
                         {
                              direction = DOWN;
                         }
                         if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
                         {
                              direction = UP;
                         }
                    }

                    if (direction == RIGHT)
                    {

                         if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
                         {
                              direction = DOWN;
                         }
                         if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
                         {
                              direction = UP;
                         }
                    }

                    if (direction == UP)
                    {
                         if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
                         {
                              direction = LEFT;
                         }
                         if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
                         {
                              direction = RIGHT;
                         }
                    }

                    if (direction == DOWN)
                    {
                         if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
                         {
                              direction = LEFT;
                         }
                         if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
                         {
                              direction = RIGHT;
                         }
                    }

                    if (snakeHead.x == point.x && snakeHead.y == point.y)
                    {
                         // chuyển point ra chỗ khác
                         point.x = (rand() % (SCREEN_HEIGHT / 20)) * 20;
                         point.y = (rand() % (SCREEN_WIDTH / 20)) * 20;
                         snakeBodyLength++;
                         snakeBody[snakeBodyLength - 1].x = snakeBody[snakeBodyLength - 2].x;
                         snakeBody[snakeBodyLength - 1].y = snakeBody[snakeBodyLength - 2].y;
                    }
                    // vẽ lại cái để ăn
                    SDL_SetRenderDrawColor(gRenderer, 255, 51, 0, 0xFF);
                    SDL_RenderFillRect(gRenderer, &point);
                    snakeMove(snakeHead, snakeBody, point, snakeBodyLength, direction);
               }
          }
     }
     return 0;
}

void snakeMove(SDL_Rect &snakeHead, SDL_Rect *snakeBody, SDL_Rect &point, int &snakeBodyLength, int direction)
{
     // di chuyển phần thân
     for (int i = snakeBodyLength - 1; i > 0; i--)
     {
          snakeBody[i].x = snakeBody[i - 1].x;
          snakeBody[i].y = snakeBody[i - 1].y;
     }
     snakeBody[0].x = snakeHead.x;
     snakeBody[0].y = snakeHead.y;

     if (direction == LEFT)
     {
          snakeHead.x = (snakeHead.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
     }
     else if (direction == RIGHT)
     {
          snakeHead.x = (snakeHead.x + step) % SCREEN_WIDTH;
     }
     else if (direction == DOWN)
     {
          snakeHead.y = (snakeHead.y + step) % SCREEN_HEIGHT;
     }
     else if (direction == UP)
     {
          snakeHead.y = (snakeHead.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
     }

     SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
     SDL_RenderClear(gRenderer);

     SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

     // ve lai cai dau
     SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
     SDL_RenderFillRect(gRenderer, &snakeHead);
     SDL_SetRenderDrawColor(gRenderer, 102, 255, 51, 0xFF);
     for (int i = 0; i < snakeBodyLength; i++)
     {
          SDL_RenderFillRect(gRenderer, &snakeBody[i]);
     }
     if (snakeHead.x == point.x && snakeHead.y == point.y)
     {
          // chuyển point ra chỗ khác
          point.x = (rand() % (SCREEN_HEIGHT / 20)) * 20;
          point.y = (rand() % (SCREEN_WIDTH / 20)) * 20;
          snakeBodyLength++;
          snakeBody[snakeBodyLength - 1].x = snakeBody[snakeBodyLength - 2].x;
          snakeBody[snakeBodyLength - 1].y = snakeBody[snakeBodyLength - 2].y;
     }
     // vẽ lại cái để ăn
     SDL_SetRenderDrawColor(gRenderer, 255, 51, 0, 0xFF);
     SDL_RenderFillRect(gRenderer, &point);

     SDL_RenderPresent(gRenderer);
     SDL_Delay(100);
}

SDL_Texture *loadTexture(std::string path)
{
     // The final texture
     SDL_Texture *newTexture = NULL;

     // Load image at specified path
     SDL_Surface *loadedSurface = IMG_Load(path.c_str());
     if (loadedSurface == NULL)
     {
          printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
     }
     else
     {
          // Create texture from surface pixels
          newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
          if (newTexture == NULL)
          {
               printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
          }

          // Get rid of old loaded surface
          SDL_FreeSurface(loadedSurface);
     }

     return newTexture;
}