#include "rasterizer.h"
#include "spriteManager.h"
#include "spriteType.h"
#include <iostream>

class Entity{
    protected:
        Polygon poly;
        Vertex pos;
        Vertex prevPos;
        Vertex direction;
        float speed;
        SpriteType type;

    public: 
        Entity(Polygon poly,Vertex pos,float speed,SpriteType type):poly(poly),pos(pos),prevPos(pos),speed(speed),type(type){};

        void drawEntity(Rasterizer* rasterizer,SpriteManager* spriteManager,float scale,double alpha){
            Vertex tempCurrent = pos;
            Vertex tempPrev = prevPos;

            tempCurrent.scale(alpha);
            tempPrev.scale(1-alpha);
            tempCurrent.add(tempPrev);

            Polygon betweenPoly = poly.add(tempCurrent).scale(scale);

            int maxy = (int) (*betweenPoly.getVerteces())[0].getY();
            int miny = (int) (*betweenPoly.getVerteces())[0].getY();
            int maxx = (int) (*betweenPoly.getVerteces())[0].getX();
            int minx = (int) (*betweenPoly.getVerteces())[0].getX();

            for(int i = 1; i < (*betweenPoly.getVerteces()).size(); i++){
                if(maxy < (int) (*betweenPoly.getVerteces())[i].getY()){
                    maxy = (int) (*betweenPoly.getVerteces())[i].getY();
                }
                if(miny > (int) (*betweenPoly.getVerteces())[i].getY()){
                    miny = (int)(*betweenPoly.getVerteces())[i].getY();
                }
                if(maxx < (int) (*betweenPoly.getVerteces())[i].getX()){
                    maxx = (int)(*betweenPoly.getVerteces())[i].getX();
                }
                if(minx > (int) (*betweenPoly.getVerteces())[i].getX()){
                    minx = (int) (*betweenPoly.getVerteces())[i].getX();
                }
            }

            int halfWidth = (*rasterizer).getWidth()/2; 
            int halfHeight = (*rasterizer).getHeight()/2;

            if(maxx + halfWidth < 0 || minx + halfWidth >= (*rasterizer).getWidth() || 
               maxy + halfHeight < 0 || miny + halfHeight >= (*rasterizer).getHeight() ){
                return;
            }

            (*rasterizer).drawSprite(betweenPoly,(*spriteManager).getSprite(rasterizer,poly,type));

        }

        SpriteType getType(){
            return type;
        }

        void update(double step,Vertex playerDir, float playerSpeed){
            playerDir.scale(playerSpeed * step * -1);

            prevPos = pos;

            pos.add(playerDir);

        }

        Vertex getDirection(){
            return direction;
        }

        float getSpeed(){
            return speed;
        }

        Polygon getPolygon(){
            return poly;
        }
};
