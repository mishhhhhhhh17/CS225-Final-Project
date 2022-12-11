/**
 * @file graph.cpp
 * 
 * Implementation of the Graph class
 * 
 * @author Marcel Hoang
 * @author Adriana Shuaipaj
 * @author Anna Polski
 * @author Michelle Zhang
 * 
 * @date Fall 2022
*/
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

//graph destructor 
Graph::~Graph() {
    _destroy();
}

//graph copy constructor
Graph::Graph(const Graph& other) {
    _copy(other);
}

//graph operator= constructor 
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        _destroy();
        _copy(other);
    }
    return *this;
}

/*graph constructor

    adds all the data into our vector of vector of strings 
    constructed all of our nodes
    populated edgelist (keeping track of what nodes are connected to what other nodes)

*/
Graph::Graph(string filename) {
    ifstream ifs{filename};
    for (string line; getline(ifs, line); line = "") {
        vector<string> vec = utilities::GetSubstrs(line, ',', '"');
        data_.push_back(vec);
    }


    for(unsigned int i = 1; i < data_.size(); i++) {
        struct Node* toInsert = new Node();
        toInsert->incidentID = data_[i][0];
        toInsert->totalLoss = stoi(data_[i][1]);
        toInsert->totalMigrants = stoi(data_[i][2]);
        pair<double, double> coor;
        coor.first = stod(data_[i][3]);
        coor.second = stod(data_[i][4]);
        toInsert->coordinates = coor;
        // finding the lowest risk node
        if (i == 1) lowest_risk_ = toInsert;
        if (calculateRisk(toInsert) < calculateRisk(lowest_risk_)) lowest_risk_ = toInsert;
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


/*
turns latitude and longitude coordinates from the csv file into x and y points that correspond to the PNG image we are using
*/
pair<double, double> Graph::latLonToXY(const PNG* image, pair<double, double> coor) {
    double x = image->width() * (180 + coor.second) / 360;
    double y = image->height() * (90 - coor.first) / 180;
    return {x, y};
}

//calculates the percentage of how many people died in one incident
double Graph::calculateRisk(Node* node) { return double(node->totalLoss) / node->totalMigrants; }

/**
calculates distance between two nodes using the haversine formula

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
    double a = pow(sin(((two->coordinates.first * M_PI / 180.0) - (one->coordinates.first * M_PI / 180.0))/2.0), 2.0)
                + cos(one->coordinates.first * M_PI / 180.0) * cos(two->coordinates.first * M_PI / 180.0)
                * pow(sin(((two->coordinates.second * M_PI / 180.0) - (one->coordinates.second * M_PI) / 180.0)/2.0), 2.0);
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

/*
Prim's algorithm 

returns a minimum spanning tree

*/
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

/* 
copy constructor helper function
*/
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

/*
graph destructor helper function
*/
void Graph::_destroy(){
    for (auto v: vertices_) {
        delete v;
    }
}

// testing functions

/*
returns the data
*/
vector<vector<string>> Graph::getData() {
    return data_;
}

/*
returns the edgeList
*/
map<Graph::Node*, vector<pair<Graph::Node*, double>>> Graph::getEdgeList() {
    return edgeList_;
}

/*
return the vertices
*/
set<Graph::Node*> Graph::getVertices() {
    return vertices_;
}

/*
BFS function
*/
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
        if (std::abs(target - calculateRisk(current)) <= range) out.push_back(current);
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

/*
We plotted all the incidents onto a map

The bad incidents are colored red

The safer incidents are colored green
*/
void Graph::plotPointsOnMap(const PNG blank_map) {
    PNG* theMap = new PNG(blank_map);
    Animation animation;
    animation.addFrame(*theMap);
    int increment = 0;
    // iterate through points
    for(auto vertex : vertices_) {
        // create color of point based on calculated risk
        // green - low risk
        // red - high risk
        double hue = 120 - calculateRisk(vertex) * 120.0;
        cs225::HSLAPixel color(hue, 1 , 0.5, 1);
        // color a 5x5 area centered on the point
        for (size_t x = 0; x < 4; x++) {
            for (size_t y = 0; y < 4; y++) {
                // if the point is in bounds
                if (latLonToXY(theMap, vertex->coordinates).first - 2 + x >= 0 && latLonToXY(theMap, vertex->coordinates).first - 2 + x < theMap->width() && 
                    latLonToXY(theMap, vertex->coordinates).second - 2 + y >= 0 && latLonToXY(theMap, vertex->coordinates).second - 2 + y < theMap->height()) {
                        theMap->getPixel(latLonToXY(theMap, vertex->coordinates).first - 2 + x, latLonToXY(theMap, vertex->coordinates).second - 2 + y) = color;
                    }
            }
        }
        // add frame to animation
        if (increment % 75 == 0) {
            animation.addFrame(*theMap);
            increment++;
        }   else {
            increment++;
        }
    }
    animation.addFrame(*theMap);
    theMap->writeToFile("../missing_migrants_map.png");
    animation.write("../missing_migrants_map_plotting.gif");
    delete theMap;
}