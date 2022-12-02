#include <catch2/catch_test_macros.hpp>
#include "graph.h"
#include "utilities.h"
#include <iostream>

TEST_CASE("Data parsing from CSV") {
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
