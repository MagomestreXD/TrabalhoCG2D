#include "entity.h"
#include "inputState.h"

class Player : public Entity{
    public:
        Player(Polygon poly,Vertex pos,float speed,SpriteType type):Entity(poly,pos,speed,type){
            direction = Vertex(1,0);
        };
        
        void update(double step, InputState inputs){
            direction = Vertex(0,0);
            
            if(inputs.up){
                direction.add(Vertex(0,-1));
            }

            if(inputs.down){
                direction.add(Vertex(0,1));
            }

            if(inputs.left){
                direction.add(Vertex(-1,0));
            }

            if(inputs.right){
                direction.add(Vertex(1,0));
            }
        };

};

