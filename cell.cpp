#include "cell.h"
#include <QScrollBar>
#include <QTextEdit>
#include <QLabel>

//Ubicacion de la celda con enfoque
int Cell::indexC=0;
int Cell::indexR=0;

//Constructor
Cell::Cell(int ir,int ic,int num){
    this->indexRow=ir;
    this->indexCol=ic;
    this->setStylePencilOffCell();
    this->setRpta(num);
}

//Functions

void Cell::setStylePencilOffCell(){
    QFont styleCell = this->font();

    styleCell.setWeight(QFont::Thin);
    styleCell.setPointSize(40);


    this->setFont(styleCell);
    this->setFixedSize(65,65);
    this->setReadOnly(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar *sb=this->verticalScrollBar();
    sb->triggerAction(QAbstractSlider::SliderNoAction);
    sb->setDisabled(true);
    this->setOverwriteMode(false);
    this->setTextInteractionFlags(Qt::NoTextInteraction);
    this->viewport()->setCursor(Qt::ArrowCursor);



}

void Cell::setStylePencilOnCell()
{
    QFont styleCell = this->font();
    styleCell.setWeight(QFont::Bold);
    styleCell.setPointSize(11);
    this->setFont(styleCell);
    QString pen="";
    for(int i=0;i<9;i++){
        pen+=((pencil[i])?QString::number(i+1):"  ");
        if(i==2||i==5)  pen+="\n";
        else            pen+="   ";
    }
    this->setText(pen);
    //this->setAlignment(Qt::AlignCenter);
}

void Cell::setScopeStyleCell()
{
    QPalette paletteC = this->palette();
    paletteC.setColor(QPalette::Base,QColor::fromRgb(200, 200, 200));
    this->setPalette(paletteC);
}

void Cell::setSelectedStyleCell()
{
//    if(pencilModeOn())  setStylePencilOnCell();
//    else    setStylePencilOffCell();

    QPalette paletteC = this->palette();
    if(this->hasRpta()&&!this->isCorrect()){
        paletteC.setColor(QPalette::Base,QColor::fromRgb(237, 36, 36));
    }else{
        paletteC.setColor(QPalette::Base,QColor::fromRgb( 42, 67, 191));
    }
    paletteC.setColor(QPalette::Text,QColor::fromRgb(255,255,255));

    this->setPalette(paletteC);
//    this->setAlignment(Qt::AlignCenter);
//    this->update();
}

void Cell::setUnselectedStyleCell(){
//    if(pencilModeOn())  setStylePencilOnCell();
//    else    setStylePencilOffCell();

    QPalette paletteC = this->palette();
    //this->setStyleSheet("QTextEdit { background-color: rgb(255,255,255); }");
    paletteC.setColor(QPalette::Base,QColor::fromRgb(255, 255, 255));

    if(this->isStart()){
        paletteC.setColor(QPalette::Text,QColor::fromRgb(0,0,0));
    }else if(this->isCorrect()|| this->pencilModeOn()){
        paletteC.setColor(QPalette::Text,QColor::fromRgb(11, 107, 218));
    }else{
        paletteC.setColor(QPalette::Text,QColor::fromRgb( 237, 36, 36 ));
        qDebug()<<"llego aca"<<Qt::endl;
    }
    this->setPalette(paletteC);
//    this->setAlignment(Qt::AlignCenter);
//    this->update();
}


void Cell::setNumberCell(int num){
    this->rpta=num;
    if(this->rpta==-1){
        this->setText("");
    }else{
        this->setText(QString::number(num));
    }
    this->setStylePencilOffCell();
    this->setAlignment(Qt::AlignCenter);
}

void Cell::setPencilMode(bool mode)
{
    this->pencilMode=mode;
}

void Cell::addDeletePencilValue(int number)
{
    pencil[number-1]=!pencil[number-1];
    //this->setStylePencilOnCell();
    this->setStylePencilOnCell();
    this->setPencilMode(true);
}

void Cell::deleteAllPencilValues()
{
    for(int i=0;i<9;++i){
        pencil[i]=false;
    }
}

void Cell::setCorrect(int num){
    this->correct = num;
}

bool Cell::isCorrect()
{
    if(rpta==-1)    return true;
    if(correct == rpta) return true;
    return false;
}

void Cell::setStart(bool b)
{
    this->start = b;
}

void Cell::setRpta(int num)
{
    this->rpta=num;
    this->setPencilMode(false);
    setNumberCell(num);
}

int Cell::getRpta()
{
    return rpta;
}

bool Cell::hasRpta()
{
    if(this->rpta!=-1)
        return true;
    return false;
}

bool Cell::pencilModeOn()
{
    //this->setStylePencilOnCell();
    return this->pencilMode;
}

bool Cell::isStart()
{
    return start;
}

void Cell::eraseAllPencilValues(){
    for(int i=0;i<9;++i){
        pencil[i]=false;
    }
}

//Events

void Cell::focusInEvent(QFocusEvent *event)
{
    Cell::indexC = indexCol;
    Cell::indexR = indexRow;
    qDebug()<<"********************************************************************************************************************";
    emit signalSelected();
}

//bool Cell::eventFilter(QObject *o, QEvent *e)
//{
//    return true;
//    if(e->type()==QEvent::Wheel){
////        e->ignore();
//    }
//    if(e->type()==QEvent::KeyPress){
//        //qDebug()<<"ACA p"<<Qt::endl;
//        return true;
//    }
//    if(e->type()==QEvent::DragEnter){
//        e->ignore();
//    }

//}

void Cell::mouseMoveEvent(QMouseEvent *e)
{
    e->ignore();
}

//void Cell::changeEvent(QEvent *e)
//{
//    //e->ignore();
//}

