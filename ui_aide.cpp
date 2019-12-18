#include "ui_aide.h"
#include "ui_ui_aide.h"

ui_aide::ui_aide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ui_aide)
{
    ui->setupUi(this);
}

ui_aide::~ui_aide()
{
    delete ui;
}
