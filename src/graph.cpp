#include "graph.h"

using namespace std;

Graph::Graph(){

}
Graph::Graph(std::string filename){

}

vector<Node> Graph::DijkstraSP(Graph G, Node s){

}
int Graph::calculateDistance(Point one, Point two){
    int distance = 0;

    int xValueDiff = (one.getXCoord() - two.getXCoord()) * (one.getXCoord() - two.getXCoord());
    int yValueDiff = (one.getYCoord() - two.getYCoord()) * (one.getYCoord() - two.getYCoord());
    distance = sqrt(xValueDiff+yValueDiff);
    return distance;
}