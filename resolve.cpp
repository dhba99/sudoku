#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QStyle>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <thread>
#include <QMessageBox>
#include "resolve.h"
#include "tablero.h"
#include "styles.h"


#define indexTmp tab[Cell::indexR][Cell::indexC]

Resolve::Resolve(QWidget* parent)
{

    //-----------------------------------------Layout Superior---------------------------------------------

    QHBoxLayout* superior = new QHBoxLayout();


    //-----------------------------------------Tablero---------------------------------------------
    //Tablero de Sudoku
    Tablero *tablero = new Tablero();
    this->tab = tablero->getArrayCell();


    //-----------------------------------------Botones del juego---------------------------------------------
    QFont font ;
    font.setPointSize(11);

    //Boton lapiz
    QPushButton *resolver=new QPushButton();
    resolver->setFont(font);
    resolver->setText("Resolver");
    QIcon *il = new QIcon(":/icon/resources/pencilIcon.png");
    resolver->setIcon(*il);

    resolver->setIconSize(*new QSize(50,50));

    //Boton borrar
    QPushButton *borrar=new QPushButton();
    borrar->setFont(font);
    borrar->setText("Borrar");
    QIcon *ib = new QIcon(":/icon/resources/deleteIcon.png");
    borrar->setIcon(*ib);
    borrar->setIconSize(*new QSize(50,50));

    //Boton deshacer
    QPushButton *deshacer=new QPushButton();
    deshacer->setFont(font);
    deshacer->setText("Deshacer");
    QIcon *id = new QIcon(":/icon/resources/undoIcon.png");
    deshacer->setIcon(*id);
    deshacer->setIconSize(*new QSize(50,50));



    QObject::connect(resolver,&QPushButton::clicked,this,&Resolve::resolveGame);
    QObject::connect(borrar,&QPushButton::clicked,this,&Resolve::borrar);
    QObject::connect(deshacer,&QPushButton::clicked,this,&Resolve::deshacer);

    //Poniendo botones en layout menu
    QHBoxLayout* menu = new QHBoxLayout();
    menu->addWidget(resolver);
    menu->addWidget(borrar);
    menu->addWidget(deshacer);


    //-----------------------------------------Uniendo Layouts---------------------------------------------
    //Layout principal
    QVBoxLayout *principal = new QVBoxLayout();



    //Añadiendo layouts
    principal->addLayout(superior);
    principal->addLayout(tablero);
    principal->addLayout(menu);
    this->setLayout(principal);


    for(auto& a1:tab){
        for(auto& a2:a1){
            a2->installEventFilter(this);
            QObject::connect(a2,&Cell::signalSelected,this,&Resolve::selectedEvent);
        }
    }

}

void Resolve::resolveGame()
{

    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(tab[i][j]->hasRpta()) tablero[i][j]=tab[i][j]->getRpta();
            else tablero[i][j]=0;
        }
    }
    auto solutions = main1();

    if(solutions>1){
        QMessageBox msgBox;
        msgBox.setInformativeText("El sudoku tiene multiples soluciones");
        msgBox.exec();
    }

}


//importante colocar la rpta a la celda
void Resolve::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() & Qt::ControlModifier && event->key()==Qt::Key_R){
        resolveGame();
        return;
    }

    //Si ninguna celda esta en foco
    if(!indexTmp->hasFocus())   return;

    //Shortcuts
    if(event->key() == Qt::Key_Backspace){
        deshacer();
        return;
    }
    if(event->key() == Qt::Key_Delete){
        borrar();
        return;
    }

    //Si la tecla presionada es una direccional
    if(event->key() >= 0x01000012 && event->key() <= 0x01000015){
        if(event->key()==Qt::Key_Up){
            --Cell::indexR;
        }else if(event->key()==Qt::Key_Down)
            ++Cell::indexR;
        else if(event->key()==Qt::Key_Left)
            --Cell::indexC;
        else if(event->key()==Qt::Key_Right)
            ++Cell::indexC;

        if(Cell::indexR<0)  Cell::indexR+=9;
        if(Cell::indexC<0)  Cell::indexC+=9;

        Cell::indexR%=9;
        Cell::indexC%=9;

        indexTmp->setFocus();
        selectedEvent();
        return;
    }

    //Solo se permiten colocar valores a celdas que no estan establecidas
    //y que la tecla presionada este entre el 1 y 9
    if(indexTmp->isStart())     return;
    if((event->text()==""))     return;
    if(!event->text().at(0).isDigit()  ||  event->text().at(0)=='0') return;

    //Ejecuta el movimiento
    makeMovement(Cell::indexR,Cell::indexC,event->text().toInt());
    movements.push_back(std::make_tuple(Cell::indexR,Cell::indexC,event->text().toInt()));
    selectedEvent();

}


bool Resolve::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::KeyPress){
        keyPressEvent(static_cast<QKeyEvent*> (event));
        return true;
    }
    return false;
}



void Resolve::selectedEvent()
{
    //Borra los estilos dejando el estilo base
    Tablero::eraseStyleCells(tab);

    if(!indexTmp->hasFocus()) return;

    //Configura el estilo del ambito de la seleccion
    Tablero::setScopeStyleCells(tab,Cell::indexR,Cell::indexC);

    //Si no hay respuesta solo seleccionar la casilla actual
    if(!indexTmp->hasRpta()){
        indexTmp->setSelectedStyleCell();
        return;
    }

    //Si no, selecciona todas las coincidencias
    Tablero::setSelectedStyleCells(tab,indexTmp->toPlainText());
}


void Resolve::makeMovement(int x, int y, int value)
{
    tab[x][y]->setCorrect(value);
    tab[x][y]->setStart(true);

}

void Resolve::deshacer()
{
    Tablero::eraseStyleCells(tab);
    if(movements.empty()) return;

    //Posicion fila
    int ir=std::get<0>(movements.back());
    //Posicion columna
    int ic=std::get<1>(movements.back());
    //Valor
    int vc=std::get<2>(movements.back());


    bool foundNum = false;

    for(auto i=movements.crbegin();i!=movements.crend();++i){
        if( std::get<0>(*i)==ir
            && std::get<1>(*i)==ic){
                    makeMovement(ir,ic,std::get<2>(*i));
                    tab[ir][ic]->setPencilMode(false);
                    foundNum=true;

                break;


        }

    }



    if(!foundNum){
        makeMovement(ir,ic,-1);
    }
    selectedEvent();

}

void Resolve::borrar(){
    makeMovement(Cell::indexR,Cell::indexC,-1);
    indexTmp->setFocus();

    //Añade a la pila de movimientos
    movements.push_back(std::make_tuple
                        (Cell::indexR,Cell::indexC,-1));

    selectedEvent();
}
