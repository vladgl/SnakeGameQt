#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(500, 500);
    v_PlayArea = new FieldGraphicsView();

    FixedRatioLayout* lout = new FixedRatioLayout();
    QWidget* wgt = new QWidget();

    lout->setMargin(0);

    lout->addWidget(v_PlayArea);
    wgt->setLayout(lout);

 //   this->setCentralWidget(wgt);
    this->setCentralWidget(v_PlayArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}




