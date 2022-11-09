#pragma once

using namespace std;

class Point {
    public:
    Point(int xCoord_, int yCoord_);
    int getXCoord();
    int getYCoord();
    
    private:

    int xCoord;
    int yCoord;
};