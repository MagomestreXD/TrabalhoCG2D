#include "spriteType.h"
#include "spriteKey.h"
#include "texture.h"

class Sprite{
    private:
        Texture data;
        SpriteKey key;
    public:
        Sprite(Texture data,SpriteKey key):data(move(data)),key(key){}

        Texture* getData(){
            return &data;
        }

        SpriteKey* getKey(){
            return &key;
        }
};
