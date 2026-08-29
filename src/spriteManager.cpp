#include "spriteManager.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>


void SpriteManager::iniTextures(){

    for(int i = 0; i < static_cast<int>(SpriteType::Count); i++){
        string path;

        switch(static_cast<SpriteType>(i)){
            case SpriteType::player:
                path = "resources/bruh.png";
                break;
            default:
                path = "resources/bruh.png";
                break;
        }

        SDL_Surface* surface = IMG_Load(path.c_str());

        if(surface == nullptr){
            SDL_Log("Erro ao carregar %s: %s", path.c_str(), SDL_GetError());
            continue;
        }

        SDL_Surface* rgba = SDL_ConvertSurface(surface,SDL_PIXELFORMAT_RGBA8888);

        if(rgba == nullptr){
            SDL_Log("Erro ao carregar %s: %s", path.c_str(), SDL_GetError());
            SDL_DestroySurface(surface);
            continue;
        }

        SDL_DestroySurface(surface);

        surface = rgba;

        uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);

        Texture texture(surface->w,surface->h);

        for (int y = 0; y < surface->h; y++) {
            for (int x = 0; x < surface->w; x++) {
                texture.getData()[y * surface->w + x] = pixels[y * surface->w + x];
            }
        }

        SDL_DestroySurface(surface);

        textures.push_back(texture);
    }

}

void SpriteManager::iniSprites(Rasterizer* rasterizer){

    iniTextures();

    Polygon basePoly(vector<Vertex>{Vertex(0,0),Vertex(32,0),Vertex(32,32),Vertex(0,32)});

    for(int i = 0; i < static_cast<int>(SpriteType::Count); i++){
        sprites.push_back((*rasterizer).scanLineNearestNeighbor(basePoly,textures[i]));
    }

}

void SpriteManager::updateSprites(Rasterizer* rasterizer,float scale){

    Polygon basePoly(vector<Vertex>{Vertex(0,0),Vertex(32,0),Vertex(32,32),Vertex(0,32)});

    Polygon poly = basePoly.scale(scale);

    for(int i = 0; i < sprites.size();i++){
        sprites[i] = (*rasterizer).scanLineNearestNeighbor(poly,textures[i]);
    }

}

Texture SpriteManager::getSprite(SpriteType type){
    return sprites[static_cast<int>(type)];
}
