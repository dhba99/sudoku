#ifndef RESOLVE_H
#define RESOLVE_H

#include <QObject>
#include "cell.h"
#include "creador.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class Resolve; }
QT_END_NAMESPACE

class Resolve : public QWidget
{
    Q_OBJECT

public:

    Resolve(QWidget *parent);
    ~Resolve()=default;


    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void signalSelectedPress();
    void signalMovement();

public slots:
    void selectedEvent();
    void makeMovement(int x, int y, int value);
    void resolveGame();
    void deshacer();
    void borrar();


private:
    std::array<std::array<Cell*,9>,9> tab;
    std::vector<std::tuple<int,int,int>>  movements;
};

#endif // RESOLVE_H
