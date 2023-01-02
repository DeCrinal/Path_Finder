#ifndef HEADERS_H
#define HEADERS_H
#include<iostream>
#include<vector>
#include <QApplication>
using std::vector;
using std::array;
using std::pair;
using std::cout;
using std::endl;
typedef std::pair<int,int> Pair;
const int N = 501;
class Zone{
public:
    virtual void forbid(vector<vector<int>>&field){};
    virtual void forbid(array<array<int,N>,N>&field)=0;
    virtual void draw(){}
    virtual void resize(int perc)=0;
    virtual int figureType(){
        return 0;
    }
    virtual Pair getCenter(){
        return {0,0};
    }
    virtual Pair getLeftTopVertex(){
        return {0,0};
    }
    virtual Pair getRightBotVertex(){
        return {0,0};
    }
    Zone(){}
    virtual int getWidth(){
        return 0;
    }
    virtual int getHeight(){
        return 0;
    }
    virtual ~Zone(){};
};
class CircleZone: public Zone{
private:
    pair<int,int>center;
    int rad;
public:
    virtual int getWidth()override{
        return rad*2;
    }
    virtual int getHeight()override{
        return rad*2;
    }
    virtual void resize(int perc)override{
        center.first/=perc;
        center.second/=perc;
        rad/=perc;
    }
    virtual Pair getCenter()override{
        return center;
    }
    virtual Pair getLeftTopVertex()override{
        return {center.first-rad,center.second-rad};
    }
    virtual Pair getRightBotVertex()override{
        return {center.first+rad, center.second+rad};
    }
    virtual void forbid(vector<vector<int>>&field) override{
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
    virtual void forbid(array<array<int,N>,N>&field)override{
        int leftBorder, rightBorder,topBorder,bottomBorder;
        leftBorder = (center.first-rad>0)?center.first-rad:0;
        rightBorder = (center.first+rad<field[0].size())?center.first+rad:field[0].size()-1;
        topBorder = (center.second -rad>0)?center.second-rad:0;
        bottomBorder = (center.second+rad<field[0].size())?center.second+rad:field[0].size()-1;
        for(int i = topBorder; i<=bottomBorder;i++){
            for(int j = leftBorder; j<=rightBorder;j++){
                if(rad*rad>=(center.first-j)*(center.first-j)+(center.second-i)*(center.second-i)){
                    field[i][j]=0;
                }
            }
        }
    }
    virtual int figureType()override{
        return 1;
    }
    virtual void draw() override{

    }
    CircleZone(pair<int,int> center={0,0}, int rad = 0){
        this->center = center;
        this->rad = rad;
    }

    virtual ~CircleZone(){

    }
};
class RectZone: public Zone{
    int left, right, top, bottom;
public:
    virtual int getWidth()override{
        return right - left;
    }
    virtual int getHeight()override{
        return bottom-top;
    }
    virtual Pair getCenter()override{
        return {(left+right)/2,(top+bottom)/2};
    }
    virtual Pair getLeftTopVertex()override{
        return {left, top};
    }
    virtual void resize(int perc)override{
        left/=perc;
        right/=perc;
        top/=perc;
        bottom/=perc;
    }
    virtual Pair getRightBotVertex()override{
        return {right, bottom};
    }
    virtual void forbid(vector<vector<int>>&field) override{
        for(int i = top; i<=bottom; i++){
            for(int j = left; j<=right; j++){
                field[i][j] = 0;
            }
        }
    }
    virtual void forbid(array<array<int,N>,N>&field)override{
        for(int i = top; i<=bottom; i++){
            for(int j = left; j<=right; j++){
                field[i][j] = 0;
            }
        }
    }
    virtual int figureType() override{
        return 2;
    }
    virtual void draw()override{

    }
    RectZone(int left=0,int top=0, int right=0, int bottom=0){
        if(left<right && top<bottom){
            this->left = left;
            this->right = right;
            this->top = top;
            this->bottom=bottom;
        }
    }
    virtual ~RectZone(){

    }
};

#endif // HEADERS_H
