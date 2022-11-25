#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>


namespace Ui {
class playWindow;
}

class playWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit playWindow(QWidget *parent = 0);

    ~playWindow();
    init_map_matrix();
signals:
    void showmainwindow();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

private slots:

    void on_back_to_main_clicked();

private:
    Ui::playWindow *ui;
    QPixmap bg;
    QPixmap player;
    QPixmap box;
    QPixmap des;
    QPixmap wall;

    int map_height,map_width;
    int box_width=64;
    char **map_matrix;
    QPoint player_pos;

    init_paint_obj();
    QPoint get_pos(int key, QPoint ori_pos);
};

#endif // PLAYWINDOW_H
