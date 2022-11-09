 #pragma once

 #include "point.h"  

 using namespace std;
   
   
class Node {
    public:
        Node(int incidentID_, int totalDead_, int totalMigrants_, Point point_);
        
    private:
        int incidentID;
        int totalDead;
        int totalMigrants;
        Point point;
};