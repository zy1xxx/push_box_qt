#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QMainWindow>

namespace Ui {
class editWindow;
}

class editWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit editWindow(QWidget *parent = 0);
    ~editWindow();
signals:
    void showmainwindow();

private slots:
    void on_back_to_main_clicked();

private:
    Ui::editWindow *ui;
};

#endif // EDITWINDOW_H
