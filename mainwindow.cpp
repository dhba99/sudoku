#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "styles.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{

    //Widget principal
    this->setFocus();
    QIcon *iwp = new QIcon(":/icon/resources/windowIcon.rc");
    this->setWindowIcon(*iwp);
    this->setWindowTitle("Sudoku v1.00");
    this->setFocusPolicy(Qt::StrongFocus);
    viewMenu();

}


void MainWindow::easyLevel()
{
    game = new Game(nullptr,Game::Difficulty::EASY);
    QObject::connect(game,&Game::exitGameSignal,this,&MainWindow::viewMenu);
    setCentralWidget(game);
}

void MainWindow::mediumLevel()
{
    game = new Game(nullptr,Game::Difficulty::MEDIUM);
    QObject::connect(game,&Game::exitGameSignal,this,&MainWindow::viewMenu);
    setCentralWidget(game);
}

void MainWindow::hardLevel()
{
    game = new Game(nullptr,Game::Difficulty::HARD);
    QObject::connect(game,&Game::exitGameSignal,this,&MainWindow::viewMenu);
    setCentralWidget(game);
}

void MainWindow::resolveGame(){

}

void MainWindow::viewMenu(){
    QLabel* titleLabel = new QLabel("Sudoku v1.00");
    Styles::setTitleStyle(titleLabel);
    QPushButton* easyButton = new QPushButton();
    QPushButton* mediumButton = new QPushButton();
    QPushButton* hardButton = new QPushButton();
    QPushButton* resolveButton = new QPushButton();

    QObject::connect(easyButton,&QPushButton::clicked,this,&MainWindow::easyLevel);
    QObject::connect(mediumButton,&QPushButton::clicked,this,&MainWindow::mediumLevel);
    QObject::connect(hardButton,&QPushButton::clicked,this,&MainWindow::hardLevel);
    QObject::connect(resolveButton,&QPushButton::clicked,this,&MainWindow::resolveGame);

    easyButton->setText("Facil");
    mediumButton->setText("Intermedio");
    hardButton->setText("Dificil");
    resolveButton->setText("Resolver mi juego");

    easyButton->setFixedSize(250,70);
    mediumButton->setFixedSize(250,70);
    hardButton->setFixedSize(250,70);
    resolveButton->setFixedSize(250,70);


    QVBoxLayout* mainLayout= new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(easyButton);
    mainLayout->addWidget(mediumButton);
    mainLayout->addWidget(hardButton);
    //mainLayout->addWidget(resolveButton);

    mainLayout->setAlignment(Qt::AlignCenter);
    widget= new QWidget();
    widget->setLayout(mainLayout);

    //actual=widget;

    this->setCentralWidget(widget);
    //QObject::connect(game,&Game::exitGameSignal,this,&MainWindow::viewMenu);

    this->resize(617,732);

}

MainWindow::~MainWindow()
{
    //delete ui;
}
