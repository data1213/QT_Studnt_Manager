#ifndef QUERY_STUDENTS_H
#define QUERY_STUDENTS_H

#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>


namespace Ui {
class Query_Students;
}

class Query_Students : public QDialog
{
    Q_OBJECT

public:
    explicit Query_Students(QWidget *parent = nullptr);
    ~Query_Students();

    int read_from_file();
    void do_query(int index,QString text);
    void match_stud_info(int row,QStringList subs);
    void set_table_title();
private slots:
    void start_to_query();

private:
    Ui::Query_Students *ui;
    QList<QString> stud_info_list;  //存放读取的学生信息

    QStandardItemModel* model;      //表对象
};

#endif // QUERY_STUDENTS_H
