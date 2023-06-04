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
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool isPressedWidget;//判断鼠标是否按下，用于防止点击后窗口发生位移
    QPoint m_lastPos;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_0_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
