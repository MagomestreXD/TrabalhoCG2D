
class Texture{
    private:
        int height;
        int width;
        uint32_t* pixels;
    public:
        Texture(int height, int width,uint32_t* pixels):height(height),width(width),pixels(pixels){};
        
        uint32_t getPixel(int x,int y){
            return pixels[(y * width) + x];
        }

        uint32_t* getData(){
            return pixels;
        }

        int getWidth(){
            return width;
        }

        int getHeight(){
            return height;
        }
};
