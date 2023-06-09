#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("文件加密解密程序");
    a.setApplicationDisplayName("文件加密解密程序");
    Widget w;
    //设置标题
    w.setWindowTitle("文件加密解密程序");
    w.show();
    return a.exec();
}
