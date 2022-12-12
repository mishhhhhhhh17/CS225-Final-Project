#include "graph.h"

int main(int argc, char** argv) {
    // argv[1] = filename of dataset (string)
    // argv[2] = filename of map (string)
    // argv[3] = target for findByLoss (double [0,1])
    // argv[4] = range for findByLoss (double [0,1])
    Graph g(argv[1]);
    Graph span = g.prim();
    PNG blank_map;
    blank_map.readFromFile(argv[2]);
    span.plotPointsOnMap(blank_map);
    vector<Graph::Node*> target_nodes = span.findByLoss(stod(argv[3]), stod(argv[4]));
    cout << "Nodes within target and range:" << endl;
    for (auto node : target_nodes) {
        cout << node->incidentID << endl;
    }
    return 0;
}