#include "rasterizer.h"
#include "spriteType.h"
#include <string>

class SpriteManager {
    private:
        float scale;
        vector<Texture> textures;
        vector<Texture> sprites;

    public:
        SpriteManager(float scale):scale(scale){
        }

        void iniSprites(Rasterizer* rasterizer);

        void iniTextures();

        void updateSprites(Rasterizer* rasterizer);

        Texture* getSprite(SpriteType type);

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

