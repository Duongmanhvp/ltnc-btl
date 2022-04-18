// g++ snake.cpp -o snake -lSDL2 -lSDL2_image
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>

// Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

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
int main(int argc, char *argv[])
{
     gWindow = SDL_CreateWindow("snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
     gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

     // tạo phần đầu
     SDL_Rect snakeHead;
     snakeHead.x = SCREEN_HEIGHT / 2;
     snakeHead.y = SCREEN_WIDTH / 2;
     snakeHead.w = 20;
     snakeHead.h = 20;
     SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
     SDL_RenderFillRect(gRenderer, &snakeHead);