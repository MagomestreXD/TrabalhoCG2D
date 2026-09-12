#pragma once

#include <memory>
#include "player.h"
#include "rasterizer.h"
#include "spriteManager.h"
#include <iostream>

using namespace std;

class Game {
    private:
        unique_ptr<Player> player;
        vector<unique_ptr<Entity>> entities;
        Rasterizer rasterizer;
        SpriteManager spriteManager;
        InputState inputs;
    public:
        Game(unique_ptr<Player> player,vector<unique_ptr<Entity>> entities,Rasterizer rasterizer,SpriteManager spriteManager):player(move(player)),entities(move(entities)),rasterizer(rasterizer),spriteManager(spriteManager){
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
        }       

        void drawFrame(double alpha){

            Vertex tempCurrent = player->getPos();
            Vertex tempPrev = player->getPrevPos();

            tempCurrent.scale(alpha);
            tempPrev.scale(1-alpha);
            tempCurrent.add(tempPrev);

            rasterizer.setCamPos(tempCurrent);

            drawEntities(alpha);
            player->drawEntity(&rasterizer,&spriteManager,spriteManager.getScale(), alpha);
        }

        void drawEntities(double alpha){
            for(int i = 0; i < entities.size(); i++){
                entities[i]->drawEntity(&rasterizer,&spriteManager,spriteManager.getScale(), alpha);
            }
        }
        
        InputState* getInputs(){
            return &inputs;
        }

        void checkCollisions();

        bool checkCollision();
};
