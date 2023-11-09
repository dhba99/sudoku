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
    MainWindow w;

    Game *game = new Game();
//    QIcon iwp("undoResource.png");
//    a.setWindowIcon();

    game->show();

    return a.exec();

}
