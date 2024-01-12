#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QObject>
#include <QVBoxLayout>
#include "game.h"
//#include "resolve.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void returnMenu();
    void easyLevel();
    void mediumLevel();
    void hardLevel();
    void resolveGame();
private:
    Game *game;
    //QWidget *widget;
    QWidget*  widget;
    QPointer<QVBoxLayout>  tlayout;
};
#endif // MAINWINDOW_H
