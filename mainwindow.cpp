#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<iostream>

#include <string>
#include <fstream>
#include <sstream>


#include<cmath>
using namespace std;

double g(9.8);
double k;
double m(80);
//mes constantes
double exp(double x);

double f(double t,double v){
    return (g-((k/m)*v));  //Pour avoir des valeurs de vitesse positives
}

double Euler(double(*f)(double,double),double t0,double v0,double h){
    v0=v0+h*(f(t0,v0));
    return v0;
}

double RungeKutta(double(*f)(double,double), double t0,double v0, double h){
    double k1=f(t0,v0);
    double k2=f(t0+h/2,v0+((h/2)*k1));
    double k3=f(t0+h,v0+(h*k2));
    v0=v0+((h/6)*(k1+4*k2+k3));
    return v0;
}


MainWindow::MainWindow(double d, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->d=d;

    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot(){
    // add two new graphs and set their look:
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setPen(QPen(Qt::red)); // Analytique

        ui->customPlot->addGraph();
        ui->customPlot->graph(1)->setPen(QPen(Qt::blue)); // Euler
        ui->customPlot->addGraph();
        ui->customPlot->graph(2)->setPen(QPen(Qt::green)); // Runge kutta
        // generate some points of data (y0 for first, y1 for second graph):
        QVector<double> x(3000), y0(3000), y1(3000),y2(3000);
        double v0=0;
        double t0=0;

         y0[0]=y1[0]=y2[0]=v0;
        for (int i=0; i<2500; ++i)
        {
            if (t0<=30){    //Avant le deployement du parachute
                k=11.2; //vitesse terminal =70m/s; dv/dt=g-(k/m)v=0 ; k=mg/v ; k=80*9.8/70 = 11.2
                x[i] = t0;
                y0[i] = (-(g*m/k)*(exp(-(x[i])*k/m)))+(g*m/k);//analytique
                y1[i+1] = Euler(f,t0,y1[i],0.02);//Euler
                y2[i+1]=RungeKutta(f,t0,y1[i],0.02);//RungeKutta

                cout<<"Analytique: "<<y0[i]<<" Euler:  "<<y1[i]<<" Runge Kutta:  "<<y2[i] <<endl;}

                else if (t0>30){ //Apres le deployement du parachute
                    k=130.67; //vitesse d'atterrissage = 6m/s ;  k=mg/v= 80*9.8/6= 130.67
                    x[i] = t0;
                    y0[i] = (-(g*m/k)*(exp(-(x[i])*k/m)))+(g*m/k);//analytique
                    y1[i+1] = Euler(f,t0,y1[i],0.02);//Euler
                    y2[i+1]=RungeKutta(f,t0,y1[i],0.02);//RungeKutta
                    cout<<"Analytique:"<<y0[i]<<" Euler:"<<y1[i]<<" Runge Kutta:"<<y2[i] <<endl;

                }


          t0=t0+(this->d);
        }
        // configure right and top axis to show ticks but no labels:
        // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
        ui->customPlot->xAxis2->setVisible(true);
        ui->customPlot->xAxis2->setTickLabels(false);
        ui->customPlot->yAxis2->setVisible(true);
        ui->customPlot->yAxis2->setTickLabels(false);
        // make left and bottom axes always transfer their ranges to right and top axes:
        connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
        // pass data points to graphs:
        ui->customPlot->graph(0)->setData(x, y0); //associer les graphes au fonctions
        ui->customPlot->graph(1)->setData(x, y1);
        ui->customPlot->graph(2)->setData(x, y2);
        // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
        ui->customPlot->graph(0)->rescaleAxes();
        // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
        ui->customPlot->graph(1)->rescaleAxes(true);
        ui->customPlot->graph(2)->rescaleAxes(true);
        // Note: we could have also just called ui->customPlot->rescaleAxes(); instead
        // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
        ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}
