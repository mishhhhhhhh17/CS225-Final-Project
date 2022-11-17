#pragma once

#include <cmath>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <map>

using std::pair;
using std::string;
using std::set;
using std::vector;
using std::map;

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
    double calculateDistance(Node* one, Node* two);

    private:
    vector<vector<string>> data_;
    map<Node*, vector<pair<Node*, double>>> edgeList;
    set<Node*> vertices;
};