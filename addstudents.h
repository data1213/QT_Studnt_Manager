#ifndef ADDSTUDENTS_H
#define ADDSTUDENTS_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class AddStudents;
}

class AddStudents : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudents(QWidget *parent = nullptr);
    ~AddStudents();
    void clear_on_addstudent_ok();
    void write_to_file(QString src);

private slots:
    void my_add_students_info_ok_slots();
    void my_add_students_info_cancel_slots();
private:
    QButtonGroup *sexGroup; //存放性别单选按钮
    QButtonGroup *habbitGroup;  //存放爱好多选按钮
    Ui::AddStudents *ui;
};

#endif // ADDSTUDENTS_H
