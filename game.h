#ifndef GAME_H
#define GAME_H

#include "cell.h"
#include <QLabel>
#include <QMainWindow>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui{
    class Game;
}
QT_END_NAMESPACE

class Game : public QWidget
{
    Q_OBJECT

public:

    Game(QWidget *parent=nullptr);
    ~Game()=default;

    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void signalSelectedPress();

public slots:
    void updateTime();
    void selectedEvent();
    void makeMovement(int x, int y, int value);
    void lapiz();
    void deshacer();
    void borrar();
    void generateGame();

private:
    std::array<std::array<Cell*,9>,9> tab;
    Ui::Game *ui;
    bool lapizOn=false;

    QLabel *tiempo;
    QTimer *timer;
    QTime* a;
    std::vector<std::tuple<int,int,int,bool>>  movements;
};

#endif // GAME_H
