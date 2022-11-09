#include "point.h"

Point::Point(int xCoord_, int yCoord_){
    xCoord = xCoord_;
    yCoord = yCoord_;
}

int Point::getXCoord() {
    return xCoord;
}
int Point::getYCoord(){
    return yCoord;
}