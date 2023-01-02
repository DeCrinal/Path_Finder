#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <vector>
#include <stack>
#include <QString>
#include "zones.h"

using std::vector;
using std::stack;

typedef std::pair<int,int> Pair;

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent = 0);
    explicit MyGraphicsView(QWidget *parent, const vector<Zone*>&data,
                            stack<Pair>&path, int perc);
    ~MyGraphicsView();


private:
    QGraphicsScene      *scene;

    //Метод отрисовки разметки и координат
    void drawAxis(int perc);

    //Метод отрисовки пути и точек
    void drawPath(const vector<Zone*>&data,stack<Pair>&path,int perc);

    //Метод отрисовки запрещенных зон
    void drawZones(const vector<Zone*>&data,stack<Pair>&path,int perc);
};

#endif // MYGRAPHICVIEW\_H
