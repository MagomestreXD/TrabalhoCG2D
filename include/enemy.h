#include "entity.h"

class Enemy : public Entity{
    public: 
        Enemy(Polygon poly,Vertex pos,float speed,SpriteType type):Entity(poly,pos,speed,type){}
        
        void update(){

        }
};
