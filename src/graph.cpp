#include "graph.h"
#include "utilities.h"

using std::pair;
using std::string;
using std::set;
using std::vector;
using std::ifstream;

Graph::Graph() {
    // code here

}

Graph::Graph(string filename) {
    ifstream ifs{filename};
    for (string line; getline(ifs, line); line = "") {
        vector<string> vec = utilities::GetSubstrs(line, ',');
        data_.push_back(vec);
    }
}

vector<Graph::Node*> Graph::DijkstraSP(Graph G, Node* s) {
    // code here

}

double Graph::calculateDistance(Node* one, Node* two){
    double distance = 0;
    double xValueDiff = (one->coordinates.first - two->coordinates.first) * (one->coordinates.first - two->coordinates.first);
    double yValueDiff = (one->coordinates.second - two->coordinates.second) * (one->coordinates.second - two->coordinates.second);
    distance = sqrt(xValueDiff+yValueDiff);
    return distance;
}