/**
 * @file graph.h
 * 
 * Definition for the Graph class that represents incidents for reported missing migrants
 * 
 * @author Marcel Hoang
 * @author Adriana Shuaipaj
 * @author Anna Polski
 * @author Michelle Zhang
 * 
 * @date Fall 2022
*/
#pragma once

#include "../lib/cs225/PNG.h"
#include "../lib/cs225/HSLAPixel.h"

#include "Animation.h"

#include <cmath>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <map>
#include <functional>
#include <algorithm>
#include <iostream>

using std::pair;
using std::priority_queue;
using std::greater;
using std::string;
using std::set;
using std::vector;
using std::map;

using namespace cs225;

class Graph {
    public: 
    /**
     * Node struct to represent each incident on the graph
    */
    struct Node {
        string incidentID;
        int totalLoss;
        int totalMigrants;
        // latitude, longitude
        pair<double, double> coordinates;
    };

    /**
     * Default constructor
    */
    Graph() = default;

    /**
     * Destructor
    */
    ~Graph();

    /**
     * Copy constructor
    */
    Graph(const Graph& other);
    
    /**
     * Copy assignment operator
    */
    Graph& operator=(const Graph& other);

    /**
     * Parametrized constructor that takes in a .csv file where each column
     * represents incidentID, totDeadMissing, totalMigrants, xCoord, and yCoord
     * @todo populate edge list. nodes have edge if within certain distance of each other.
     * 
     * @param filename .csv file of incidents
    */
    Graph(string filename);
    
    /**
     * Returns shortest path from root of spanning tree to node
     * @param node Dijkstra's
    */
    vector<Node*> getShortestPath(Node* node);

    // helper functions for Prim's:
    // finds the node with minimum distance in a heap
    Node* findMin(map<Node*, double>& heap);
    void addEdge(Node* node1, Node* node2, double distance);

    //to help with operator=
    void _copy(const Graph& other);

    // destructor helper function
    void _destroy();

    vector<Node*> findByLoss(double target, double range);

    PNG plotPointsOnMap(const PNG map);

    PNG pathsOnMap(const PNG map);

    Graph prim();

    // for testing
    vector<vector<string>> getData();
    map<Node*, vector<pair<Node*, double>>> getEdgeList();
    set<Node*> getVertices();
    


    private:
    vector<vector<string>> data_;

    map<Node*, vector<pair<Node*, double>>> edgeList_;

    // set of all vertices in the Graph
    set<Node*> vertices_;

    /*
    Node with the lowest fraction of lost migrants.
    Initialized in the Graph constructor.
    */
    Node* lowest_risk_;

    /**
     * Finding the distance between two coordinates in radians using the haversine formula @endparblock
     * 
     * degrees to radians: degrees ⋅ pi / 180
     * 
     * φ = latitude
     * λ = longitude
     * R = Earth's radius = 6,371km
     * 
     * Haversine Formula:
     * a = sin²(Δφ/2) + cos(φ1) ⋅ cos(φ2) ⋅ sin²(Δλ/2)
     * c = 2 ⋅ atan2( √a, √(1−a) )
     * distance = R ⋅ c
     * 
     * @cite https://www.movable-type.co.uk/scripts/latlong.html
     * 
     * @param one first node
     * @param two second node
     * @return distance between one and two in kilometers
    */
    double calculateDistance(Node* one, Node* two);

    /**
     * helper function that converts (latitude, longitude) points to (x, y) points on a equirectangular projection map
     * 
     * @cite https://stackoverflow.com/questions/1369512/converting-longitude-latitude-to-x-y-on-a-map-with-calibration-points
     * 
     * @param image blank map
     * @param coor pair coordinates in latitude, longitude
     * 
     * @return pair of coordinates (x, y) coordinates in relation to the image of the map
    */
    pair<double, double> latLonToXY(const PNG* image, pair<double, double> coor);

    /*
    Returns the fraction of lost migrants out of the total number.
    */
    double calculateRisk(Node* node);
    
};