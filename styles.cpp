#include "styles.h"
#include <QFont>
#include <QStyle>

void Styles::setTitleStyle(QLabel* label){
    QFont font;
    font.setPointSize(25);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(font);
}

void Styles::setCountersGameStyle(QLabel *label)
{
    QFont font;
    font.setPointSize(12);
    // label->setAlignment(Qt::AlignCenter);
    label->setFont(font);
}

void Styles::setTimerStyle(QLabel *label)
{
    QFont styles;
    styles.setPointSize(25);
    #ifdef _WIN32
        styles.setFamily("Segoe UI");
        styles.setStyleHint(QFont::TypeWriter);
    #endif
    label->setFont(styles);
    label->setWordWrap(true);
}
