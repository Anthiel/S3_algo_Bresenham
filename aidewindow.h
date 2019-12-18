#ifndef AIDEWINDOW_H
#define AIDEWINDOW_H

#include <QDialog>

namespace Ui {
class aideWindow;
}

class aideWindow : public QDialog
{
    Q_OBJECT

public:
    explicit aideWindow(QWidget *parent = nullptr);
    ~aideWindow();

private:
    Ui::aideWindow *ui;
};

#endif // AIDEWINDOW_H
