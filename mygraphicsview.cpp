#include "mygraphicsview.h"
#include <algorithm>
#include <QRect>
#include <QGraphicsTextItem>
#include <iostream>
MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{

}
MyGraphicsView::MyGraphicsView(QWidget *parent, const vector<Zone*>&data,
                        stack<Pair>&path, int perc) : QGraphicsView(parent)
{

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    scene = new QGraphicsScene();
    this->setScene(scene);
    this->setRenderHints(QPainter::Antialiasing |
                            QPainter::SmoothPixmapTransform);

    this->drawAxis(perc);
    this->drawZones(data,path,perc);
    this->drawPath(data,path,perc);
}
MyGraphicsView::~MyGraphicsView()
{
    delete scene;
}

void MyGraphicsView::drawAxis(int perc){
    QGraphicsTextItem *text;
    QPen grayPen(Qt::gray);

    scene->addLine(0,0,400,0,grayPen);
    scene->addLine(0,0,0,400,grayPen);
    scene->addLine(400,0,400,400, grayPen);
    scene->addLine(0,400,400,400, grayPen);
    scene->addLine(100,0,100,400, grayPen);
    scene->addLine(200,0,200,400, grayPen);
    scene->addLine(300,0,300,400, grayPen);
    scene->addLine(0,100,400,100, grayPen);
    scene->addLine(0,200,400,200, grayPen);
    scene->addLine(0,300,400,300, grayPen);

    for(int i = 0; i<5; i++){
        text = scene->addText(QString::number(100*perc*i));
        auto digitsAm = [](int n)->int{
            int res=1;
            while(n!=0){n/=10;}
            return res;
        };
        text->setPos(100*i-digitsAm(100*i)*15,-25);
        if(i==0) continue;
        text = scene ->addText(QString::number(100*perc*i));
        text->setPos(-25-digitsAm(100*i)*13, 100*i-15);
    }
}

void MyGraphicsView::drawPath(const vector<Zone*>&data,stack<Pair>&path,int perc){
    QPen blackPen(Qt::black);
    QBrush greenBrush(Qt::green);
    Pair prevPoint = path.top();
    Pair prevPointToPrint = prevPoint;
    Pair delta;
    path.pop();

    //Отрисовка точки изгиба пути
    auto temp = scene->addEllipse(QRectF(prevPoint.second-3.5,
                                        prevPoint.first-3.5,7,7),blackPen,greenBrush);

    //Точки изгиба должны отображаться поверх пути и краев зон
    temp->setZValue(2);
    for(int i = 0; !path.empty();i++){
        if(i>0){
            bool isAngle = delta.first != prevPoint.second-path.top().second
                    || delta.second != prevPoint.first-path.top().first
                    || path.size()==1;
            if(isAngle)
            {
                auto temp = scene->addEllipse(QRectF(path.top().second-3.5,
                                        path.top().first-3.5,7,7),blackPen,greenBrush);
                temp->setZValue(2);
            }
        }
        auto temp = scene->addLine(QLine(prevPoint.second, prevPoint.first,
                    path.top().second,path.top().first));
        temp->setZValue(1);
        delta = {prevPoint.second - path.top().second,prevPoint.first - path.top().first};
        prevPoint = path.top();
        path.pop();
    }
}
void MyGraphicsView::drawZones(const vector<Zone*>&data,stack<Pair>&path,int perc)
{
    QPen redPen(Qt::red);
    QBrush redBrush(Qt::red);
    for(int i = 0; i<data.size();i++)
    {
        switch(data[i]->getType())
        {
        case(1):
        {
            scene->addEllipse(QRectF(data[i]->getLeftTopVertex().first,
                        data[i]->getLeftTopVertex().second,data[i]->getWidth(),
                                data[i]->getHeight()),redPen,redBrush);
            break;
        }
        case(2):
        {
            scene->addRect(QRectF(data[i]->getLeftTopVertex().first,
                        data[i]->getLeftTopVertex().second,data[i]->getWidth(),
                                data[i]->getHeight()),redPen,redBrush);
            break;
        }
        default:break;
        }
    }
}
