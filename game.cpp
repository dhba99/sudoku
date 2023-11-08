#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QStyle>
#include <QTime>
#include <QTimer>
#include "game.h"
#include "tablero.h"
#include "creador.cpp"

#define indexTmp tab[Cell::indexR][Cell::indexC]

Game::Game(QWidget* parent)
{


    //Widget principal
    this->setFocus();
    QIcon *iwp = new QIcon("C://Users//Bryan//OneDrive//OneDriveAccs//Documentos//untitled//resources//8.rc");
    this->setWindowIcon(*iwp);
    this->setWindowTitle("Sudoku v1.00");
    ////////////////////////////////
    this->setFocusPolicy(Qt::StrongFocus);

    //-----------------------------------------Layout 1---------------------------------------------
    //Tiempo
    a = new QTime();
    a->setHMS(0,0,0);
    tiempo = new QLabel();
    QFont styles;
    styles.setWeight(QFont::Thin);
    styles.setPointSize(25);
    tiempo->setFont(styles);
    tiempo->setWordWrap(true);
    tiempo->setAlignment(Qt::AlignCenter);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Game::updateTime);
    timer->start(1000);


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
    QIcon *il = new QIcon("C://Users//Bryan//OneDrive//OneDriveAccs//Documentos//untitled//resources//10.png");
    lapiz->setIcon(*il);

    lapiz->setIconSize(*new QSize(50,50));

    //Boton borrar
    QPushButton *borrar=new QPushButton();
    borrar->setText("Borrar");
    QIcon *ib = new QIcon("C://Users//Bryan//OneDrive//OneDriveAccs//Documentos//untitled//resources//8.png");
    borrar->setIcon(*ib);
    borrar->setIconSize(*new QSize(50,50));

    //Boton deshacer
    QPushButton *deshacer=new QPushButton();
    deshacer->setText("Deshacer");
    QIcon *id = new QIcon("C://Users//Bryan//OneDrive//OneDriveAccs//Documentos//untitled//resources//9.png");
    deshacer->setIcon(*id);
    deshacer->setIconSize(*new QSize(50,50));



    QObject::connect(lapiz,&QPushButton::clicked,this,&Game::lapiz);
    QObject::connect(borrar,&QPushButton::clicked,this,&Game::borrar);
    QObject::connect(deshacer,&QPushButton::clicked,this,&Game::deshacer);

    //Poniendo botones en layout menu
    QHBoxLayout* menu = new QHBoxLayout();
    menu->addWidget(lapiz);
    menu->addWidget(borrar);
    menu->addWidget(deshacer);


    //-----------------------------------------Uniendo Layouts---------------------------------------------
    //Layout principal
    QVBoxLayout *principal = new QVBoxLayout();
    //Añadiendo layouts
    principal->addWidget(tiempo);
    principal->addLayout(tablero);
    principal->addLayout(menu);
    this->setLayout(principal);


    generateGame();

    for(auto& a1:tab){
        for(auto& a2:a1){
            a2->installEventFilter(this);
            QObject::connect(a2,&Cell::signalSelected,this,&Game::selectedEvent);
            QObject::connect(this,&Game::signalSelectedPress,this,&Game::selectedEvent);
        }
    }
}


void Game::updateTime(){
    *this->a = this->a->addMSecs(1000);
    this->tiempo->setText(this->a->toString());
}

//importante colocar la rpta a la celda
void Game::keyPressEvent(QKeyEvent *event)
{
    //Si ninguna celda esta en foco
    if(!indexTmp->hasFocus())   return;

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

    makeMovement(Cell::indexR,Cell::indexC,event->text().toInt());
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

void Game::makeMovement(int x, int y, int value)
{
    if(this->lapizOn){
        if(tab[x][y]->hasRpta()) return;
        tab[x][y]->addDeletePencilValue(value);
    }else{
        tab[x][y]->setRpta(value);
        tab[x][y]->eraseAllPencilValues();

    }
    movements.push_back(std::make_tuple(x,y,value,this->lapizOn));
//    for(auto i=movements.crbegin();i!=movements.crend();++i){
//        cout<<std::get<0>(*i)<<" "<<std::get<1>(*i)<<" "<<std::get<2>(*i)<<" "<<std::get<3>(*i)<<endl;

//    }
//    cout<<endl;
}

void Game::lapiz()
{
    this->lapizOn = !this->lapizOn;
    if(indexTmp!=nullptr)   indexTmp->setFocus();
}



void Game::generateGame(){
    main11();

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
                cout<<"aaa aaa a "<<std::get<2>(*i)<<endl;
                tab[ir][ic]->setRpta(-1);
                foundPen=true;
                tab[ir][ic]->addDeletePencilValue(std::get<2>(*i));
                tab[ir][ic]->setPencilMode(true);
            }else{

                if(!foundPen){
                    tab[ir][ic]->setRpta(std::get<2>(*i));
                    tab[ir][ic]->setPencilMode(false);
                    foundNum=true;
                }
                break;

            }
        }

    }



    if(!foundNum && !foundPen){
        tab[ir][ic]->setRpta(-1);
    }
    selectedEvent();

}

void Game::borrar(){

    if(indexTmp->isStart())     return;
    Tablero::eraseStyleCells(tab);
    indexTmp->setRpta(-1);
    indexTmp->deleteAllPencilValues();

    //Añade a la pila de movimientos
    movements.push_back(std::make_tuple
                        (Cell::indexR,Cell::indexC,-1,false));
}


