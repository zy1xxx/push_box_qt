#include "editwindow.h"
#include "ui_editwindow.h"

editWindow::editWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::editWindow)
{
    ui->setupUi(this);
}

editWindow::~editWindow()
{
    delete ui;
}

void editWindow::on_back_to_main_clicked()
{
    emit showmainwindow();
    this->hide();
}
