#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(double d,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void makePlot();
private:
    Ui::MainWindow *ui;
    double d;
};

#endif // MAINWINDOW_H
