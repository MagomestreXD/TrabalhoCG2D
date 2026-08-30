#include "entity.h"

class Enemy : public Entity{
    public: 
        Enemy(Polygon poly,Vertex pos,float speed,SpriteType type):Entity(poly,pos,speed,type){}
        
        void update(double step,Vertex playerDir, float playerSpeed){
            playerDir.scale(playerSpeed * step * -1);

            prevPos = pos;

            pos.add(playerDir);

        }
};
