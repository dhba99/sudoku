#ifndef CELL_H
#define CELL_H

#include <QTextEdit>
#include <QKeyEvent>

class Cell : public QTextEdit
{
    Q_OBJECT

public:
    Cell(int ir,int ic,int num);
    ~Cell()=default;

    static int indexR;
    static int indexC;

    //Estilos de las celdas
    void setStylePencilOffCell();
    void setStylePencilOnCell();
    void setScopeStyleCell();
    void setSelectedStyleCell();
    void setUnselectedStyleCell();

    //Operaciones en las celdas
    void setNumberCell(int num);
    void setPencilMode(bool mode);
    void addDeletePencilValue(int number);
    void deleteAllPencilValues();
    bool isCorrect();
    void setCorrect(int num);
    bool isStart();
    void setStart(bool b);
    void setRpta(int num);
    int getRpta();
    bool hasRpta();
    bool pencilModeOn();

    void focusInEvent(QFocusEvent *event) override;
    //bool eventFilter(QObject *o, QEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;


    void eraseAllPencilValues();
signals:
    void signalSelected();
private:
    using QTextEdit::keyPressEvent;
    int correct;
    int rpta;
    bool start=false;
    bool pencilMode=false;
    std::array<bool,9> pencil{false};
    int indexRow;
    int indexCol;
    QFont resp;
};
#endif
