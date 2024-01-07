#include <QtDebug>
#include "mainwindow.h"

#include <QApplication>
#include <QStyle>
#include <QPushButton>
#include <QLabel>

#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    MainWindow* w = new MainWindow(nullptr);

    w->show();
    // Game *game = new Game();
    // game->show();

    return a.exec();

}
