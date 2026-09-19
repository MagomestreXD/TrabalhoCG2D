#pragma once

#include <memory>
#include "player.h"
#include "rasterizer.h"
#include "spriteManager.h"
#include "room.h"
#include <iostream>

using namespace std;

class Game {
    private:
        unique_ptr<Player> player;
        vector<unique_ptr<Entity>> entities;
        Room room;
        Rasterizer rasterizer;
        SpriteManager spriteManager;
        InputState inputs;
        int round = 1;

    public:
        Game(unique_ptr<Player> player,vector<unique_ptr<Entity>> entities,Rasterizer rasterizer,SpriteManager spriteManager,Room room):player(move(player)),entities(move(entities)),rasterizer(rasterizer),spriteManager(spriteManager),room(room){
        };

        void iniGame(){
        }

        vector<unique_ptr<Entity>>& getEntities(){
            return entities;
        }

        Rasterizer* getRasterizer(){
            return &rasterizer;
        }

        SpriteManager* getSpriteManager(){
            return &spriteManager;
        }

        void updateLogic(double step){
            player->update(step,inputs);
            for(int i = 0; i < entities.size(); i++){
                entities[i]->update();
            }

            checkCollisions();
        }       

        void drawFrame(double alpha){

            Vertex tempCurrent = player->getPos();
            Vertex tempPrev = player->getPrevPos();

            double alphaScale [3][3] = {{alpha,0,0},{0,alpha,0},{0,0,1}};
            double nAlphaScale [3][3] = {{1-alpha,0,0},{0,1-alpha,0},{0,0,1}};

            tempCurrent.multMatrix(alphaScale);
            tempPrev.multMatrix(nAlphaScale);

            double translation [3][3] = {{1,0,tempPrev.getX()},{0,1,tempPrev.getY()},{0,0,1}};

            tempCurrent.multMatrix(translation);

            rasterizer.setCamPos(tempCurrent);

            room.draw(&rasterizer,&spriteManager,spriteManager.getScale());
            drawEntities(alpha);
            player->drawEntity(&rasterizer,&spriteManager,spriteManager.getScale(), alpha);
        }

        void drawEntities(double alpha){
            for(int i = 0; i < entities.size(); i++){
                entities[i]->drawEntity(&rasterizer,&spriteManager,spriteManager.getScale(),alpha);
            }
        }
        
        InputState* getInputs(){
            return &inputs;
        }

        void checkCollisions();

        bool checkCollision(Polygon polya, Polygon polyb, Vertex posa, Vertex posb);

        bool testSAT(Polygon* pa,Polygon* pb);
};
