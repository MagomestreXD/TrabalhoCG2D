#pragma once
#include "spriteType.h"

class SpriteKey{
    private:
        SpriteType type;
    public:
        SpriteKey(SpriteType type):type(type){}
        
        SpriteType getSpriteType() const{
            return type;
        }

        bool operator== (const SpriteKey& outro) const{
            return type == outro.getSpriteType();
        }
};
