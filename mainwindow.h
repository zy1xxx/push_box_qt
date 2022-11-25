#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "playwindow.h"
#include "editwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_play_B_clicked();

    void on_edit_B_clicked();

private:
    Ui::MainWindow *ui;
    playWindow play_ui;
    editWindow edit_ui;
};

#endif // MAINWINDOW_H
