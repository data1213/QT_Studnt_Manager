#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addstudents.h"
#include "Query_Students.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void show_my_Add_stud_Dialog();
    void show_my_Query_stud_Dialog();

private:
    Ui::MainWindow *ui;
    AddStudents AS;         //添加学生信息的Dialog窗口
    Query_Students QS;      //查询学生信息的Dialog窗口
};

#endif // MAINWINDOW_H
