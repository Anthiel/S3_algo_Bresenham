#include "aidewindow.h"
#include "ui_aidewindow.h"

aideWindow::aideWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aideWindow)
{
    ui->setupUi(this);
}

aideWindow::~aideWindow()
{
    delete ui;
}
