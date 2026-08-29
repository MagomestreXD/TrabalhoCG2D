#include "rasterizer.h"
#include "spriteType.h"

class Entity{
    private:
        Polygon poly;
        Vertex pos;
        Vertex prevPos;
        Vertex direction;
        float speed;
        SpriteType type;
    public: 
        Entity(Polygon poly,Vertex pos,float speed,SpriteType type):poly(poly),pos(pos),prevPos(pos),speed(speed),type(type){};

        void drawEntity(Rasterizer* rasterizer,Texture sprite,float scale){
            (*rasterizer).drawSprite(poly.scale(scale),sprite);
        }

        SpriteType getType(){
            return type;
        }
};
