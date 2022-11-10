#include "graph.h"

using std::pair;
using std::string;
using std::set;
using std::vector;

Graph::Graph() {
    // code here

}

Graph::Graph(std::string filename) {
    // code here

}

vector<Graph::Node> Graph::DijkstraSP(Graph G, Node s) {
    // code here

}

int Graph::calculateDistance(Node one, Node two){
    int distance = 0;
    int xValueDiff = (one.coordinates.first - two.coordinates.first) * (one.coordinates.first - two.coordinates.first);
    int yValueDiff = (one.coordinates.second - two.coordinates.second) * (one.coordinates.second - two.coordinates.second);
    distance = sqrt(xValueDiff+yValueDiff);
    return distance;
}