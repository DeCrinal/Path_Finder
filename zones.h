#ifndef ZONES_H
#define ZONES_H

#include <iostream>
#include <vector>
#include <array>

using std::vector;
using std::array;

typedef std::pair<int,int>Pair;


//Для создания зоны нового типа достаточно создать наследника Zone
class Zone{
private:
public:
    virtual void forbid(vector<vector<int>>&field)=0;
    virtual void resize(int perc)=0;
    virtual int getType()=0;
    virtual Pair getCenter()=0;
    virtual Pair getLeftTopVertex()=0;
    virtual Pair getRightBotVertex()=0;
    virtual int getWidth()=0;
    virtual int getHeight()=0;
    virtual ~Zone(){};
};

class CircleZone: public Zone{
private:
    Pair center;
    int rad;
public:
    CircleZone(Pair center={0,0},int rad = 0);
    virtual ~CircleZone();
    virtual int getWidth()override;
    virtual int getHeight()override;
    virtual void resize(int perc)override;
    virtual Pair getCenter()override;
    virtual Pair getLeftTopVertex()override;
    virtual Pair getRightBotVertex()override;
    virtual void forbid(vector<vector<int>>&field)override;
    virtual int getType()override;

};

class RectZone: public Zone{
private:
    int left, right, top, bottom;
public:
    RectZone(int left = 0, int top = 0, int right = 0, int bottom=0);
    virtual ~RectZone();
    virtual int getWidth()override;
    virtual int getHeight()override;
    virtual void resize(int perc)override;
    virtual Pair getCenter()override;
    virtual Pair getLeftTopVertex()override;
    virtual Pair getRightBotVertex()override;
    virtual void forbid(vector<vector<int>>&field)override;
    virtual int getType()override;
};
#endif // ZONES_H
