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

        void drawEntity(Rasterizer* rasterizer,Texture sprite,float scale,double alpha){
            Vertex tempCurrent = pos;
            Vertex tempPrev = prevPos;

            tempCurrent.scale(alpha);
            tempPrev.scale(1-alpha);
            tempCurrent.add(tempPrev);

            (*rasterizer).drawSprite(poly.add(tempCurrent).scale(scale),sprite);
        }

        SpriteType getType(){
            return type;
        }

        void update(double step){
            direction = Vertex(1,0);
            direction.scale(speed * step);

            prevPos = pos;

            pos.add(direction);
        }
};
