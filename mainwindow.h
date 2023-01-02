#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mygraphicsview.h"
#include "zones.h"
#include <vector>
#include <stack>
typedef std::pair<int,int> Pair;
using std::vector;
using std::stack;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QWidget *parent, const vector<Zone*>&data,
                        stack<Pair>&path, int perc);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    MyGraphicsView  *myPicture;     // Наш кастомный виджет
};

#endif // MAINWINDOW\_H
