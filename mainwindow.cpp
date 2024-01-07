#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //Widget principal
    this->setFocus();
    QIcon *iwp = new QIcon(":/icon/resources/windowIcon.rc");
    this->setWindowIcon(*iwp);
    this->setWindowTitle("Sudoku v1.00");
    ////////////////////////////////
    this->setFocusPolicy(Qt::StrongFocus);


    QPushButton* easy=new QPushButton();
    QPushButton* medium=new QPushButton();
    QPushButton* hard=new QPushButton();

    QObject::connect(easy,&QPushButton::clicked,this,&MainWindow::easyLevel);
    QObject::connect(medium,&QPushButton::clicked,this,&MainWindow::mediumLevel);
    QObject::connect(hard,&QPushButton::clicked,this,&MainWindow::hardLevel);

    QStyle* style;

    easy->setText("Facil");
    medium->setText("Intermedio");
    hard->setText("Dificil");

    easy->setFixedSize(250,70);
    medium->setFixedSize(250,70);
    hard->setFixedSize(250,70);


    QVBoxLayout* mainLayout= new QVBoxLayout();
    mainLayout->addWidget(easy);
    mainLayout->addWidget(medium);
    mainLayout->addWidget(hard);

    mainLayout->setAlignment(Qt::AlignCenter);
    QWidget* widget = new QWidget();
    widget->setLayout(mainLayout);


    this->setCentralWidget(widget);


    this->resize(617,732);
    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::easyLevel()
{
    game = new Game(nullptr,Game::Difficulty::EASY);
    setCentralWidget(game);
}

void MainWindow::mediumLevel()
{
    game = new Game(nullptr,Game::Difficulty::MEDIUM);
    setCentralWidget(game);
}

void MainWindow::hardLevel()
{
    game = new Game(nullptr,Game::Difficulty::HARD);
    setCentralWidget(game);
}

