#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent *e)
{
    qDebug()<<"aca"<<Qt::endl;
    return true;
}
