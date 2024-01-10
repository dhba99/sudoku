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

    enum class Difficulty{EASY,MEDIUM,HARD};

    Game(QWidget *parent, Difficulty inDifficulty);
    ~Game()=default;


    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void signalSelectedPress();
    void signalMovement();

public slots:
    void updateTime();
    void selectedEvent();
    void movementEvent();
    void makeMovement(int x, int y, int value,bool lapizOn);
    void lapiz();
    void deshacer();
    void borrar();
    void generateGame(Difficulty difficulty);

private:
    std::array<std::array<Cell*,9>,9> tab;
    Ui::Game *ui;
    bool lapizOn=false;
    int corrects=0,errors=0,emptys=0;
    Difficulty difficulty;

    QLabel *lDifficulty;
    QLabel *tiempo;
    QLabel *correctCnt,*errorCnt,* emptyCnt;
    QTimer *timer;
    QTime* a;
    std::vector<std::tuple<int,int,int,bool>>  movements;
};

#endif // GAME_H
