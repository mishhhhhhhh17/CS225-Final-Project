#include "graph.h"
#include "utilities.h"

using std::atan2;
using std::cos;
using std::pair;
using std::pow;
using std::sin;
using std::sqrt;
using std::string;
using std::stod;
using std::stoi;
using std::set;
using std::vector;
using std::ifstream;
using std::find;

Graph::~Graph() {
    _destroy();
}

Graph::Graph(const Graph& other) {
    // @todo
}
    
Graph& Graph::operator=(const Graph& other) {
    // @todo
    if (this != &other) {
        _destroy();
        _copy(other);
    }
    return *this;
}

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
        if (i == 1) lowest = toInsert;
        if (calculateRisk(toInsert) < calculateRisk(lowest)) lowest = toInsert;
        vertices_.insert(toInsert);
    }

    for (auto v : vertices_) { // populating edgeList
        vector<pair<Node*, double>> vect;
        for (auto e : vertices_) {
            if (calculateDistance(v, e) != 0 && calculateDistance(v, e) < 750) vect.push_back({e, calculateDistance(v, e)});
        }
        edgeList_[v] = vect;
    }
}

vector<Graph::Node*> Graph::getShortestPath(Node* node) {
    return short_paths_[node];
}

pair<unsigned int, unsigned int> Graph::latLonToXY(const PNG* image, pair<double, double> coor) {
    unsigned int x = image->width() * (180 + coor.first) / 360;
    unsigned int y = image->height() * (90 - coor.second) / 180;
    return {x, y};
}

double Graph::calculateRisk(Node* node) { return node->totalLoss / node->totalMigrants; }

/**
 * φ = latitude
 * λ = longitude
 * R = Earth's radius = 6,371km
 * 
 * Haversine Formula:
 * a = sin²(Δφ/2) + cos(φ1) ⋅ cos(φ2) ⋅ sin²(Δλ/2)
 * c = 2 ⋅ atan2( √a, √(1−a) )
 * distance = R ⋅ c
*/
double Graph::calculateDistance(Node* one, Node* two){
    double a = pow(((two->coordinates.first * M_PI / 180.0) - (one->coordinates.first * M_PI / 180.0))/2.0, 2.0)
                + cos(one->coordinates.first * M_PI / 180.0) * cos(two->coordinates.first * M_PI / 180.0)
                * pow(((two->coordinates.second * M_PI / 180.0) - (one->coordinates.second * M_PI) / 180.0)/2.0, 2.0);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return 6371 * c;
}

// helper function for Prim's, finds the node with minimum distance in a heap
Graph::Node* Graph::findMin(map<Node*, double>& heap) {
    pair<Node*, double> min_pair = *heap.begin(); // arbitrary
    for (auto map_pair : heap) {
        if (map_pair.second < min_pair.second) min_pair = map_pair;
    }
    return min_pair.first;
}

void Graph::addEdge(Node* node1, Node* node2, double distance) {
    edgeList_[node1].push_back({node2, distance});
    edgeList_[node2].push_back({node1, distance});
}

Graph Graph::prim() {
    map<Node*, double> pq; // fake heap with distance as second argument
    map<Node*, Node*> predecessor; // <node, parent>
    vector<Node*> visited; // keeping track of visited nodes to create spanning tree
    Graph spanning_tree = Graph();

    for (auto v : vertices_) {
        if (v == *vertices_.begin()) pq.insert({v, 0}); // distance is 0 for starting node
        else pq.insert({v, INT16_MAX}); // "infinity" distance for all other nodes
        predecessor.insert({v, NULL}); // predecessors initialized to null
    }

    while (!pq.empty()) {
        Node* current = findMin(pq); // node w/ min distance
        pq.erase(current); // removes the min node from the heap
        visited.push_back(current); // adds this node to the spanning tree

        for (auto edge : edgeList_[current]) { // looking through adjacent nodes of current
            if (!(find(visited.begin(), visited.end(), edge.first) != visited.end())) { // checking if in visited
                if (calculateDistance(current, edge.first) < pq[edge.first]) { // need to update the weight
                    auto it = pq.find(edge.first);
                    if (it != pq.end()) it->second = calculateDistance(current, edge.first); // updating weight in heap
                    auto itr = predecessor.find(edge.first);
                    if (itr != predecessor.end()) itr->second = current; // updating predecessor
                }
            }
        }
    }

    for (auto node : visited) { // populating spanning_tree
        if (predecessor[node] != NULL) spanning_tree.addEdge(node, predecessor[node], calculateDistance(node, predecessor[node]));
    }
    
    return spanning_tree;
}


void Graph::_copy(const Graph& other){
    if(!other.vertices_.empty()) {
        //begin populating the edge list and vertices.

    //map<Node*, vector<pair<Node*, double>>> edgeList_;
    
        for (auto iter = other.edgeList_.begin(); iter != other.edgeList_.end(); iter++) {
            edgeList_[iter->first] = iter->second;
        }

        //for vertices
        for (auto& iter : other.vertices_) {
            struct Node* toInsert = new Node();
            toInsert->incidentID = iter->incidentID;
            toInsert->totalLoss = iter->totalLoss;
            toInsert->totalMigrants = iter->totalMigrants;
            toInsert->coordinates = iter->coordinates;
            vertices_.insert(toInsert);
        }
    }
}


void Graph::_destroy(){
    for (auto v: vertices_) {
        delete v;
    }
}

// testing functions
vector<vector<string>> Graph::getData() {
    return data_;
}

map<Graph::Node*, vector<pair<Graph::Node*, double>>> Graph::getEdgeList() {
    return edgeList_;
}

set<Graph::Node*> Graph::getVertices() {
    return vertices_;
}

std::vector<Graph::Node*> Graph::findByLoss(double target, double range) {
    // to return
    std::vector<Node*> out;
    
    // Mark all the vertices as not visited
    std::map<Node*, bool> visited;
    for (auto node : vertices_) visited.emplace(node, false);

    // Create a queue for BFS
    std::queue<Node*> q;
    
    // // Mark the current node as visited and enqueue it
    Node* current = lowest_risk_;
    visited[current] = true;
    q.push(current);
    
    while(!q.empty()) {
        // Dequeue a vertex from queue
        current = q.front();

        // check if current's risk is within range of target
        if (abs(target - calculateRisk(current)) <= range) out.push_back(current);
        // pop
        q.pop();
        
        // Get all adjacent vertices of the dequeued
        // vertex current. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (auto adj : edgeList_[current]) {
            if (!visited[adj.first]) {
                visited[adj.first] = true;
                q.push(adj.first);
            }
        }
    }
    return out;
}

void Graph::plotPointsOnMap(const PNG blank_map, vector<pair<double, double>> points) {
    PNG* theMap = new PNG(blank_map);
    // create color of point
    cs225::HSLAPixel red(0, 1 , 0.5, 1);
    // iterate through points
    for(auto point : points) {
        // color a 5x5 area centered on the point
        for (size_t x = 0; x < 4; x++) {
            for (size_t y = 0; y < 4; y++) {
                // if the point is in bounds
                if (latLonToXY(theMap, point).first - 2 + x >= 0 && latLonToXY(theMap, point).first - 2 + x < theMap->width() && 
                    latLonToXY(theMap, point).second - 2 + y >= 0 && latLonToXY(theMap, point).second - 2 + y < theMap->height()) {
                        theMap->getPixel(latLonToXY(theMap, point).first - 2 + x, latLonToXY(theMap, point).second - 2 + y) = red;
                    }
            }
        }
    }
    theMap->writeToFile("../missing_migrants_map.png");
}