#pragma once
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Graph {
    public: 
    Graph();
    Graph(std::string filename);
    vector<Node> DijkstraSP(Graph G, Node s);
    int calculateDistance(Node one, Node two);


    private:
    vector<string> data_;
    vector<pair<Node,pair<Node,double>> edgeList;
    set<Node> vertices;


    struct Node {
        int incidentID;
        int totalDead;
        int totalMigrants;
        pair<double, double> coordinates; 
    }




};