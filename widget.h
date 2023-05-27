#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "encryptionanddecryption.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    QString filePath; //加密文件
    int fileEncryption(QString filePath); //加密
    int fileDecryption(QString filePath); //解密




public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_0_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
