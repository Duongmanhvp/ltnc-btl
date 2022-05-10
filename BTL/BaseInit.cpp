#include "BaseInit.h"

bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer)
{
    bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            cout <<  "Warning: Linear texture filtering not enabled!" << endl;
        }

        //Create window
        gWindow = SDL_CreateWindow( "SNAKE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            cout <<  "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if( gRenderer == NULL )
            {
                cout <<  "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    cout <<  "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

void QuitSDL(SDL_Window* &gWindow, SDL_Renderer* &gRenderer)
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

bool CheckVaCham(SDL_Rect &a, SDL_Rect &b)
{
    if(SDL_HasIntersection(&a, &b) == SDL_TRUE)return true;
    return false;
}
