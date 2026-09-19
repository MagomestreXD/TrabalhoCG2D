#include "rasterizer.h"
#include "spriteManager.h"
#include "spriteType.h"
#include <iostream>
#include <iomanip>

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

            double alphaScale [3][3] = {{alpha,0,0},{0,alpha,0},{0,0,1}};
            double nAlphaScale [3][3] = {{1-alpha,0,0},{0,1-alpha,0},{0,0,1}};

            tempCurrent.multMatrix(alphaScale);
            tempPrev.multMatrix(nAlphaScale);

            double translation [3][3] = {{1,0,tempPrev.getX()},{0,1,tempPrev.getY()},{0,0,1}};

            tempCurrent.multMatrix(translation);

            double betweenPosM [3][3] = {{1,0,tempCurrent.getX()},{0,1,tempCurrent.getY()},{0,0,1}};

            float scaleM [3][3] = {{scale,0,0},{0,scale,0},{0,0,1}};

            Polygon betweenPoly = poly.multMatrix(betweenPosM).multMatrix(scaleM);

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

            int halfWidth = (*rasterizer).getWidth()/2 - (int)((*rasterizer).getCamPos().getX() * scale); 
            int halfHeight = (*rasterizer).getHeight()/2 - (int)((*rasterizer).getCamPos().getY() * scale);

            if(maxx + halfWidth < 0 || minx + halfWidth >= (*rasterizer).getWidth() || 
               maxy + halfHeight < 0 || miny + halfHeight >= (*rasterizer).getHeight() ){
                return;
            }

            (*rasterizer).drawSprite(betweenPoly,(*spriteManager).getSprite(rasterizer,poly.multMatrix(scaleM),type),false);

        }

        SpriteType getType(){
            return type;
        }

        void update(){

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

        Vertex getPos(){
            return pos;
        }

        Vertex getPrevPos(){
            return prevPos;
        }
};
