#include "zones.h"
CircleZone::CircleZone(Pair center,int rad){
    this->center = center;
    this->rad=rad;
}
CircleZone::~CircleZone(){

}

int CircleZone::getWidth(){
    return rad*2;
}
int CircleZone::getHeight(){
    return rad*2;
}
void CircleZone::resize(int perc){
    center.first/=perc;
    center.second/=perc;
    rad/=perc;
}
Pair CircleZone::getCenter(){
    return center;
}
Pair CircleZone::getLeftTopVertex(){
    return {center.first-rad,center.second-rad};
}
Pair CircleZone::getRightBotVertex(){
    return {center.first+rad, center.second+rad};
}
void CircleZone::forbid(vector<vector<int>>&field){
    int leftBorder, rightBorder,topBorder,bottomBorder;
    leftBorder = (center.first-rad>0)?center.first-rad:0;
    rightBorder = (center.first+rad<field[0].size())?center.first+rad:field[0].size()-1;
    topBorder = (center.second -rad>0)?center.second-rad:0;
    bottomBorder = (center.second+rad<field[0].size())?center.second+rad:field[0].size()-1;
    for(int i = topBorder; i<=bottomBorder;i++){
        for(int j = leftBorder; j<=rightBorder;j++){
            if(rad*rad>=(center.first-j)*(center.first-j)+(center.second-i)*(center.second-i))
                field[i][j]=0;
        }
    }
}
int CircleZone::getType(){
    return 1;
}
RectZone::RectZone(int left,int top, int right, int bottom){
    if(left<right && top<bottom){
        this->left = left;
        this->right = right;
        this->top = top;
        this->bottom=bottom;
    }
}
RectZone::~RectZone(){

}
int RectZone::getWidth(){
    return right - left;
}
int RectZone::getHeight(){
    return bottom-top;
}
Pair RectZone::getCenter(){
    return {(left+right)/2,(top+bottom)/2};
}
Pair RectZone::getLeftTopVertex(){
    return {left, top};
}
void RectZone::resize(int perc){
    left/=perc;
    right/=perc;
    top/=perc;
    bottom/=perc;
}
Pair RectZone::getRightBotVertex(){
    return {right, bottom};
}
void RectZone::forbid(vector<vector<int>>&field){
    for(int i = top; i<=bottom; i++){
        for(int j = left; j<=right; j++){
            field[i][j] = 0;
        }
    }
}
int RectZone::getType() {
    return 2;
}

