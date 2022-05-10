#ifndef snake_move_h_
#define snake_move_h_

#include "BaseInit.h"

class SnakeClass
{

public:
     static const int step = 20;
     // tao phan dau
     static const int snakeBodyLength = 2;
     SDL_Rect snakeHead;

     // tạo phần thân
     static const int snakeMaxLength = SCREEN_HEIGHT * SCREEN_WIDTH / 20;
     SDL_Rect snakeBody[snakeMaxLength];

     int direction;

     SnakeClass();
     ~SnakeClass();
     void handleMove(SDL_Event &e);
     void renderSnake(SDL_Renderer *&gRenderer);
     void snakeMove(SDL_Rect &point);
     bool gameOver();
};
#endif
