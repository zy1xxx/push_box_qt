#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&play_ui, &playWindow::showmainwindow, this, &MainWindow::show);
    connect(&edit_ui, &editWindow::showmainwindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_play_B_clicked()
{
    this->hide();
    play_ui.show();
    play_ui.init_map_matrix();
}

void MainWindow::on_edit_B_clicked()
{
    this->hide();
    edit_ui.show();
}
