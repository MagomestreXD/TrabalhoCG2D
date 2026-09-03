#pragma once
#include "rasterizer.h"
#include "spriteType.h"
#include "spriteKey.h"
#include "sprite.h"
#include <string>
#include <optional>

class SpriteManager {
    private:
        float scale;
        vector<optional<Texture>> textures;
        vector<Sprite> sprites;

    public:
        SpriteManager(float scale):scale(scale),textures(vector<optional<Texture>>(static_cast<int>(SpriteType::Count))){
        }

        void loadTexture(SpriteKey* key);

        void loadSprite(Rasterizer* rasterizer,Polygon* poly,SpriteKey* key);

        Texture* getSprite(Rasterizer* rasterizer,Polygon poly,SpriteType type);

        void emptySprites();

        float getScale(){
            return scale;
        }
    
        void setScale(float f){
            scale = f;
            return;
        }

        void multiplyScale(float f){
            scale = scale * f;
            return;
        }
};

