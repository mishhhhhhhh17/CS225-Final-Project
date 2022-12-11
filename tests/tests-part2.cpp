// TESTS for BFS

#include <catch2/catch_test_macros.hpp>
#include "graph.h"
#include "utilities.h"
#include <iostream>
#include <set>

TEST_CASE("Constructor") {
    Graph graph = Graph("../data/bfs_test_data.csv");

    SECTION("create simple graph, checking the set") {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> one;
        one.push_back("incidentID"); one.push_back("totDeadMissing"); one.push_back("totalMigrants"); one.push_back("xCoord");
            one.push_back("yCoord");
        std::vector<std::string> two; 
        two.push_back("a"); two.push_back("10"); two.push_back("100"); two.push_back("0"); two.push_back("0");
        std::vector<std::string> three;
        three.push_back("b"); three.push_back("15"); three.push_back("100"); three.push_back("1"); three.push_back("0"); 
        std::vector<std::string> four; 
        four.push_back("c"); four.push_back("15"); four.push_back("100"); four.push_back("10"); four.push_back("10");
        std::vector<std::string> five; 
        five.push_back("d"); five.push_back("5"); five.push_back("100"); five.push_back("50"); five.push_back("50");
        std::vector<std::string> six; 
        six.push_back("e"); six.push_back("50"); six.push_back("100"); six.push_back("0"); six.push_back("1");
        std::vector<std::string> seven; 
        seven.push_back("f"); seven.push_back("1"); seven.push_back("100"); seven.push_back("100"); seven.push_back("100");
        std::vector<std::string> eight; 
        eight.push_back("g"); eight.push_back("90"); eight.push_back("100"); eight.push_back("10"); eight.push_back("0");
        std::vector<std::string> nine;
        nine.push_back("h"); nine.push_back("75"); nine.push_back("100"); nine.push_back("5"); nine.push_back("50");
        std::vector<std::string> ten; 
        ten.push_back("i"); ten.push_back("25"); ten.push_back("100"); ten.push_back("100"); ten.push_back("50");

        result.push_back(one);
        result.push_back(two);
        result.push_back(three);
        result.push_back(four);
        result.push_back(five);
        result.push_back(six);
        result.push_back(seven);
        result.push_back(eight);
        result.push_back(nine);
        result.push_back(ten);
        REQUIRE(result == graph.getData());

    }

    SECTION("checking nodes") {
        for (auto node : graph.getVertices()) {
            if (node->incidentID == "a") {
                REQUIRE(node->totalLoss == 10);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(0,0);
                REQUIRE(node->coordinates == coor);
            }
            if (node->incidentID == "b") {
                REQUIRE(node->totalLoss == 15);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(1,0);
                REQUIRE(node->coordinates == coor);
            }
            if (node->incidentID == "c") {
                REQUIRE(node->totalLoss == 15);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(10,10);
                REQUIRE(node->coordinates == coor);
            }
            if (node->incidentID == "d") {
                REQUIRE(node->totalLoss == 5);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(50,50);
                REQUIRE(node->coordinates == coor);
            }
            if (node->incidentID == "e") {
                REQUIRE(node->totalLoss == 50);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(0,1);
                REQUIRE(node->coordinates == coor);
            }
            if (node->incidentID == "f") {
                REQUIRE(node->totalLoss == 1);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(100,100);
                REQUIRE(node->coordinates == coor);
            }
            if (node->incidentID == "g") {
                REQUIRE(node->totalLoss == 90);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(10,0);
                REQUIRE(node->coordinates == coor);
            }
            if (node->incidentID == "h") {
                REQUIRE(node->totalLoss == 75);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(5,50);
                REQUIRE(node->coordinates == coor);
            }
            if (node->incidentID == "i") {
                REQUIRE(node->totalLoss == 25);
                REQUIRE(node->totalMigrants == 100);
                std::pair<double, double> coor(100,50);
                REQUIRE(node->coordinates == coor);
            }
        }
    }
}