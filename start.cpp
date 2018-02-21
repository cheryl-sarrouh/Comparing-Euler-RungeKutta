#include "start.h"
#include "ui_start.h"
#include"mainwindow.h"
#include<iostream>
using namespace std;


Start::Start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_clicked()
{
  MainWindow * m= new MainWindow(ui->delta->value()); //pour pouvoir changer le pas
  m->show();
  //m->makePlot();
}
