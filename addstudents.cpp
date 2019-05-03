#include "addstudents.h"
#include "ui_addstudents.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QTextStream>

AddStudents::AddStudents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudents)
{
    ui->setupUi(this);

    //单选按钮放进组，多选按钮放进组
    sexGroup = new QButtonGroup(this);
    sexGroup->addButton(this->ui->rb_male,0);
    sexGroup->addButton(this->ui->rb_female,1);
    this->ui->rb_male->setChecked(true); //default

    habbitGroup = new QButtonGroup(this);
    habbitGroup->addButton(this->ui->cb_1,0);
    habbitGroup->addButton(this->ui->cb_2,1);
    habbitGroup->addButton(this->ui->cb_3,2);
    habbitGroup->addButton(this->ui->cb_4,3);
    // 设置不互斥
    habbitGroup->setExclusive(false);//这样的话就支持多选了。

    //连接“确认”按钮到槽函数
    connect(this->ui->btn_ok,SIGNAL(clicked()),this,SLOT(my_add_students_info_ok_slots()));
    //连接“取消”按钮到槽函数
    connect(this->ui->btn_cancel,SIGNAL(clicked()),this,SLOT(my_add_students_info_cancel_slots()));
}

AddStudents::~AddStudents()
{
    delete ui;
    delete sexGroup;
    delete habbitGroup;
}

void AddStudents::my_add_students_info_ok_slots(){

    //获取lineEdit控件的输入信息
    QString context = "";
    QString name = this->ui->lineedit_name->text();
    QString id = this->ui->lineedit_id->text();
    context +=name+'\n'+id+'\n';
    //获取年龄和院系
    QString age = this->ui->cb_age->currentText();
    QString sche = this->ui->cb_sche->currentText();

    context += age+'\n'+sche+'\n';

    //获取性别
    QString sex = this->sexGroup->checkedButton()->text();
    context += sex+'\n';

    //获取兴趣，遍历
    QList<QAbstractButton*> ins_list = habbitGroup->buttons();
    QString ins="";
    for(int i =0 ;i<ins_list.length();i++)
    {
        QAbstractButton *che = ins_list.at(i);
        if(che->isChecked())
            ins += che->text() + " ";
    }
    context += ins+'\n';

    if(context.length() != 0 && name != "" && id !="" && ins.length()!= 0){
        int res = QMessageBox::information(this,"请确认信息",context,"确认","取消");
        if(res == 0){
            //点击确定
            //由于准备采用readline的方式来读取文件，所以不能是用'\n'来拼接字符串，换成' '符号来拼接
            QString src_s = name +' ' + id+' '+sex+' '+sche+' '+age+' '+ins+'\n';
            write_to_file(src_s);
            //恢复添加界面属性值为初始值
            clear_on_addstudent_ok();
        }
    }else{
        QMessageBox::critical(this,"请确认信息","信息不完整，请重新输入！","确认","取消");
        //重新设置光标位置。这里设置name对应的lineEdit控件获取光标
        this->ui->lineedit_name->setFocus();
    }
}


//当点击添加学生信息界面的确定之后，需要恢复当前界面的初始值，等待继续添加
void AddStudents::clear_on_addstudent_ok(){
    //this->ui->lineedit_name->setText("");
    this->ui->lineedit_name->clear();
    this->ui->lineedit_id->clear();

    //对于sex的单选框，只需要设置默认为男性就好
    this->ui->rb_male->setChecked(true);

    //下拉菜单恢复设置
    this->ui->cb_age->setCurrentIndex(0);
    this->ui->cb_sche->setCurrentIndex(0);

    //多选框恢复到都未勾选状态
    QList<QAbstractButton*> ins_list = habbitGroup->buttons();
    QString ins;
    for(int i =0 ;i<ins_list.length();i++)
    {
        QAbstractButton *che = ins_list.at(i);
        che->setChecked(false);
    }

    //重新设置光标位置。这里设置name对应的lineEdit控件获取光标
    this->ui->lineedit_name->setFocus();
}

//保存添加学生信息界面的数据到文本
void AddStudents::write_to_file(QString src){
    QFile file("stu.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::critical(this,"打开文件错误","确认");
        return;
    }
    QTextStream out(&file);
    out << src;
}

//取消按钮的槽函数
void AddStudents::my_add_students_info_cancel_slots(){
    this->close();
}

