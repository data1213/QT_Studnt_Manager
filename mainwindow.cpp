#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addstudents.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //连接创建的菜单到槽
    connect(this->ui->actionAdd_Students,SIGNAL(triggered()),this,SLOT(show_my_Add_stud_Dialog()));
    connect(this->ui->actionQuery_Students,SIGNAL(triggered()),this,SLOT(show_my_Query_stud_Dialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug()<<"主窗口完成退出";
}

void MainWindow::show_my_Add_stud_Dialog(){
    AS.show();
}
void MainWindow::show_my_Query_stud_Dialog(){
    QS.show();
}
