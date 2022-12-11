// TESTS for BFS

#include <catch2/catch_test_macros.hpp>
#include "graph.h"
#include "utilities.h"
#include <iostream>
#include <set>

TEST_CASE("Constructor") {
    Graph graph = Graph("/workspaces/cs225/CS225-Final-Project/data/mini_test_case.csv");

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

    SECTION("checking a Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "a");
        REQUIRE(graph.vertices_[1]->totalLoss = 10);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 0;
        coor.second = 0;
        REQUIRE(graph.vertices_[1]->coordinates = coor);
    }

    SECTION("checking b Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "b");
        REQUIRE(graph.vertices_[1]->totalLoss = 15);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 1;
        coor.second = 0;
        REQUIRE(graph.vertices_[1]->coordinates = coor);      
    }

    SECTION("checking c Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "c");
        REQUIRE(graph.vertices_[1]->totalLoss = 15);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 10;
        coor.second = 10;
        REQUIRE(graph.vertices_[1]->coordinates = coor);      
    }

    SECTION("checking d Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "d");
        REQUIRE(graph.vertices_[1]->totalLoss = 5);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 50;
        coor.second = 50;
        REQUIRE(graph.vertices_[1]->coordinates = coor);      
    }

    SECTION("checking e Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "e");
        REQUIRE(graph.vertices_[1]->totalLoss = 50);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 0;
        coor.second = 1;
        REQUIRE(graph.vertices_[1]->coordinates = coor);      
    }

    SECTION("checking f Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "f");
        REQUIRE(graph.vertices_[1]->totalLoss = 1);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 100;
        coor.second = 100;
        REQUIRE(graph.vertices_[1]->coordinates = coor);      
    }

    SECTION("checking g Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "g");
        REQUIRE(graph.vertices_[1]->totalLoss = 90);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 10;
        coor.second = 0;
        REQUIRE(graph.vertices_[1]->coordinates = coor);      
    }

    SECTION("checking h Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "h");
        REQUIRE(graph.vertices_[1]->totalLoss = 75);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 5;
        coor.second = 50;
        REQUIRE(graph.vertices_[1]->coordinates = coor);      
    }

    SECTION("checking i Node") {
        REQUIRE(graph.vertices_[1]->incidentID = "i");
        REQUIRE(graph.vertices_[1]->totalLoss = 25);
        REQUIRE(graph.vertices_[1]->totalMigrants = 100);
        std::pair<double, double> coor;
        coor.first = 100;
        coor.second = 50;
        REQUIRE(graph.vertices_[1]->coordinates = coor);      
    }

}