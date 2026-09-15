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

        Polygon multMatrix(float matrix[3][3]){
            vector<Vertex> copy = verteces;

            for(int i = 0; i < copy.size(); i++){
                copy[i].multMatrix(matrix);
            }
            
            return Polygon(copy);
        }

        Polygon multMatrix(double matrix[3][3]){
            vector<Vertex> copy = verteces;

            for(int i = 0; i < copy.size(); i++){
                copy[i].multMatrix(matrix);
            }
            
            return Polygon(copy);
        }
};
