#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QRect>
#include <QGraphicsScene>
#include <vector>
#include <cmath>
#include <array>
#include <iostream>
#include "AStarSearch.h"
#include "zones.h"
#include <memory>

using std::cout;
using std::endl;
using std::cin;
using std::max;


//Инициализация готовыми запрещенными зонами, без пересчета perc
[[deprecated("For the tests only")]]
void initZonesAuto(vector<Zone*>&zones, int perc);

//Ручная инициализация запрещенных зон
void initZonesHand(vector<Zone*>&zones, int &percData, int&percGraphic,
                   int dataSize);
//Инициализация начальной и конечных точек
void initSrcDst(Pair &src, Pair&dst, int &percData, int &percGraphic, int dataSize);

//Печать пути
void printPath(stack<Pair>purePath, int percData, const Pair& dst );

//Обмен координат и сжатие - для работы алгоритма
void swapAndShift(Pair&src, Pair&dst, int percData);

//Метод для печати пути между двумя точками
void printPointToPoint(const Pair&pt1, const Pair&pt2, int percData);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Pair src, dst;
    vector<vector<int>>fieldVect;
    vector<Zone*>forbiddenZones;
    stack<Pair>path;
    const int fixedSize=401;

    fieldVect.resize(fixedSize);
    for(int i=  0; i<fixedSize; i++){
        fieldVect[i].assign(fixedSize,1);
    }
    int percData = 1;
    int percGraphic = 1;

    initSrcDst(src, dst, percData, percGraphic, fixedSize);
    //initZonesAuto(forbiddenZones, percData);
    initZonesHand(forbiddenZones, percData, percGraphic, fixedSize);

    for(int i = 0; i<forbiddenZones.size(); i++)
    {
        forbiddenZones[i]->resize(percData);
        forbiddenZones[i]->forbid(fieldVect);
    }
    swapAndShift(src,dst, percData);

    AStarSearch::aStarSearch(fieldVect,src,dst,path);
    printPath(path, percData, dst);

    MainWindow w(nullptr, forbiddenZones, path, percGraphic);
    w.setWindowTitle("Path Finder");

    w.show();
    a.exec();

    for(int i = 0; i<forbiddenZones.size(); i++){
       delete forbiddenZones[i];
    }

    return 0;
}
void initSrcDst(Pair &src, Pair&dst, int &percData, int &percGraphic, int dataSize)
{
    int maxValueData=dataSize-2;
    int maxValueGraphic=399;
    cin>>src.first>>src.second;
    cin>>dst.first>>dst.second;
    maxValueData = max(maxValueData, max(dst.first,
                    max(src.first, max(src.second, dst.second))));
    maxValueGraphic = max(maxValueGraphic, max(dst.first,
                    max(src.first, max(src.second, dst.second))));
    percData = max(percData, static_cast<int>(ceil(maxValueData/
                                               static_cast<double>(dataSize-1))));
    percGraphic = max(percGraphic, static_cast<int>(ceil(maxValueGraphic/400.0)));
}

void initZonesHand(vector<Zone*>&zones, int &percData, int&percGraphic,
                    int dataSize)
{
    // 0 - rectangle zone
    // 1 - circle zone
    // ex.: 0 1 1 300 300 	- прямоугольная зона с (1,1) до (300,300)
    // 		1 25 25 30		- круглая зона с центром в (25,25) рад. 30
    // 		-1 				- конец ввода

    int type;
    int in1, in2, in3, in4;
    int maxValueData=dataSize-2;
    int maxValueGraphic=399;
    do{
        cin>>type;
        switch(type){
        case(0):{
            cin>>in1>>in2>>in3>>in4;
            maxValueData = max(in1, max(in2, max(in3, max(in4, maxValueData))));
            maxValueGraphic = max(in1, max(in2, max(in3, max(in4,
                                                            maxValueGraphic))));
            zones.push_back(new RectZone(in1, in2, in3, in4));
            break;
        }
        case(1):{
            cin>>in1>>in2>>in3;
            maxValueData=max(in1+in3, max(in2+in3, maxValueData));
            maxValueGraphic=max(in1+in3, max(in2+in3, maxValueGraphic));
            zones.push_back(new CircleZone({in1, in2},in3));
            break;
        }
        default:;
        }
    }while(type!=-1);
    percData = max(percData, static_cast<int>(ceil(maxValueData/
                                                   static_cast<double>(dataSize-1))));
    percGraphic = max(percGraphic, static_cast<int>(ceil(maxValueGraphic/400.0)));
}

void initZonesAuto(vector<Zone*>&zones, int perc)
{
    zones.push_back(new RectZone(0, 10, 50, 100));
    zones.push_back(new RectZone(250,10,350,100));
    zones.push_back(new CircleZone({150, 300},25));
    zones.push_back(new RectZone(100, 100, 150, 150));
    zones.push_back(new CircleZone({350, 300},25));
    zones.push_back(new RectZone(200, 175, 250, 225));
    zones.push_back(new CircleZone({150, 150},25));
    zones.push_back(new CircleZone({250, 300},35));
    zones.push_back(new RectZone(100, 0, 200, 100));
    zones.push_back(new CircleZone({300, 30},20));
}

void printPointToPoint(const Pair&pt1, const Pair&pt2, int perc){
    cout<<"("<<pt1.second*perc<<","<<pt1.first*perc
       <<") -> (" <<pt2.second*perc<<","<<pt2.first*perc<<")"<<endl;
}

void printPath(stack<Pair>purePath, int perc, const Pair& dest)
{
    if(purePath.size()==0 || purePath.size()==1)
        return;
    Pair prevPrintedPoint = purePath.top();
    Pair prevPoint=prevPrintedPoint;
    Pair curPoint;
    Pair delta={0, 0};
    purePath.pop();
    cout<<endl<<"The path is:"<<endl;
    while(purePath.size()!=0)
    {
        curPoint = purePath.top();
        purePath.pop();
        bool isFirstPt = delta.first==0&&delta.second==0;
        if(isFirstPt)
        {
            delta.first = curPoint.first - prevPoint.first;
            delta.second = curPoint.second - prevPoint.second;
            prevPoint = curPoint;
            continue;
        }
        bool isAngle = delta.first != curPoint.first-prevPoint.first ||
                delta.second != curPoint.second - prevPoint.second;
        if(isAngle)
        {
            delta = {curPoint.first-prevPoint.first, curPoint.second-
                     prevPoint.second};
            printPointToPoint(prevPrintedPoint,prevPoint,perc);
            prevPrintedPoint = prevPoint;
        }
        prevPoint = curPoint;
    }
    printPointToPoint(prevPrintedPoint,prevPoint,perc);

}

void swapAndShift(Pair&src, Pair&dst, int perc)
{
    src.second/=perc;
    src.first/=perc;
    dst.first/=perc;
    dst.second/=perc;
    std::swap(src.second,src.first);
    std::swap(dst.second,dst.first);
}
