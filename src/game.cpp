#include "game.h"

void Game::checkCollisions(){
    for(int i = 0; i < entities.size() - 1; i++){
        for(int j = i + 1; j < entities.size();j++){
            checkCollision(entities[i]->getPolygon().add(entities[i]->getPos()),entities[j]->getPolygon().add(entities[j]->getPos()));
        }
    }

    for(int i = 0; i < entities.size(); i++){
        checkCollision(player->getPolygon().add(player->getPos()),entities[i]->getPolygon().add(entities[i]->getPos()));       
    }  

}

bool Game::checkCollision(Polygon pa, Polygon pb){
    
    vector<Vertex>* va = pa.getVerteces();
    vector<Vertex>* vb = pb.getVerteces();

    float maxya = (*va)[0].getY();
    float minya = (*va)[0].getY();
    float maxxa = (*va)[0].getX();
    float minxa = (*va)[0].getX();

    float maxyb = (*vb)[0].getY();
    float minyb = (*vb)[0].getY();
    float maxxb = (*vb)[0].getX();
    float minxb = (*vb)[0].getX();

    for(int i = 1; i < (*va).size(); i++){
        if(maxya < (*va)[i].getY()){
            maxya = (*va)[i].getY();
        }
        if(minya > (*va)[i].getY()){
            minya = (*va)[i].getY();
        }
        if(maxxa < (*va)[i].getX()){
            maxxa = (*va)[i].getX();
        }
        if(minxa > (*va)[i].getX()){
            minxa = (*va)[i].getX();
        }
    }
 
    for(int i = 1; i < (*vb).size(); i++){
        if(maxyb < (*vb)[i].getY()){
            maxyb = (*vb)[i].getY();
        }
        if(minyb > (*vb)[i].getY()){
            minyb = (*vb)[i].getY();
        }
        if(maxxb < (*vb)[i].getX()){
            maxxb = (*vb)[i].getX();
        }
        if(minxb > (*vb)[i].getX()){
            minxb = (*vb)[i].getX();
        }
    }
    if(maxxa < minxb || maxya < minyb || maxxb < minxa || maxyb < minya){
        return false;
    }

    cout<<"tocando"<<endl;
    return true;
}
