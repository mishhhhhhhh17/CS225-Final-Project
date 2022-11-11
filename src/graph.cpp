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

    for(unsigned int i = 1; i < data_.size(); i++) {
        Node toInsert;
        toInsert.incidentID = data_[i][0];
        toInsert.totalDead = data_[i][1];
        toInsert.totalMigrants = data_[i][2];
        pair<double, double> coor;
        coor.first = data_[i][3];
        coor.second = data_[i][4];
        toInsert.coordinates = coor;
        vertices.insert(toInsert);
    }
}

vector<Graph::Node*> Graph::DijkstraSP(Graph G, Node* s) {
    // code here
    vector<Node*> v;
    return v;
}

double Graph::calculateDistance(Node* one, Node* two){
    double distance = 0;
    double xValueDiff = (one->coordinates.first - two->coordinates.first) * (one->coordinates.first - two->coordinates.first);
    double yValueDiff = (one->coordinates.second - two->coordinates.second) * (one->coordinates.second - two->coordinates.second);
    distance = sqrt(xValueDiff+yValueDiff);
    return distance;
}