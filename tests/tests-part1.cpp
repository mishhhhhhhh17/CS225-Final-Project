#include <catch2/catch_test_macros.hpp>
#include "graph.h"
#include "utilities.h"
#include <iostream>

using std::cout;
using std::endl;

TEST_CASE("Data parsing from CSV") {
    SECTION("cleaning dataset") {
        datasetCleaning("./data/MissingMigrants-Global-2022.csv");
    }

    Graph g("../data/missing_migrants_2022.csv");
    vector<vector<string>> data = g.getData();

    SECTION("size of data") {
        REQUIRE(data.size() == 835); // testing # rows
        REQUIRE(data.at(0).size() == 5); // testing # cols
    }
    
    SECTION("parsing labels") {
        REQUIRE(data.at(0).at(0) == "incidentID");
        REQUIRE(data.at(0).at(1) == "totDeadMissing");
        REQUIRE(data.at(0).at(2) == "totalMigrants");
        REQUIRE(data.at(0).at(3) == "xCoord");
        REQUIRE(data.at(0).at(4) == "yCoord");
    }

    SECTION("random spot testing") {
        REQUIRE(data.at(692).at(4) == "-111.060104");
        REQUIRE(data.at(692).at(1) == "1");
        REQUIRE(data.at(692).at(1) != "1.0");
        REQUIRE(data.at(34).at(2) == "1.0");
        REQUIRE(data.at(34).at(0) == "2022.MMP00035");
        REQUIRE(data.at(829).at(2) == "0.0");
        REQUIRE(data.at(829).at(3) == "37.35629868");
    }

    // 2022.MMP694,1,1.0,31.67987304,-111.060104 -> row 693
    // 2022.MMP00035,1,1.0,32.5488045,-117.0228877 -> row 35
    // 2022.MMP817,8,0.0,37.35629868,25.260743 -> row 830
}

TEST_CASE("Graph members") {
    Graph g("../data/missing_migrants_2022.csv");
    set<Graph::Node*> verticies = g.getVertices();
    SECTION("verticies") {
        REQUIRE(verticies.size() == 834);
    }
}

TEST_CASE("prim's algorithm") {
    Graph graph("../data/small_test_case.csv");

    // for printing edge list
    /* auto edgelist = graph.getEdgeList();
    for (auto pair : edgelist) {
        cout << "\n" << pair.first->incidentID << ":" << endl;
        for (auto edges : pair.second) {
            cout << edges.first->incidentID << ", " << edges.second << endl;
        }
    }
    */
    Graph span = graph.prim();
    auto edgelist = span.getEdgeList();
    vector<string> c_edges{"g", "f", "d"};
    vector<string> b_edges{"d", "a"};
    vector<string> a_edges{"b", "e"};
    vector<string> e_edges{"a"};
    vector<string> d_edges{"c", "b"};
    vector<string> f_edges{"c"};
    for (auto pair : edgelist) {
        if (pair.first->incidentID == "c") {
            REQUIRE(pair.second.size() == 3);
            vector<string> actual_c_edges;
            for (auto edges : pair.second) {
                actual_c_edges.push_back(edges.first->incidentID);
            }
            REQUIRE(c_edges == actual_c_edges);
        }
        else if (pair.first->incidentID == "b") {
            REQUIRE(pair.second.size() == 2);
            vector<string> actual_b_edges;
            for (auto edges : pair.second) {
                actual_b_edges.push_back(edges.first->incidentID);
            }
            REQUIRE(b_edges == actual_b_edges);
        }
        else if (pair.first->incidentID == "a") {
            REQUIRE(pair.second.size() == 2);
            vector<string> actual_a_edges;
            for (auto edges : pair.second) {
                actual_a_edges.push_back(edges.first->incidentID);
            }
            REQUIRE(a_edges == actual_a_edges);
        }
        else if (pair.first->incidentID == "e") {
            REQUIRE(pair.second.size() == 1);
            vector<string> actual_e_edges;
            for (auto edges : pair.second) {
                actual_e_edges.push_back(edges.first->incidentID);
            }
            REQUIRE(e_edges == actual_e_edges);
        }
        else if (pair.first->incidentID == "d") {
            REQUIRE(pair.second.size() == 2);
            vector<string> actual_d_edges;
            for (auto edges : pair.second) {
                actual_d_edges.push_back(edges.first->incidentID);
            }
            REQUIRE(d_edges == actual_d_edges);
        }
        else if (pair.first->incidentID == "f") {
            REQUIRE(pair.second.size() == 1);
            vector<string> actual_f_edges;
            for (auto edges : pair.second) {
                actual_f_edges.push_back(edges.first->incidentID);
            }
            REQUIRE(f_edges == actual_f_edges);
        }
    }
}
