#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(0, 10);
    ui->plot->yAxis->setRange(0, 10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineOnPlot(double x1, double y1, double x2, double y2){

    QVector<double> X{x1,x2};
    QVector<double> Y{y1,y2};

    ui->plot->addGraph();
    ui->plot->graph(0)->setData(X,Y);
    ui->plot->replot();
}


/* SLOT de Qt */

void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
    x1 = arg1.toInt();
}

void MainWindow::on_spinBox_2_valueChanged(const QString &arg1)
{
    y1 = arg1.toInt();
}

void MainWindow::on_spinBox_3_valueChanged(const QString &arg1)
{
    x2 = arg1.toInt();
}

void MainWindow::on_spinBox_4_valueChanged(const QString &arg1)
{
    y2 = arg1.toInt();
}

void MainWindow::on_pushButton_clicked()
{
    drawLineOnPlot(x1, y1, x2, y2);

}
