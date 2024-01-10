#include "tablero.h"
#include <QGridLayout>

Tablero::Tablero()
{
    this->setSpacing(5);
    for(int i=0;i<9;i+=3){
        for(int j=0;j<9;j+=3){
            QGridLayout *square = new QGridLayout();
            square->setSpacing(2);
            for(int i1=i;i1<i+3;i1++){
                for(int j1=j;j1<j+3;j1++){
                    tablero[i1][j1]=new Cell(i1,j1,-1);
                    square->addWidget(tablero[i1][j1],i1%3,j1%3);
                }
            }
            this->addLayout(square,i/3,j/3);
        }
    }
}

void Tablero::eraseStyleCells(CASILLAS tablero)
{
    for(auto& iItem:tablero){
        for(auto& jItem:iItem){
            jItem->setUnselectedStyleCell();
        }
    }
}

void Tablero::setSelectedStyleCells(CASILLAS tablero,QString number)
{
    for(auto& iItem:tablero){
        for(auto& jItem:iItem){
            if(jItem->toPlainText()==number)    jItem->setSelectedStyleCell();
        }
    }
}

void Tablero::setScopeStyleCells(CASILLAS tablero,int r,int c)
{
    for(int i=0;i<9;i++){
        tablero[r][i]->setScopeStyleCell();
        tablero[i][c]->setScopeStyleCell();
        tablero[r-r%3+i/3][c-c%3+i%3]->setScopeStyleCell();
    }
}

CASILLAS Tablero::getArrayCell(){
    return tablero;
}




