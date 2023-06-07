#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //设置当前窗口为无边框窗口
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    //设置textEdit自动换行模式为不换行
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);
    //----------------确保每次在textEdit的最后追加内容----------------------
    //创建一个名为cur的QTextCursor类型的变量，用于与窗口中的textEdit元素建立联系
    QTextCursor cur = ui->textEdit->textCursor();
    //对象在插入文本时，参数位置将保持不变。
    cur.setKeepPositionOnInsert(true);
    //将光标移动到文本的末尾
    cur.movePosition(QTextCursor::End);
    //-----------------------------------------------------------------
    //设置进度条取值范围为0到100
    ui->progressBar->setRange(0,100);
    //当lineEdit的文本发生改变，在textEdit中打印文本更改内容
    connect(this->ui->lineEdit,&QLineEdit::textChanged,this,[=](){
       this->ui->textEdit->append(QString("已经检测到："));
       this->ui->textEdit->append(ui->lineEdit_2->text());
    });
}

Widget::~Widget()
{
    delete ui;
}
//加密
int Widget::fileEncryption()    //成功返回1，失败返回0
{

    //密钥
    std::string passwordKey;
    //密钥长度
    int pwdlen;
    //判断文件路径是否为空
    QString filePath = ui->lineEdit->text();
    if(!filePath.isEmpty())
        this->ui->textEdit->append(QString("加密程序已经成功读取你的文件。"));
    else
    {
        ui->textEdit->setTextColor(QColor(255,0,0));
        this->ui->textEdit->append(QString("没有检测到文件路径。"));
        ui->textEdit->setTextColor(QColor(0,0,0));
        return 0;
    }

    ui->progressBar->setValue(2);
    //判断密钥是否为空
    if(!(ui->lineEdit_2->text().isEmpty()))
    {
        QByteArray byteText = ui->lineEdit_2->text().toUtf8();
        QString md5 = QCryptographicHash::hash(byteText, QCryptographicHash::Md5).toHex();
        passwordKey = md5.toStdString();
        qDebug() << md5;
        pwdlen = (int)passwordKey.length();
        ui->textEdit->append(QString("加密程序已经成功读取你的密钥("));
        ui->textEdit->append(ui->lineEdit_2->text());
        ui->textEdit->append(QString("字符)。"));
    }
    else
    {
        ui->textEdit->setTextColor(QColor(255,0,0));
        ui->textEdit->append(QString("没有检测到密钥。"));
        ui->textEdit->setTextColor(QColor(0,0,0));
        return 0;
    }
    ui->progressBar->setValue(4);
    this->ui->textEdit->append(QString("正在加密……"));
    ui->progressBar->setValue(6);
    //打开文件
    QFile file(filePath);
    //只读方式打开
    file.open(QIODevice::ReadOnly);
    //获取文件信息
    QFileInfo fileInfo(filePath);
    //创建加密后文件
    QString newFile = fileInfo.absolutePath() + "/fileEncryption_" +fileInfo.fileName();
    qDebug() << newFile;
    //以只写方式打开加密后文件
    QFile file_ed(newFile);
    file_ed.open(QIODevice::WriteOnly);
    ui->progressBar->setValue(20);
    //文件流打开
    QDataStream fileStrem(&file);
    QDataStream file_edStream(&file_ed);
    qint64 fileSize = fileInfo.size();


    this->ui->textEdit->append(QString("文件大小："));
    this->ui->textEdit->append(QString::number(fileSize));
    //----------------加解密核心代码-----------------------
    int i = 0;
    qint64 progressBarNum = 0;
    while(!fileStrem.atEnd())
    {
        uint bufferSize = 1;
        char buffer[1];
        //从文件流中读取缓存区大小的字节到buffer中

        qint64 bytesRead = fileStrem.readRawData(buffer, bufferSize);

        //检查读取是否成功
        if (bytesRead == -1)
        {
            //错误处理
            break;
        }
        buffer[0] ^= passwordKey[i++ % pwdlen];
        //从buffer中写入读取到的字节到目标文件流
        file_edStream.writeRawData(buffer, bytesRead);
        ui->progressBar->setValue((int)(20 + progressBarNum++ * 1.0 / fileSize * 79));
    }
    //--------------------------------------------
    ui->progressBar->setValue(100);
    //关闭文件
    file_ed.close();
    file.close();
    this->ui->textEdit->append(QString("加密完成。"));
    return 1;
}
//解密
int Widget::fileDecryption()    //成功返回1，失败返回0
{

    //密钥
    std::string passwordKey;
    //密钥长度
    int pwdlen;
    //判断文件路径是否为空
    QString filePath = ui->lineEdit->text();
    if(!filePath.isEmpty())
        this->ui->textEdit->append(QString("解密程序已经成功读取你的文件。"));
    else
    {
        ui->textEdit->setTextColor(QColor(255,0,0));
        this->ui->textEdit->append(QString("没有检测到文件路径。"));
        ui->textEdit->setTextColor(QColor(0,0,0));
        return 0;
    }
    ui->progressBar->setValue(2);
    //判断密钥是否为空
    if(!(ui->lineEdit_2->text().isEmpty()))
    {
        QByteArray byteText = ui->lineEdit_2->text().toUtf8();
        QString md5 = QCryptographicHash::hash(byteText, QCryptographicHash::Md5).toHex();
        passwordKey = md5.toStdString();
        pwdlen = (int)passwordKey.length();
        ui->textEdit->append(QString("解密程序已经成功读取你的密钥("));
        ui->textEdit->append(ui->lineEdit_2->text());
        ui->textEdit->append(QString(")。"));
    }
    else
    {
        ui->textEdit->setTextColor(QColor(255,0,0));
        ui->textEdit->append(QString("没有检测到密钥。"));
        ui->textEdit->setTextColor(QColor(0,0,0));

        return 0;
    }
    ui->progressBar->setValue(4);
    this->ui->textEdit->append(QString("正在加密……"));
    ui->progressBar->setValue(6);
    //打开文件
    QFile file(filePath);
    //只读方式打开
    file.open(QIODevice::ReadOnly);
    //获取文件信息
    QFileInfo fileInfo(filePath);
    //文件流打开
    QDataStream fileStrem(&file);
    //获取文件大小
    qint64 fileSize = fileInfo.size();
    this->ui->textEdit->append(QString("文件大小："));
    this->ui->textEdit->append(QString::number(fileSize));
    //创建加密后文件
    QString newFile = fileInfo.absolutePath() + "/fileDecryption_" +fileInfo.fileName();
    qDebug() << newFile;
    //以只写方式打开加密后文件
    QFile file_ed(newFile);
    file_ed.open(QIODevice::WriteOnly);
    ui->progressBar->setValue(20);
    QDataStream file_edStream(&file_ed);
    //----------------加解密核心代码-----------------------
    qint64 progressBarNum = 0;
    int i = 0;
    while(!fileStrem.atEnd())
    {
        uint bufferSize = 1;
        char buffer[1];
        //从文件流中读取缓存区大小的字节到buffer中

        qint64 bytesRead = fileStrem.readRawData(buffer, bufferSize);

        //检查读取是否成功
        if (bytesRead == -1)
        {
            //错误处理
            break;
        }
        buffer[0] ^= passwordKey[i++ % pwdlen];
        //从buffer中写入读取到的字节到目标文件流
        file_edStream.writeRawData(buffer, bytesRead);
        ui->progressBar->setValue((int)(progressBarNum++ * 1.0 / fileSize * 79));
    }
    //-----------------------------------------------
    //关闭文件
    file_ed.close();
    file.close();
    ui->progressBar->setValue(100);
    this->ui->textEdit->append(QString("解密完成。"));
    return 1;
}
 //选择文件
void Widget::on_pushButton_clicked()
{
        this->ui->textEdit->append("你正在选择文件……\n");

        //点击按钮 弹出对话框，选择文件
        filePath = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\Administrator\\Desktop");
        qDebug()<<filePath;

        if(filePath.isEmpty())
        {
            this->ui->textEdit->append(QString("没有选择文件！\n"));
            QMessageBox::warning(this,"警告","文件路径不能为空");
            return;
        }
        else
        {
            this->ui->textEdit->append(QString("选择文件："));
            this->ui->textEdit->append(filePath);
            this->ui->textEdit->append(QString("\n"));
            //将文件路径放入到 lineEdit中
            this->ui->lineEdit->setText(filePath);
        }
}
//加密
void Widget::on_pushButton_2_clicked()
{
    fileEncryption();
}
//解密
void Widget::on_pushButton_0_clicked()
{
    fileDecryption();
}
//关闭程序
void Widget::on_pushButton_3_clicked()
{
    this->close();
}
//生成密钥
void Widget::on_pushButton_4_clicked()
{
    //创建窗口对象
    PasswordGenerator *pg = new PasswordGenerator();
    pg->setWindowTitle(QString("RSA密钥生成器"));
    //若成功生成明文，则将明文置入密钥窗口
    connect(pg,&PasswordGenerator::encryptionCompleted,this,[=](QString key){
        key.chop(1);
       this->ui->lineEdit_2->setText(key);
       this->ui->textEdit->append(QString("已经接收到来自密码生成器的密钥"));
    });
    pg->show();

    //pg->close();
}

//-------------------事件监控---------------------
//当鼠标拖动widget控件时，可以实现拖动窗口移动
void Widget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->globalPos();
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget) {
            this->move(this->x() + (event->globalX() - m_lastPos.x()),
                       this->y() + (event->globalY() - m_lastPos.y()));
            m_lastPos = event->globalPos();
        }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{

    m_lastPos = event->globalPos();
    isPressedWidget = false; // 鼠标松开时，置为false
}
