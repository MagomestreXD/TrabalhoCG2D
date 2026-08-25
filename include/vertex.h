class Vertex {
    private:
        float x;
        float y;
    public:
        Vertex(float x,float y):x(x),y(y){};

        float getX(){
            return x;
        }

        float getY(){
            return y;
        }
};
