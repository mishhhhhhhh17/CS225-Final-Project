#pragma once

#include <cmath>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

using std::pair;
using std::string;
using std::set;
using std::vector;

class Graph {
    public: 
    /**
     * Node struct to represent each incident on the graph
    */
    struct Node {
        int incidentID;
        int totalDead;
        int totalMigrants;
        pair<double, double> coordinates; 
    };

    /**
     * Default constructor
    */
    Graph() = default;

    /**
     * Parametrized constructor that takes in a .csv file where each column
     * represents incidentID, totDeadMissing, totalMigrants, xCoord, and yCoord
     * 
     * @param filename .csv file of incidents
    */
    Graph(string filename);

    vector<Node*> DijkstraSP(Graph G, Node* s);

    /**
     * Finding the distance between two coordinates in radians using the haversine formula
     * 
     * degrees to radians: degrees * pi / 180
     * 
     * φ = latitude
     * λ = longitude
     * R = Earth's radius = 6,371km
     * 
     * Haversine Formula:
     * a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
     * c = 2 ⋅ atan2( √a, √(1−a) )
     * distance = R ⋅ c
     * 
     * @cite https://www.movable-type.co.uk/scripts/latlong.html
    */
    double calculateDistance(Node* one, Node* two);

    private:
    vector<vector<string>> data_;
    vector<pair<Node*, pair<Node*, double>>> edgeList;
    set<Node*> vertices;
};