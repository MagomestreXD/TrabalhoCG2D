#include "spriteManager.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>


void SpriteManager::loadTexture(SpriteKey* key){

    string path;

    switch(static_cast<SpriteType>((*key).getSpriteType())){
        case SpriteType::player:
            path = "resources/bruh.png";
            break;
        case SpriteType::inimigo:
            path = "resources/inimigo.png";
            break;
        default:
            path = "resources/bruh.png";
            break;
    }

    SDL_Surface* surface = IMG_Load(path.c_str());

    if(surface == nullptr){
        SDL_Log("Erro ao carregar %s: %s", path.c_str(), SDL_GetError());
    }

    SDL_Surface* rgba = SDL_ConvertSurface(surface,SDL_PIXELFORMAT_RGBA8888);

    if(rgba == nullptr){
        SDL_Log("Erro ao carregar %s: %s", path.c_str(), SDL_GetError());
        SDL_DestroySurface(surface);
        return;
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

    textures[static_cast<int>((*key).getSpriteType())] = texture;

}

void SpriteManager::loadSprite(Rasterizer* rasterizer,Polygon* poly,SpriteKey* key){

    int index = static_cast<int>((*key).getSpriteType());

    if(!textures[index].has_value()){
        loadTexture(key);
        cout << "loaded texture: " << static_cast<int>((*key).getSpriteType()) << endl;
    }
    
    sprites.push_back(Sprite((*rasterizer).scanLineNearestNeighbor((*poly).scale(scale),textures[index].value()), *key));           

    return;

}

Texture* SpriteManager::getSprite(Rasterizer* rasterizer,Polygon poly,SpriteType type){
    SpriteKey key(type);

    for(Sprite& sprite: sprites){
        if(*sprite.getKey() == key){
            return sprite.getData();
        }
    }

    loadSprite(rasterizer,&poly,&key);
    cout << "loaded sprite: " << static_cast<int>(type) << endl;

    for(Sprite& sprite: sprites){
        if(*sprite.getKey() == key){
            return sprite.getData();
        }
    }

    return NULL;
}

void SpriteManager::emptySprites(){

    sprites.clear();
}

