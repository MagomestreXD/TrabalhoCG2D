#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "game.h"
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

    Polygon poly(vector<Vertex>{Vertex(0,0,0xFF0000FF),Vertex(32,0,0x0000FFFF),Vertex(32,32,0x00FF00FF),Vertex(0,32,0xFFFF00FF)});
 
    Polygon polyDif(vector<Vertex>{Vertex(-16,-16,0xFF0000FF),Vertex(48,-16,0x0000FFFF),Vertex(48,48,0x00FF00FF),Vertex(-16,48,0xFFFF00FF)});

    float scale = 2.0f;

    vector<unique_ptr<Entity>> entities;

    entities.push_back(
        make_unique<Entity>(poly,Vertex(-16,-16),10,SpriteType::player)
    );

    Game game(move(entities),Rasterizer(renderer,Height,Width),SpriteManager(scale));   

    game.drawFrame();   

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        Width,
        Height
    );

    SDL_UpdateTexture(texture,NULL,game.getRasterizer().getFramebuffer(), game.getRasterizer().getWidth() * sizeof(uint32_t));

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
