#ifndef TABLERO_H
#define TABLERO_H

#include "cell.h"
#include <QGridLayout>

typedef std::array<std::array<Cell*,9>,9> CASILLAS;

class Tablero : public QGridLayout
{
    Q_OBJECT
public:
    Tablero();
    ~Tablero()=default;
    static void eraseStyleCells(CASILLAS tablero);
    static void setSelectedStyleCells(CASILLAS tablero,QString number);
    static void setScopeStyleCells(CASILLAS tablero,int r,int c);
    std::array<std::array<Cell*,9>,9> getArrayCell();
private:
    CASILLAS tablero;
};

#endif // TABLERO_H
