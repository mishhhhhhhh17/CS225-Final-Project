#pragma once

#include <cmath>
#include <set>
#include <string>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::set;
using std::vector;

class Graph {
    public: 
    struct Node {
        int incidentID;
        int totalDead;
        int totalMigrants;
        pair<double, double> coordinates; 
    };

    Graph();
    Graph(string filename);
    vector<Node*> DijkstraSP(Graph G, Node* s);
    double calculateDistance(Node* one, Node* two);

    private:
    vector<vector<string>> data_;
    vector<pair<Node*, pair<Node*, double>>> edgeList;
    set<Node*> vertices;
};