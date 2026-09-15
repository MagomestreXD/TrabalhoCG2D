
class Vertex {
    private:
        float x;
        float y;
        float z = 1;
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

    public:
        Vertex(float x,float y, uint32_t color):x(x),y(y),r(color >> 24),g((color >> 16) & 0xFF),b((color >> 8) & 0xFF),a(color & 0xFF){};

        Vertex(float x,float y, uint8_t r, uint8_t g , uint8_t b, uint8_t a):x(x),y(y),r(r),g(g),b(b),a(a){};

        Vertex(float x,float y):x(x),y(y),r(0),g(0),b(0),a(0xFF){};

        Vertex():x(0),y(0),r(0),g(0),b(0),a(0){};

        float getX(){
            return x;
        }

        float getY(){
            return y;
        }

        float getZ(){
            return z;
        }

        uint8_t getR(){
            return r;
        }

        uint8_t getG(){
            return g;
        }

        uint8_t getB(){
            return b;
        }

        uint8_t getA(){
            return a;
        }

        uint32_t getColor(){
            uint32_t color = r << 24 | g << 16 | b << 8 | a;

            return color;
        }

        void add(Vertex a){
            x += a.getX();
            y += a.getY();
            return;
        }
        
        Vertex addCopy(Vertex a){
            Vertex copy = *this;
            copy.add(a);
            return copy;
        }

        void multMatrix(float matrix [3][3]){
            float prevx = x;
            float prevy = y;
            float prevz = z;

            x = prevx * matrix[0][0] + prevy * matrix[0][1] + prevz * matrix[0][2];
            y = prevx * matrix[1][0] + prevy * matrix[1][1] + prevz * matrix[1][2];
            z = prevx * matrix[2][0] + prevy * matrix[2][1] + prevz * matrix[2][2];

            return;
        }

        void multMatrix(double matrix [3][3]){
            double prevx = x;
            double prevy = y;
            double prevz = z;

            x = prevx * matrix[0][0] + prevy * matrix[0][1] + prevz * matrix[0][2];
            y = prevx * matrix[1][0] + prevy * matrix[1][1] + prevz * matrix[1][2];
            z = prevx * matrix[2][0] + prevy * matrix[2][1] + prevz * matrix[2][2];

            return;
        }

};
