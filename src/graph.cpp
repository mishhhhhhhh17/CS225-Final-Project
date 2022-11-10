#include "graph.h"

using namespace std;

Graph::Graph(){

}
Graph::Graph(std::string filename){


}

vector<Node> Graph::DijkstraSP(Graph G, Node s){

}
int Graph::calculateDistance(Node one, Node two){
    int distance = 0;

    int xValueDiff = (one.coordinates.first - two.coordinates.first) * (one.coordinates.first - two.coordinates.first);
    int yValueDiff = (one.coordinates.second - two.coordinates.second) * (one.coordinates.second - two.coordinates.second);
    distance = sqrt(xValueDiff+yValueDiff);
    return distance;
}