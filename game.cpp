#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QStyle>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <thread>
#include <QMessageBox>
#include "game.h"
#include "tablero.h"
#include "styles.h"
#include "creador.cpp"

#define indexTmp tab[Cell::indexR][Cell::indexC]

Game::Game(QWidget* parent, Game::Difficulty inDifficulty):difficulty{inDifficulty}
{

    //-----------------------------------------Layout Superior---------------------------------------------

    QHBoxLayout* superior = new QHBoxLayout();

    
    //Time
    a = new QTime();
    a->setHMS(0,0,0);
    tiempo = new QLabel();
    Styles::setTimerStyle(tiempo);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Game::updateTime);
    timer->start(1000);


    lDifficulty = new QLabel();
    //Difficulty
    switch(difficulty){
        case Difficulty::EASY: lDifficulty->setText("Facil"); break;
        case Difficulty::MEDIUM: lDifficulty->setText("Intermedio"); break;
        case Difficulty::HARD: lDifficulty->setText("Dificil"); break;
        default: break;
    }

    QFont styles=lDifficulty->font();
    styles.setPointSize(18);
    lDifficulty->setFont(styles);


    QPixmap correct(":/icon/resources/checkIcon.png"),error(":/icon/resources/errorIcon.png"),empty(":/icon/resources/interrogationIcon.png");
    QPushButton* pauseGame = new QPushButton();
    QLabel *correctData = new QLabel();
    QLabel *errorData = new QLabel();
    QLabel * emptyData= new QLabel();

    correctCnt = new QLabel();
    errorCnt = new QLabel();
    emptyCnt= new QLabel();

    Styles::setCountersGameStyle(correctCnt);
    Styles::setCountersGameStyle(errorCnt);
    Styles::setCountersGameStyle(emptyCnt);

    pauseGame->setIcon(*(new QIcon(":/icon/resources/pauseIcon.png")));
    correctData->setPixmap(correct);
    errorData->setPixmap(error);
    emptyData->setPixmap(empty);

    correctData->resize(32,32),errorData->resize(32,32),emptyData->resize(15,15);

    superior->addWidget(pauseGame,2,Qt::AlignLeft);
    superior->addWidget(correctData,2,Qt::AlignLeft);
    superior->addWidget(correctCnt,2,Qt::AlignLeft);
    superior->addWidget(errorData,2,Qt::AlignLeft);
    superior->addWidget(errorCnt,17,Qt::AlignLeft);
    // superior->addWidget(emptyData,2,Qt::AlignLeft);
    // superior->addWidget(emptyCnt,16,Qt::AlignLeft);
    superior->addWidget(lDifficulty,34,Qt::AlignCenter);
    superior->addWidget(tiempo,33,Qt::AlignRight);

    QObject::connect(pauseGame,&QPushButton::clicked,this,&Game::pauseMenuEvent);


    //-----------------------------------------Tablero---------------------------------------------
    //Tablero de Sudoku
    Tablero *tablero = new Tablero();
    this->tab = tablero->getArrayCell();


    //-----------------------------------------Botones del juego---------------------------------------------
    QFont font ;
    font.setPointSize(11);

    //Boton lapiz
    QPushButton *lapiz=new QPushButton();
    lapiz->setFont(font);
    lapiz->setText("Lapiz");
    QIcon *il = new QIcon(":/icon/resources/pencilIcon.png");
    lapiz->setIcon(*il);

    lapiz->setIconSize(*new QSize(50,50));

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



    QObject::connect(lapiz,&QPushButton::clicked,this,&Game::lapiz);
    QObject::connect(borrar,&QPushButton::clicked,this,&Game::borrar);
    QObject::connect(deshacer,&QPushButton::clicked,this,&Game::deshacer);

    QObject::connect(this,&Game::signalMovement,this,&Game::movementEvent);

    //Poniendo botones en layout menu
    QHBoxLayout* menu = new QHBoxLayout();
    menu->addWidget(lapiz);
    menu->addWidget(borrar);
    menu->addWidget(deshacer);


    //-----------------------------------------Uniendo Layouts---------------------------------------------
    //Layout principal
    QVBoxLayout *principal = new QVBoxLayout();



    //Añadiendo layouts
   // principal->addWidget(tiempo);
    principal->addLayout(superior);
    principal->addLayout(tablero);
    principal->addLayout(menu);
    this->setLayout(principal);

    generateGame(difficulty);

    for(auto& a1:tab){
        for(auto& a2:a1){
            a2->installEventFilter(this);
            QObject::connect(a2,&Cell::signalSelected,this,&Game::selectedEvent);
            QObject::connect(this,&Game::signalSelectedPress,this,&Game::selectedEvent);
        }
    }


    emit signalMovement();
}


void Game::updateTime(){
    // std::this_thread::sleep_for
    *this->a = this->a->addMSecs(1000);
    this->tiempo->setText(this->a->toString());
}

//importante colocar la rpta a la celda
void Game::keyPressEvent(QKeyEvent *event)
{
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
    if(event->modifiers() & Qt::ControlModifier && event->key()==Qt::Key_L){
        lapiz();
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
    makeMovement(Cell::indexR,Cell::indexC,event->text().toInt(),this->lapizOn);
    movements.push_back(std::make_tuple(Cell::indexR,Cell::indexC,event->text().toInt(),this->lapizOn));
    selectedEvent();

}


bool Game::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::KeyPress){
        keyPressEvent(static_cast<QKeyEvent*> (event));
        return true;
    }
    return false;
}



void Game::selectedEvent()
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

void Game::movementEvent()
{
    corrects=0,errors=0,emptys=0;
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(tab[i][j]->getRpta()==-1) ++emptys;
            else{
                if(tab[i][j]->isCorrect()) ++corrects;
                else ++errors;
            }

        }
    }

    correctCnt->setText(QString::number(this->corrects));
    errorCnt->setText(QString::number(this->errors));
    emptyCnt->setText(QString::number(this->emptys));

    if(emptys==0 && errors==0){
        selectedEvent();
        QMessageBox msgBox;
        QPixmap qpx(30,30);
        qpx.load(":/icon/resources/winnerIcon.png");
        QIcon s(":/icon/resources/windowIcon.rc");
        msgBox.setWindowIcon(s);
        msgBox.setIconPixmap(qpx);
        msgBox.setText("Has ganado");

        int ret = msgBox.exec();

        if(ret==QMessageBox::Ok){
            emit exitGameSignal();
        }

    }

}

void Game::pauseMenuEvent()
{
    this->timer->stop();

    QMessageBox msgBox;
    QIcon s(":/icon/resources/windowIcon.rc");
    msgBox.setWindowIcon(s);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Que desea hacer?");

    QAbstractButton *retornar = msgBox.addButton(tr("Retornar"),QMessageBox::YesRole);
    QAbstractButton *salir = msgBox.addButton(tr("Salir"),QMessageBox::YesRole);


    //QObject::connect(&(msgBox.button(QMessageBox::Ok)),&QPushButton::clicked,this,&Game::exitGameEvent);

    int ret = msgBox.exec();

    if(msgBox.clickedButton()==salir){
        emit exitGameSignal();
    }else{
        this->timer->start(1000);

    }



}

void Game::exitGameEvent()
{

}

void Game::makeMovement(int x, int y, int value,bool lapizOn)
{
    if(lapizOn){
        if(tab[x][y]->hasRpta()) return;
        tab[x][y]->addDeletePencilValue(value);
    }else{
        tab[x][y]->setRpta(value);
        tab[x][y]->eraseAllPencilValues();
    }
    emit signalMovement();
}

void Game::lapiz()
{
    this->lapizOn = !this->lapizOn;
    if(indexTmp!=nullptr)   indexTmp->setFocus();
}



void Game::generateGame(Difficulty difficulty){

    int diff=0;
    if(difficulty==Difficulty::EASY) diff=1;
    else if(difficulty==Difficulty::MEDIUM) diff=2;
    else if(difficulty==Difficulty::HARD) diff=3;
    main11(diff);

    //Generate all
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            tab[i][j]->setCorrect(def[i][j].first);
            if((def[i][j].second)!=0){
                tab[i][j]->setNumberCell(int(def[i][j].first));

                tab[i][j]->setStart(true);
            }
            std::cout<<def[i][j].first<<std::endl;
        }
    }


}

void Game::deshacer()
{
    Tablero::eraseStyleCells(tab);
    if(movements.empty()) return;

    //Posicion fila
    int ir=std::get<0>(movements.back());
    //Posicion columna
    int ic=std::get<1>(movements.back());
    //Valor
    int vc=std::get<2>(movements.back());
    //Es lapiz
    bool l = std::get<3>(movements.back());
    movements.pop_back();

    if(l){
        tab[ir][ic]->addDeletePencilValue(vc);
        return;
    }

    bool foundPen = false;
    bool foundNum = false;

    for(auto i=movements.crbegin();i!=movements.crend();++i){
        if( std::get<0>(*i)==ir
         && std::get<1>(*i)==ic){

            if(std::get<3>(*i)){
               makeMovement(ir,ic,-1,false);
                foundPen=true;
                tab[ir][ic]->addDeletePencilValue(std::get<2>(*i));
                tab[ir][ic]->setPencilMode(true);
            }else{

                if(!foundPen){
                    makeMovement(ir,ic,std::get<2>(*i),false);
                    tab[ir][ic]->setPencilMode(false);
                    foundNum=true;
                }
                break;

            }
        }

    }



    if(!foundNum && !foundPen){
        makeMovement(ir,ic,-1,false);
    }
    selectedEvent();

}

void Game::borrar(){

    if(indexTmp->isStart())     return;
    makeMovement(Cell::indexR,Cell::indexC,-1,false);
    indexTmp->setFocus();
    indexTmp->deleteAllPencilValues();

    //Añade a la pila de movimientos
    movements.push_back(std::make_tuple
                        (Cell::indexR,Cell::indexC,-1,false));

    selectedEvent();
}
