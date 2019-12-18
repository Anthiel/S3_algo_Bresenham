#ifndef VERSIONAUTEURWINDOW_H
#define VERSIONAUTEURWINDOW_H

#include <QDialog>

namespace Ui {
class versionAuteurWindow;
}

class versionAuteurWindow : public QDialog
{
    Q_OBJECT

public:
    explicit versionAuteurWindow(QWidget *parent = nullptr);
    ~versionAuteurWindow();

private:
    Ui::versionAuteurWindow *ui;
};

#endif // VERSIONAUTEURWINDOW_H
