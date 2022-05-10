#ifndef Load_Texture_h_
#define Load_Texture_h_

#include "BaseInit.h"

SDL_Texture *loadTexture(std::string path, SDL_Renderer *&gRenderer);
void renderTextTexture(SDL_Renderer *&gRenderer, const std::string &fontName,
                       const std::string &content, const int &fontSize,
                       const SDL_Color &fcolor, const int &x, const int &y);
#endif
