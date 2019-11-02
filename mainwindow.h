#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QVector>

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

    int x1 = 0, y1 = 0; // premier point
    int x2 = 0, y2 = 0; // deuxieme point



private slots:
    void on_spinBox_valueChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(const QString &arg1);

    void on_spinBox_3_valueChanged(const QString &arg1);

    void on_spinBox_4_valueChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
