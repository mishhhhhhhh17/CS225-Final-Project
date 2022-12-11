#include <catch2/catch_test_macros.hpp>
#include "graph.h"
#include "utilities.h"
#include <iostream>

using std::cout;
using std::endl;

TEST_CASE("Data parsing from CSV") {
    SECTION("cleaning dataset") {
        utilities::datasetCleaning("../data/MissingMigrants-Global-2022.csv");
    }

    Graph g("../data/cleaned_dataset.csv");
    vector<vector<string>> data = g.getData();

    SECTION("actual database parsing") {
        // testing rows and cols
        REQUIRE(data.size() == 835);
        REQUIRE(data.at(0).size() == 5);

        // testing labels
        REQUIRE(data.at(0).at(0) == "incidentID");
        REQUIRE(data.at(0).at(1) == "totDeadMissing");
        REQUIRE(data.at(0).at(2) == "totalMigrants");
        REQUIRE(data.at(0).at(3) == "xCoord");
        REQUIRE(data.at(0).at(4) == "yCoord");

        // spot testing data
        REQUIRE(data.at(692).at(4) == "-111.060104");
        REQUIRE(data.at(692).at(1) == "1");
        REQUIRE(data.at(692).at(1) != "1.0");
        REQUIRE(data.at(34).at(2) == "1");
        REQUIRE(data.at(34).at(0) == "2022.MMP00035");
        REQUIRE(data.at(829).at(2) == "116");
        REQUIRE(data.at(829).at(3) == "37.35629868");
    }

    // 2022.MMP694,1,1,31.67987304,-111.060104 -> row 693
    // 2022.MMP00035,1,1,32.5488045,-117.0228877 -> row 35
    // 2022.MMP817,8,116,37.35629868,25.260743 -> row 830

    SECTION("parsing bfs test csv") {
        Graph a("../data/bfs_test_data.csv");
        vector<vector<string>> actual_data = a.getData();
        vector<vector<string>> correct_data = {
            {"incidentID","totDeadMissing","totalMigrants","xCoord","yCoord"}, 
            {"a","10","100","0","0"}, 
            {"b","15","100","1","0"}, 
            {"c","15","100","10","10"},
            {"d","5","100","50","50"},
            {"e","50","100","0","1"},
            {"f","1","100","100","100"},
            {"g","90","100","10","0"},
            {"h","75","100","5","50"},
            {"i","25","100","100","50"}
        };
        REQUIRE(actual_data == correct_data);
    }
}

TEST_CASE("Graph members") {
    SECTION("bfs test case csv") {
        // testing vertices
        Graph a("../data/bfs_test_data.csv");
        set<Graph::Node*> v = a.getVertices();
        REQUIRE(v.size() == 9); 
        
    }

    SECTION("actual data csv") {
        Graph g("../data/cleaned_dataset.csv");
        set<Graph::Node*> verticies = g.getVertices();
        REQUIRE(verticies.size() == 834);
    }
    
}

TEST_CASE("prim's algorithm") {
    Graph graph("../data/small_test_case.csv");
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
            REQUIRE(pair.second.size() == c_edges.size());
            vector<string> actual_c_edges;
            for (auto edges : pair.second) {
                actual_c_edges.push_back(edges.first->incidentID);
            }
            bool has_g = std::find(actual_c_edges.begin(), actual_c_edges.end(), "g") != actual_c_edges.end();
            bool has_f = std::find(actual_c_edges.begin(), actual_c_edges.end(), "f") != actual_c_edges.end();
            bool has_d = std::find(actual_c_edges.begin(), actual_c_edges.end(), "d") != actual_c_edges.end();
            REQUIRE(has_g);
            REQUIRE(has_f);
            REQUIRE(has_d);
        }
        else if (pair.first->incidentID == "b") {
            REQUIRE(pair.second.size() == b_edges.size());
            vector<string> actual_b_edges;
            for (auto edges : pair.second) {
                actual_b_edges.push_back(edges.first->incidentID);
            }
            bool has_d = std::find(actual_b_edges.begin(), actual_b_edges.end(), "d") != actual_b_edges.end();
            bool has_a = std::find(actual_b_edges.begin(), actual_b_edges.end(), "a") != actual_b_edges.end();
            REQUIRE(has_d);
            REQUIRE(has_a);
        }
        else if (pair.first->incidentID == "a") {
            REQUIRE(pair.second.size() == a_edges.size());
            vector<string> actual_a_edges;
            for (auto edges : pair.second) {
                actual_a_edges.push_back(edges.first->incidentID);
            }
            bool has_b = std::find(actual_a_edges.begin(), actual_a_edges.end(), "b") != actual_a_edges.end();
            bool has_e = std::find(actual_a_edges.begin(), actual_a_edges.end(), "e") != actual_a_edges.end();
            REQUIRE(has_b);
            REQUIRE(has_e);
        }
        else if (pair.first->incidentID == "e") {
            REQUIRE(pair.second.size() == e_edges.size());
            vector<string> actual_e_edges;
            for (auto edges : pair.second) {
                actual_e_edges.push_back(edges.first->incidentID);
            }
            bool has_a = std::find(actual_e_edges.begin(), actual_e_edges.end(), "a") != actual_e_edges.end();
            REQUIRE(has_a);
        }
        else if (pair.first->incidentID == "d") {
            REQUIRE(pair.second.size() == d_edges.size());
            vector<string> actual_d_edges;
            for (auto edges : pair.second) {
                actual_d_edges.push_back(edges.first->incidentID);
            }
            bool has_c = std::find(actual_d_edges.begin(), actual_d_edges.end(), "c") != actual_d_edges.end();
            bool has_b = std::find(actual_d_edges.begin(), actual_d_edges.end(), "b") != actual_d_edges.end();
            REQUIRE(has_c);
            REQUIRE(has_b);
        }
        else if (pair.first->incidentID == "f") {
            REQUIRE(pair.second.size() == f_edges.size());
            vector<string> actual_f_edges;
            for (auto edges : pair.second) {
                actual_f_edges.push_back(edges.first->incidentID);
            }
            bool has_c = std::find(actual_f_edges.begin(), actual_f_edges.end(), "c") != actual_f_edges.end();
            REQUIRE(has_c);
        }
    }
}
