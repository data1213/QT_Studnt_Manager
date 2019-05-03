#include "query_students.h"
#include "ui_query_students.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

Query_Students::Query_Students(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Query_Students)
{
    ui->setupUi(this);

    //创建查询窗口的时候，将文件数据全部获取到内存——stud_info_list中待用。
    int res = read_from_file();
    if(res == -1){
        this->close();  //打开文件失败，关闭当前窗口
    }

    //绑定 “开始查询”按钮到槽函数
    connect(this->ui->btn_query,SIGNAL(clicked()),this,SLOT(start_to_query()));

    /*
    创建一个表对象
    */
    this->model = new QStandardItemModel();
    /*
    为表的对应行、列锁定的表项填入数据
    */
    //1、设置表头,setHorizontalHeaderItem不需要行参数(就是第一行)，需要：列号+要显式的内容
    //表头是需要在窗口显式出来的时候就显式的，而数据项是在点击“开始查询”之后才填入的。
    this->set_table_title();
    //除表头外的数据后续添加...

    //关联表对象与tableview控件,这样表的内容就显式到tableview控件上去了
    this->ui->tableView->setModel(model);

}

Query_Students::~Query_Students()
{
    delete ui;
}


//读取学生信息操作
int Query_Students::read_from_file(){

    QString line_info="";
    QFile file("stu.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this,"打开文件错误","确认");
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        line_info = in.readLine();
        this->stud_info_list.append(line_info);
    }
    //关闭文件
    file.close();
    return 0;
}


void Query_Students::start_to_query(){

    //清空当前tableview数据
    this->model->clear();
    //重新设置表头
    this->set_table_title();

    //获取当前准备查询的类型，以及lineEdit的内容
    int methd = this->ui->cb_query->currentIndex();
    QString cnt = this->ui->le_query->text();
    this->do_query(methd,cnt);
}

//查询算法
void Query_Students::do_query(int index,QString text){
    //原始数据都在：QList<QString> stud_info_list;
    //遍历
    int row = 0;
    for(int i=0;i<this->stud_info_list.length();i++){
        QString line = this->stud_info_list.at(i);      //取出一条记录
        //去掉开头和末尾的空格字符
        line = line.trimmed();
        //分割
        QStringList qlist = line.split(" ");
        //匹配
        switch(index){
            case 0:
            if(text == qlist.at(0)){
                qDebug()<<line;
                this->match_stud_info(row++,qlist);
            }
            break;
        case 1:
            if(text == qlist.at(1)){
                this->match_stud_info(row++,qlist);
                qDebug()<<line;
            }
            break;
        case 2:
            if(text == qlist.at(3)){
                this->match_stud_info(row++,qlist);
                qDebug()<<line;
            }
            break;
        default:
            break;

        }
    }
}

/*
当获取到文件中一行记录之后，并且转换为QStringList对象了，需要将其填入到指定的行、列标识的表中
setItem:一次只能填一个表格的信息，需要知道行号+列号+内容
*/
void Query_Students::match_stud_info(int row,QStringList subs){
    //前面五个都是1对1的，比如：姓名-->jerry
    for(int i = 0;i<5;i++){
        this->model->setItem(row,i,new QStandardItem(subs.at(i)));
    }
    //对于爱好，由于是1对多的，需要拼接所有，然后显示在一个表格中
    QString line_item ="";
    for(int i=5;i<subs.length();i++){
        line_item +=subs.at(i)+',';
    }
    this->model->setItem(row,5,new QStandardItem(line_item));
}

void Query_Students::set_table_title(){
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("性别"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("院系"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("年龄"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("爱好"));

    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,200);
    this->ui->tableView->setColumnWidth(2,100);
    this->ui->tableView->setColumnWidth(3,200);
    this->ui->tableView->setColumnWidth(4,100);
    this->ui->tableView->setColumnWidth(5,200);
}
