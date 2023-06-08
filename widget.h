#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
#include<QMouseEvent>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#include <string>
#include <QThread>
#include "passwordgenerator.h"
#include <QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    QString filePath; //加密文件
    int fileEncryption(); //加密
    int fileDecryption(); //解密
protected:
    //事件监控
    //当鼠标拖动widget控件时，可以实现拖动窗口移动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool isPressedWidget;//判断鼠标是否按下，用于防止点击后窗口发生位移
    QPoint m_lastPos;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();   //选择文件
    void on_pushButton_2_clicked();   //加密
    void on_pushButton_0_clicked();   //解密
    void on_pushButton_3_clicked();   //关闭程序
    void on_pushButton_4_clicked();   //生成密钥

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
