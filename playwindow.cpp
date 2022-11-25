#include "playwindow.h"
#include "ui_playwindow.h"
#include <QPainter>
#include <fstream>
#include <QKeyEvent>

playWindow::playWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::playWindow)
{
    ui->setupUi(this);
    init_paint_obj();
}

playWindow::init_map_matrix(){
    std::ifstream infile;
    infile.open("../push_box/map.txt");//判断是否存在

    infile>>map_height>> map_width;
    map_matrix=new char*[map_height];
    for (int i = 0; i < map_height; i++)
    {
        map_matrix[i] = new char[map_width];
    }
    for (int i = 0; i < map_height; i++)
        {
            for (int j = 0; j < map_width; j++) {
                char tmp_s;
                infile >> tmp_s;
                switch (tmp_s)
                {
                case '#':
                    map_matrix[i][j] = '#';
                    break;
                case 'X':
                    map_matrix[i][j] = 'X';
                    break;
                case 'o':
                    map_matrix[i][j] = 'o';
                    break;
                case 'd':
                    map_matrix[i][j] = 'd';
                    break;
                case 'p':
                    map_matrix[i][j] = 'p';
                    player_pos.setX(i);
                    player_pos.setY(j);
                    break;
                case 'P':
                    map_matrix[i][j] = 'P';
                    player_pos.setX(i);
                    player_pos.setY(j);
                    break;
                case 'u':
                    map_matrix[i][j] = 'u';
                    break;
                default:
                    break;
                }
            }
        }
}


playWindow::~playWindow()
{
    delete ui;
}
playWindow::init_paint_obj(){
    bg.load("../push_box/img/bg.jpg");
    player.load("../push_box/img/player.png");
    box.load("../push_box/img/box.png");
    des.load("../push_box/img/des.png");
    wall.load("../push_box/img/wall.png");
}
void playWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    painter.drawPixmap(0, 0, box_width*map_height,box_width*map_width,bg);
    for (int i = 0; i < map_height; i++)
        {
            for (int j = 0; j < map_width; j++) {
                switch (map_matrix[i][j])
                {
                case '#':
                    painter.drawPixmap(box_width * j, box_width * i, box_width,box_width,wall);
                    break;
                case 'X':
                    painter.drawPixmap(box_width * j, box_width * i, box_width,box_width,box);
                    break;
                case 'o':
                    break;
                case 'd':
                    painter.drawPixmap(box_width * j, box_width * i,des,-16,-16,0,0);
                    break;
                case 'P':
                    painter.drawPixmap(box_width * j, box_width * i,des,-16,-16,0,0);
                    painter.drawPixmap(box_width * j, box_width * i,player,-16,0,0,0);
                    break;
                case 'p':
                    painter.drawPixmap(box_width * j, box_width * i,player,-16,0,0,0);
                    break;
                case 'u':
                    painter.drawPixmap(box_width * j, box_width * i,des,-16,-16,0,0);
                    painter.drawPixmap(box_width * j, box_width * i, box_width,box_width,box);
                    break;
                default:
                    break;
                }
            }
    }
}

QPoint playWindow::get_pos(int key,QPoint ori_pos){
    QPoint tmp(ori_pos);
    switch (key)
   {
       case Qt::Key_W :{tmp.rx()-=1;
        if(tmp.rx()<0){
            tmp.rx()=0;
        }
        break;}
       case Qt::Key_S : {
        tmp.rx()+=1;
        if(tmp.rx()>map_height-1){
            tmp.rx()=map_height-1;
        }
        break;
    }
    case Qt::Key_A :{tmp.ry()-=1;
     if(tmp.ry()<0){
         tmp.ry()=0;
     }
     break;}
    case Qt::Key_D : {
     tmp.ry()+=1;
     if(tmp.ry()>map_width-1){
         tmp.ry()=map_width-1;
     }
     break;
 }
   }
   return tmp;
}

void playWindow::keyPressEvent(QKeyEvent *e)
{
    QPoint new_player=get_pos(e->key(),player_pos);
    if(map_matrix[new_player.rx()][new_player.ry()]=='#'){
        return;
    }
    else if(map_matrix[new_player.rx()][new_player.ry()]=='X' || map_matrix[new_player.rx()][new_player.ry()]=='u'){
        QPoint new_box=get_pos(e->key(),new_player);
        if(map_matrix[new_box.rx()][new_box.ry()]=='#' || map_matrix[new_box.rx()][new_box.ry()]=='X' || map_matrix[new_player.rx()][new_player.ry()]=='u'){
            return;
        }
        else{
            if(map_matrix[player_pos.rx()][player_pos.ry()]!='p'){
                map_matrix[player_pos.rx()][player_pos.ry()]='o';
            }
            else{
                map_matrix[player_pos.rx()][player_pos.ry()]='d';
            }

            if(map_matrix[new_player.rx()][new_player.ry()]='u'){
                map_matrix[new_player.rx()][new_player.ry()]='P';
            }
            else{
                map_matrix[new_player.rx()][new_player.ry()]='p';
            }

            if(map_matrix[new_box.rx()][new_box.ry()]='o'){
                map_matrix[new_box.rx()][new_box.ry()]='X';
            }
            else{
                map_matrix[new_box.rx()][new_box.ry()]='u';
            }
        }
    }
    else{

        if(map_matrix[player_pos.rx()][player_pos.ry()]!='p'){
            map_matrix[player_pos.rx()][player_pos.ry()]='o';
        }
        else{
            map_matrix[player_pos.rx()][player_pos.ry()]='d';
        }

        if(map_matrix[new_player.rx()][new_player.ry()]='d'){
            map_matrix[new_player.rx()][new_player.ry()]='P';
        }
        else{
            map_matrix[new_player.rx()][new_player.ry()]='p';
        }
    }
    player_pos=new_player;
    update();
}

void playWindow::on_back_to_main_clicked()
{
    emit showmainwindow();
    this->hide();
}
