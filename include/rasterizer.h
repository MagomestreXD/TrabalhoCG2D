#include <SDL3/SDL.h>

class Rasterizer {
    private:
        SDL_Renderer* renderer;
        int height;
        int width;

    public: 
        Rasterizer(SDL_Renderer* renderer,int height,int width);

        void setPixel(int x,int y, uint32_t color);

        void drawLine(float x0,float y0,float x1,float y1,uint32_t color);

        void drawCircle(float x0,float y0,float radius,uint32_t color);

        void drawElipse(float x0,float y0,float rA,float rB,uint32_t color);
};
