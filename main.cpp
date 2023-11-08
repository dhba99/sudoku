#include <QtDebug>
#include "mainwindow.h"

#include <QApplication>
#include <QFormLayout>
#include <QLayout>
#include <QLayout>
#include <QStyle>
#include <QPushButton>
#include <QTime>
#include <QLabel>
#include <QSplashScreen>

#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Game *game = new Game();
//    auto ss = game->palette();
//    ss.setColor(QPalette::Window,QColor::fromRgb(0, 0, 0));
//    game->setPalette(ss);

    game->show();

    //a.setStyleSheet("QTextEdit {border: 1px solid #7B7B7B; background-color: palette(base);}");

    //his->setStyleSheet("QTextEdit { background-color: rgb( 42, 67, 191); color:rgb(255,255,255); }");
    //paletteC.setColor(QPalette::Highlight, Qt::green);//#7B7B7B

    return a.exec();

}
