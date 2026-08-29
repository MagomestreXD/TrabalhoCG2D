#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
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

    rasterizer.clearFrameBuffer();

    SDL_Surface* surface = IMG_Load("resources/bruh.png");

    if (surface == nullptr) {
        SDL_Log("Erro ao carregar PNG: %s", SDL_GetError());
    }

    SDL_Surface* rgba = SDL_ConvertSurface(surface,SDL_PIXELFORMAT_RGBA8888);

    SDL_DestroySurface(surface);

    surface = rgba;

    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);

    Texture gato(32,32,pixels);

    Polygon poly(vector<Vertex>{Vertex(-16,-16,0xFF0000FF),Vertex(16,-16,0x0000FFFF),Vertex(16,16,0x00FF00FF),Vertex(-16,16,0xFFFF00FF)});
 
    Polygon polyDif(vector<Vertex>{Vertex(-16,-16,0xFF0000FF),Vertex(48,-16,0x0000FFFF),Vertex(48,48,0x00FF00FF),Vertex(-16,48,0xFFFF00FF)});

    float scale = 2.0f;

    Texture spriteGato = rasterizer.scanLineNearestNeighbor(poly.scale(scale),gato);

    rasterizer.drawSprite(polyDif.scale(scale),spriteGato);

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
    
    free(spriteGato.getData());

    return 0;
}
