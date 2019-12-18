#include "versionauteurwindow.h"
#include "ui_versionauteurwindow.h"

versionAuteurWindow::versionAuteurWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::versionAuteurWindow)
{
    ui->setupUi(this);
}

versionAuteurWindow::~versionAuteurWindow()
{
    delete ui;
}
