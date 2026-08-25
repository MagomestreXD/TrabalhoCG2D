#include "rasterizer.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

Rasterizer::Rasterizer(SDL_Renderer* renderer,int height,int width): renderer(renderer),height(height),width(width){}

void Rasterizer::setPixel(int x,int y, uint32_t color){
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8 ) & 0xFF;
    uint8_t a = color & 0xFF;

    SDL_SetRenderDrawColor(renderer,r,g,b,a);
    SDL_RenderPoint(renderer,x,y);
}

void Rasterizer::drawLine(float x0,float y0,float x1,float y1,uint32_t color){
    float temp;
    int dir;

    if(abs(x1 - x0) > abs(y1 - y0)){
        if(x0 > x1){
            temp = x0;
            x0 = x1;
            x1 = temp;

            temp = y0;
            y0 = y1;
            y1 = temp;
        }

        int dx = (int) x1 - (int) x0;
        int dy = (int)y1 - (int) y0;

        if(dy < 0){ dir = -1; }else{ dir = 1;}

        dy = dy * dir;

        int y = (int) y0;
        
        int D = 2*dy - dx;

        for(int x = (int) x0; x <= (int) x1;x++){
            
            setPixel(x,y,color);

            if(D >= 0){
                y += dir;
                D = D - 2*dx;
            }
            D = D + 2*dy;
        }

    }else{

         if(y0 > y1){
            temp = x0;
            x0 = x1;
            x1 = temp;

            temp = y0;
            y0 = y1;
            y1 = temp;
        }

        int dx = (int) x1 -(int) x0;
        int dy = (int) y1 -(int) y0;

        if(dx < 0){ dir = -1; }else{ dir = 1;}

        dx = dx * dir;

        int x = (int) x0;
        
        int D = 2*dx - dy;

        for(int y = (int) y0; y <= (int) y1;y++){
            
            setPixel(x,y,color);

            if(D >= 0){
                x += dir;
                D = D - 2*dy;
            }
            D = D + 2*dx;
        }       
    }
}

void Rasterizer::drawCircle(float x0,float y0,float radius,uint32_t color){
    int xc = (int) x0;
    int yc = (int) y0;
    int r = (int) radius;

    int x = r;
    int y = 0;

    float D = 0.25 - r;

    while(y < x){
        if(D > 0){
            x--;
            D += 2*y - 2*x + 3;
        }else{
            D += 2*y + 1;
        }

        setPixel(xc + x,yc + y,color);
        setPixel(xc - x,yc + y,color);
        setPixel(xc + x,yc - y,color);
        setPixel(xc - x,yc - y,color);

        setPixel(xc + y,yc + x,color);
        setPixel(xc - y,yc + x,color);
        setPixel(xc + y,yc - x,color);
        setPixel(xc - y,yc - x,color);

        y++;
    }
}

void Rasterizer::drawElipse(float x0,float y0,float rA,float rB,uint32_t color){
    int xc = (int) x0;
    int yc = (int) y0;
    int a = (int) rA;
    int b = (int) rB;

    int x = a;
    int y = 0;

    float D = b*b*(0.25 - a);

    while(x*b*b > y*a*a){
        if(D > 0){
           D += (1 - x)*2*b*b;    
           x--;           
        }

        D += (2*y+1)*a*a;

        setPixel(xc + x,yc + y,color);
        setPixel(xc - x,yc + y,color);
        setPixel(xc + x,yc - y,color);
        setPixel(xc - x,yc - y,color);

        y++;
    }

    D = x*x*b*b + (y*y + y + 0.25)*a*a - a*a*b*b;

    while(x >= 0){
        if(D < 0){
           D += (y + 1)*2*a*a;    
           y++;           
        }

        D += (-2*x+1)*b*b;

        setPixel(xc + x,yc + y,color);
        setPixel(xc - x,yc + y,color);
        setPixel(xc + x,yc - y,color);
        setPixel(xc - x,yc - y,color);

        x--;       
    }
}

void Rasterizer::intersection(Vertex a, Vertex b, int minx, int miny, vector<vector<int>> *outline){
    int x0 = ((int) a.getX()) - minx;
    int y0 = ((int) a.getY()) - miny;
    int x1 = ((int) b.getX()) - minx;
    int y1 = ((int) b.getY()) - miny;

    float temp;
    int dir;

    bool swap = false;

    if(y0 == y1){
        (*outline)[y0].push_back(x0);
        return;
    }

    if(abs(x1 - x0) > abs(y1 - y0)){
        if(x0 > x1){

            swap = true;
    
            temp = x0;
            x0 = x1;
            x1 = temp;

            temp = y0;
            y0 = y1;
            y1 = temp;
        }

        int dx = x1 - x0;
        int dy = y1 - y0;

        if(dy < 0){ dir = -1; }else{ dir = 1;}

        dy = dy * dir;

        int y = y0;
        
        int D = 2*dy - dx;

        int prevY = -1;

        for(int x = x0; x <= x1;x++){

            if(!swap){
                if((y != prevY && y >= y0 && y < y1) || (y != prevY && y > y1 && y <= y0)){
                    (*outline)[y].push_back(x);
                    prevY = y;
                }
            }else{
                if((y != prevY && y > y0 && y <= y1) || (y != prevY && y >= y1 && y < y0)){
                    (*outline)[y].push_back(x);
                    prevY = y;
                }
            }

            if(D >= 0){
                y += dir;
                D = D - 2*dx;
            }
            D = D + 2*dy;
        }

    }else{
         if(y0 > y1){

            swap = true;

            temp = x0;
            x0 = x1;
            x1 = temp;

            temp = y0;
            y0 = y1;
            y1 = temp;
        }

        int dx = x1 - x0;
        int dy = y1 - y0;

        if(dx < 0){ dir = -1; }else{ dir = 1;}

        dx = dx * dir;

        int x = x0;
        
        int D = 2*dx - dy;

        for(int y = y0; y <= y1;y++){

            if(!swap){
                if(y >= y0 && y < y1){
                    (*outline)[y].push_back(x);
                }
            }else{
                if(y > y0 && y <= y1){
                    (*outline)[y].push_back(x);
                }
            }

            if(D >= 0){
                x += dir;
                D = D - 2*dy;
            }
            D = D + 2*dx;
        }       
    }

}

void Rasterizer::scanLine(Polygon poly,uint32_t color){

    vector<Vertex> *verteces = poly.getVerteces();

    int maxy = (int) (*verteces)[0].getY();
    int miny = (int) (*verteces)[0].getY();
    int maxx = (int) (*verteces)[0].getX();
    int minx = (int) (*verteces)[0].getX();

    for(int i = 1; i < (*verteces).size(); i++){
        if(maxy < (int) (*verteces)[i].getY()){
            maxy = (int) (*verteces)[i].getY();
        }
        if(miny > (int) (*verteces)[i].getY()){
            miny = (int) (*verteces)[i].getY();
        }
        if(maxx < (int) (*verteces)[i].getX()){
            maxx = (int) (*verteces)[i].getX();
        }
        if(minx > (int) (*verteces)[i].getX()){
            minx = (int) (*verteces)[i].getX();
        }
    }
    
    int layers = maxy - miny + 1;

    vector<vector<int>> outline(layers);
    
    for(int i = 0; i + 1 < (*verteces).size(); i++){
        intersection((*verteces)[i],(*verteces)[i+1],minx,miny,&outline);
    }   
    intersection((*verteces)[(*verteces).size() - 1],(*verteces)[0],minx,miny,&outline);   


    for(int i = 0; i < (*verteces).size();i++){
        int prev = (i - 1 + (*verteces).size() ) % (*verteces).size();
        int next = (i + 1 ) % (*verteces).size();

        bool concave = true;

        if((*verteces)[prev].getY() == (*verteces)[i].getY() && (*verteces)[next].getY() == (*verteces)[i].getY()){
            concave = false;
        }else if((*verteces)[prev].getY() < (*verteces)[i].getY() && (*verteces)[next].getY() > (*verteces)[i].getY()){
            concave = false;
        }else if((*verteces)[prev].getY() > (*verteces)[i].getY() && (*verteces)[next].getY() < (*verteces)[i].getY()){
            concave = false;
        }

        if(concave){
            outline[(*verteces)[i].getY() - miny].push_back((*verteces)[i].getX() - minx);
            cout<< "Adicionado extra Y = " << (*verteces)[i].getY() << " : " << (*verteces)[i].getX() << endl;
        }
    }

    int temp;

    for(int y = 0; y < layers; y++){
        for(int i = 0; i < outline[y].size() - 1; i++){
            for(int j = i + 1; j < outline[y].size(); j++){
                if(outline[y][i] > outline[y][j]){
                    temp = outline[y][i];
                    outline[y][i] = outline[y][j];
                    outline[y][j] = temp;
                }
            }
        }
    }

    for(int y = 0; y < layers; y++){
        cout << "y = " << y + miny << ": ";

        for(int x : outline[y]){
            cout << x + minx << " ";
        }

        cout << endl;
    }

    cout << "Depois contagem" << endl;


    for(int y = 0; y < layers; y++){
        for(int i = 0; i + 1 < outline[y].size(); i = i + 2){
            for(int x = outline[y][i] ; x <= outline[y][i+1]; x++){
                setPixel(x + minx,y + miny,color);
            }
        }
    }   

}

