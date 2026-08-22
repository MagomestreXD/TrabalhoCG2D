#include "rasterizer.h"
#include <SDL3/SDL.h>
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



