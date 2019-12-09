#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QVector>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawLineOnPlot(double x1, double y1, double x2, double y2);
    void resetBresenham();

    void processPartOfBresenham(QVector<double> &listX, QVector<double> &listY, QVector<int> distance,
                                            int &princValue, int &maxPrincValue, int &otherValue, int ID,
                                            bool firstOpe, bool secOpe, bool thirdOpe, int operatorChoose);

    void addPixel(QVector<double> &listX, QVector<double> &listY, double x, double y);
    void drawBresenham(int x1, int y1, int x2, int y2);
    void prendrePartieVector();


    int x1 = 0, y1 = 0; // premier point
    int x2 = 0, y2 = 0; // deuxieme point

    int maxBresenham = 0;
    int etapeMaxBresenham = 0;
    int etape = 0;

    QVector <double> lX, lY;
    QVector<double> listX, listY;


private slots:
    void on_spinBox_valueChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(const QString &arg1);

    void on_spinBox_3_valueChanged(const QString &arg1);

    void on_spinBox_4_valueChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_EtapePrec_clicked();

    void on_EtapeSuiv_clicked();

    void on_supprBresenham_clicked();

    void on_BresenhamButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
