#include <vector>

using namespace std;

class Texture{
    private:
        int height;
        int width;
        vector<uint32_t> pixels;
    public:
        Texture(int width,int height):width(width),height(height),pixels(width * height){};
        
        uint32_t getPixel(int x,int y){
            return pixels[(y * width) + x];
        }

        vector<uint32_t>& getData(){
            return pixels;
        }

        int getWidth(){
            return width;
        }

        int getHeight(){
            return height;
        }
};
