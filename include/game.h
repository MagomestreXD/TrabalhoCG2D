#pragma once

#include <memory>
#include "entity.h"
#include "rasterizer.h"
#include "spriteManager.h"
#include <iostream>

using namespace std;

class Game {
    private:
        vector<unique_ptr<Entity>> entities;
        Rasterizer rasterizer;
        SpriteManager spriteManager;
    public:
        Game(vector<unique_ptr<Entity>> entities,Rasterizer rasterizer,SpriteManager spriteManager):entities(move(entities)),rasterizer(rasterizer),spriteManager(spriteManager){
            iniGame();
        };

        void iniGame(){
            spriteManager.iniSprites(&rasterizer);
        }

        vector<unique_ptr<Entity>>& getEntities(){
            return entities;
        }

        Rasterizer* getRasterizer(){
            return &rasterizer;
        }

        void updateLogic(double step){
            for(int i = 0; i < entities.size(); i++){
                entities[i]->update(step);
            }
        }       

        void drawFrame(double alpha){
            drawEntities(alpha);
        }

        void drawEntities(double alpha){
            for(int i = 0; i < entities.size(); i++){
                entities[i]->drawEntity(&rasterizer,spriteManager.getSprite(entities[i]->getType()),spriteManager.getScale(), alpha);
            }
        }
        
};
