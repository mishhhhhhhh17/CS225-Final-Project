#include "graph.h"
#include "utilities.h"

using std::pair;
using std::string;
using std::stod;
using std::stoi;
using std::set;
using std::vector;
using std::ifstream;

Graph::Graph(string filename) {
    ifstream ifs{filename};
    for (string line; getline(ifs, line); line = "") {
        vector<string> vec = utilities::GetSubstrs(line, ',');
        data_.push_back(vec);
    }

    Node* lowest;
    for(unsigned int i = 1; i < data_.size(); i++) {
        struct Node* toInsert = new Node();
        toInsert->incidentID = data_[i][0];
        toInsert->totalLoss = stoi(data_[i][1]);
        toInsert->totalMigrants = stoi(data_[i][2]);
        pair<double, double> coor;
        coor.first = stod(data_[i][3]);
        coor.second = stod(data_[i][4]);
        toInsert->coordinates = coor;
        if (i == 1) lowest == toInsert;
        if (calculateRisk(toInsert) < calculateRisk(lowest)) lowest = toInsert;
        vertices_.insert(toInsert);
    }

    for (auto v : vertices_) { // populating edgeList
        vector<pair<Node*, double>> vect;
        for (auto e : vertices_) {
            if (calculateDistance(v, e) != 0) {
                vect.push_back({e, calculateDistance(v, e)});
            }
        }
        edgeList_[v] = vect;
    }
}

vector<Graph::Node*> Graph::getShortestPath(Node* node) {
    return short_paths_[node];
}

double Graph::calculateRisk(Node* node) { return node->totalLoss / node->totalMigrants; }

double Graph::calculateDistance(Node* one, Node* two){
    double distance = 0;
    double xValueDiff = (one->coordinates.first - two->coordinates.first) * (one->coordinates.first - two->coordinates.first);
    double yValueDiff = (one->coordinates.second - two->coordinates.second) * (one->coordinates.second - two->coordinates.second);
    distance = sqrt(xValueDiff+yValueDiff);
    return distance;
}

void Graph::dijkstra(Node* node) {
    priority_queue<pair<double, Node*>> pq;
 
    map<Node*, double> dist;
 
     pq.push({0, node});
     dist[node] = 0;

    while (!pq.empty()) {
        
        Node* u = pq.top().second;
        pq.pop();
 
        std::vector<pair<Node*, double>>::iterator i;
        for (i = edgeList_[u].begin(); i != edgeList_[u].end(); ++i) {
            // Get vertex label and weight of current
            // adjacent of u.
            Node* v = (*i).first;
            double weight = (*i).second;
 
            // If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight) {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
                
                // add vertex to path from source to final node
                short_paths_[v].push_back(v);
            }
         }
    }
}