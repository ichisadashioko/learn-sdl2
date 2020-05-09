#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int main(int argc, char **argv)
{
    // https://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world

    // start SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }

    // open a window
    cout << "prepare to create a window" << endl;
    SDL_Window *win = SDL_CreateWindow("SDL window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // create a renderer
    cout << "creating renderer" << endl;
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        SDL_DestroyWindow(win);
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // load a bitmap image
    cout << "arguments:" << endl;
    for (int i = 0; i < argc; i++)
    {
        cout << i << " - " << argv[i] << endl;
    }

    if (argc < 2)
    {
        cout << "please supply the image path to display" << endl;
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    string imagePath = argv[1];
    SDL_Surface *img = IMG_Load(imagePath.c_str());
    if (img == nullptr)
    {
        cout << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    if (tex == nullptr)
    {
        cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // draw the texture
    for (int i = 0; i < 3; i++)
    {
        // first clear the renderer
        SDL_RenderClear(ren);
        // draw the texture
        SDL_RenderCopy(ren, tex, NULL, NULL);
        // update the screen
        SDL_RenderPresent(ren);
        SDL_Delay(1000);
    }

    SDL_Delay(2000);

    // clean up
    cout << "cleaning up" << endl;
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}