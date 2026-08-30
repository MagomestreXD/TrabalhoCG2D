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

        Polygon scale(float scale){
            vector<Vertex> copy = verteces;

            for(int i = 0; i < copy.size(); i++){
                copy[i].scale(scale);
            }

            return Polygon(copy);
        }       

        Polygon add(Vertex a){
            vector<Vertex> copy = verteces;

            for(int i = 0; i < copy.size(); i++){
                copy[i].add(a);
            }

            return Polygon(copy);
        }
};
