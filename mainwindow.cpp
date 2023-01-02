#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Инициализируем виджет с графикой */
    myPicture   = new MyGraphicsView();
    /* и добавляем его на слой */
    ui->graphicsLayout->addWidget(myPicture);
}
MainWindow::MainWindow(QWidget *parent,const std::vector<Zone*>&data,
                       std::stack<Pair>&Path, int perc):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myPicture   = new MyGraphicsView(nullptr,data,Path, perc);
    ui->graphicsLayout->addWidget(myPicture);
}
MainWindow::~MainWindow()
{
    delete myPicture;
    delete ui;
}
