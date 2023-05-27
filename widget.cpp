#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);


    connect(this->ui->lineEdit,&QLineEdit::textChanged,this,[=](){
       this->ui->textEdit->append(QString("已经检测到："));
        this->ui->textEdit->append(QString(filePath));

    });

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
        this->ui->textEdit->append("你正在选择文件……\n");

        //点击按钮 弹出对话框，选择文件
        filePath = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\Administrator\\Desktop");
        qDebug()<<filePath;

        if(filePath.isEmpty())
        {
            this->ui->textEdit->append("没有选择文件！\n");
            QMessageBox::warning(this,"警告","文件路径不能为空");
            return;
        }
        else
        {
            this->ui->textEdit->append("选择文件：");
            this->ui->textEdit->append(filePath);
            this->ui->textEdit->append("\n");
            //将文件路径放入到 lineEdit中
            this->ui->lineEdit->setText(filePath);

            //将文件内容读取到 textEdit中
            QFile file(filePath);

            //指定打开方式
            file.open(QIODevice::ReadOnly);

            //Qt默认支持格式是utf-8
            QByteArray array;

            array = file.readLine();

            while(!file.atEnd())
            {
                array += file.readLine();
            }


            this->ui->textEdit->append(array);
            file.close();

        }







}
