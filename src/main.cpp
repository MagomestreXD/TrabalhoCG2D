#include <SDL3/SDL.h>
#include <iostream>
#include "rasterizer.h"
#define Width 1280
#define Height 720

using namespace std;

int main(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        cout << "SDL3 init Error: " << SDL_GetError() << endl;
        return 1;

    }

    SDL_Window *window = SDL_CreateWindow("Jogo",Width,Height,0);

    //SDL_SetWindowFullscreen(window, true);

    if(window == NULL){
        cout << "SDL3 init Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    Rasterizer rasterizer (renderer,Height,Width);   

    for(int i = 0; i < Width; i++){
        for(int j = 0; j < Height; j++){
            rasterizer.setPixel(i,j,0xFFFFFFFF);
        }
    }

    Polygon poly(vector<Vertex>{Vertex(100,100,0xFF0000FF),Vertex(150,150,0x0000FFFF),Vertex(100,200,0x00FF00FF),Vertex(200,200,0xFFFF00FF),Vertex(200,100,0x00FFFFFF)});

    rasterizer.scanLine(poly);

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        Width,
        Height
    );

    SDL_UpdateTexture(texture,NULL,rasterizer.getFramebuffer(), rasterizer.getWidth() * sizeof(uint32_t));

    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer,texture,NULL,NULL);

    SDL_RenderPresent(renderer);

    bool running = true;

    while(running){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
