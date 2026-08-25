#include <vector>
#include "vertex.h"
using namespace std;

class Polygon {
    private:
        vector<Vertex> verteces;
    public:
        Polygon(vector<Vertex> verteces):verteces(verteces){};

        vector<Vertex>* getVerteces(){
            return &verteces;
        }
};
