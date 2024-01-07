#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //bool event(QEvent *e) override;
    Game *game;
public slots:
    void easyLevel();
    void mediumLevel();
    void hardLevel();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
