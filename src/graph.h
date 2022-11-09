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
    int calculateDistance(Point one, Point two);


    private:
    vector<string> data_;




};