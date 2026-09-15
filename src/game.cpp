#include "game.h"

void Game::checkCollisions(){
    for(int i = 0; i < entities.size() - 1; i++){
        for(int j = i + 1; j < entities.size();j++){
            checkCollision(entities[i]->getPolygon(),entities[j]->getPolygon(),entities[i]->getPos(),entities[j]->getPos());
        }
    }

    for(int i = 0; i < entities.size(); i++){
        checkCollision(player->getPolygon(),entities[i]->getPolygon(),player->getPos(),entities[i]->getPos());       
    }  

}

bool Game::checkCollision(Polygon polya, Polygon polyb, Vertex posa, Vertex posb){
    float minDistanceSqrd = 5200;

    float xdistance = posa.getX() - posb.getX();
    float ydistance = posa.getY() - posb.getY();

    float distSqrd = (xdistance * xdistance) + (ydistance * ydistance);

    if(distSqrd > minDistanceSqrd){
        cout<<"evitei checkBox"<<endl;
        return false;
    }
    
    float transPosA [3][3] = {{1,0,posa.getX()},{0,1,posa.getY()},{0,0,1}};
    float transPosB [3][3] = {{1,0,posb.getX()},{0,1,posb.getY()},{0,0,1}};

    Polygon pa = polya.multMatrix(transPosA);
    Polygon pb = polyb.multMatrix(transPosB);

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
        cout<<"checkbox negativo"<<endl;
        return false;
    }

    if(!testSAT(&pa,&pb)){
        return false;
    }

    cout<<"tocando"<<endl;
    return true;
}

bool Game::testSAT(Polygon* pa,Polygon* pb){

    for(int i = 0; i < pa->getVerteces()->size(); i++){
        int next = (i + 1) % pa->getVerteces()->size();
        
        float axisx = (*pa->getVerteces())[i].getY() - (*pa->getVerteces())[next].getY();
        float axisy = (*pa->getVerteces())[next].getX() - (*pa->getVerteces())[i].getX();

        float minproja = ( (*pa->getVerteces())[0].getX() * axisx + (*pa->getVerteces())[0].getY() * axisy );
        float maxproja = ( (*pa->getVerteces())[0].getX() * axisx + (*pa->getVerteces())[0].getY() * axisy );

        float proj;

        for(int i = 1; i < pa->getVerteces()->size();i++){
            proj = ( (*pa->getVerteces())[i].getX() * axisx + (*pa->getVerteces())[i].getY() * axisy );
            if(proj < minproja){
                minproja = proj;
            }
            if(proj > maxproja){
                maxproja = proj;
            }
        }

        float minprojb = ( (*pb->getVerteces())[0].getX() * axisx + (*pb->getVerteces())[0].getY() * axisy );
        float maxprojb = ( (*pb->getVerteces())[0].getX() * axisx + (*pb->getVerteces())[0].getY() * axisy );

        for(int i = 1; i < pb->getVerteces()->size();i++){
            proj = ( (*pb->getVerteces())[i].getX() * axisx + (*pb->getVerteces())[i].getY() * axisy );
            if(proj < minprojb){
                minprojb = proj;
            }
            if(proj > maxprojb){
                maxprojb = proj;
            }
        }

        if(minproja > maxprojb || maxproja < minprojb){
            return false;
        }
    }

    for(int i = 0; i < pb->getVerteces()->size(); i++){
        int next = (i + 1) % pb->getVerteces()->size();
        
        float axisx = (*pb->getVerteces())[i].getY() - (*pb->getVerteces())[next].getY();
        float axisy = (*pb->getVerteces())[next].getX() - (*pb->getVerteces())[i].getX();

        float minprojb = ( (*pb->getVerteces())[0].getX() * axisx + (*pb->getVerteces())[0].getY() * axisy );
        float maxprojb = ( (*pb->getVerteces())[0].getX() * axisx + (*pb->getVerteces())[0].getY() * axisy );

        float proj;

        for(int i = 1; i < pb->getVerteces()->size();i++){
            proj = ( (*pb->getVerteces())[i].getX() * axisx + (*pb->getVerteces())[i].getY() * axisy );
            if(proj < minprojb){
                minprojb = proj;
            }
            if(proj > maxprojb){
                maxprojb = proj;
            }
        }

        float minproja = ( (*pa->getVerteces())[0].getX() * axisx + (*pa->getVerteces())[0].getY() * axisy );
        float maxproja = ( (*pa->getVerteces())[0].getX() * axisx + (*pa->getVerteces())[0].getY() * axisy );

        for(int i = 1; i < pa->getVerteces()->size();i++){
            proj = ( (*pa->getVerteces())[i].getX() * axisx + (*pa->getVerteces())[i].getY() * axisy );
            if(proj < minproja){
                minproja = proj;
            }
            if(proj > maxproja){
                maxproja = proj;
            }
        }

        if(minprojb > maxproja || maxprojb < minproja){
            return false;
        }
    }

    return true;
}
