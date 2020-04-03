#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    v_PlayArea = new FieldGraphicsView();

    QVBoxLayout* lout = new QVBoxLayout();
    QWidget* wgt = new QWidget();

    lout->setMargin(0);

    lout->addWidget(v_PlayArea);
    wgt->setLayout(lout);

    this->setCentralWidget(wgt);

    v_PlayArea->resize(QSize(128, 128));
}

MainWindow::~MainWindow()
{
    delete ui;
}




