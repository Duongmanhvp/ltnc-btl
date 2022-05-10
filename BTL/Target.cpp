#include "Target.h"

Target::Target()
{
     // tạo điểm ngẫu nhiên để ăn
     point.x = (rand() % (SCREEN_WIDTH / 20 + 1)) * 20;
     point.y = (rand() % (SCREEN_HEIGHT / 20 + 1)) * 20;
     point.w = 20;
     point.h = 20;
}

Target::~Target()
{
}

void Target::renderTarget(SDL_Renderer *&gRenderer)
{
     SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 0xFF);
     SDL_RenderFillRect(gRenderer, &point);
}
