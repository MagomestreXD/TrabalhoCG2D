#include <SDL3/SDL.h>
#include <iostream>
#include "rasterizer.h"

using namespace std;

int main(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        cout << "SDL3 init Error: " << SDL_GetError() << endl;
        return 1;

    }

    SDL_Window *window = SDL_CreateWindow("Jogo",800,800,0);

    if(window == NULL){
        cout << "SDL3 init Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    Rasterizer rasterizer (renderer,800,800);   

    for(int i = 0; i< 800; i++){
        for(int j = 0; j < 800; j++){
            rasterizer.setPixel(i,j,0xFFFFFFFF);
        }
    }

    rasterizer.drawElipse(399,399,300,100,0x00FF00FF);
    rasterizer.drawElipse(399,399,100,300,0xFF0000FF);

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
