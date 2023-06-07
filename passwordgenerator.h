#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QWidget>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <QCryptographicHash>  //md5加密的库
#include <QDebug>   //调试输出
#include <QMessageBox>

namespace Ui {
class PasswordGenerator;
}

class PasswordGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordGenerator(QWidget *parent = nullptr);
    ~PasswordGenerator();

private slots:
    void on_pushButton_3_clicked(); //RSA加密
    void on_pushButton_clicked();  //生成随机密钥
    void on_pushButton_2_clicked(); //RSA解密
private:
    Ui::PasswordGenerator *ui;
    int BianaryTransform(int num, int bin_num[]);    //二进制转换
    long long Modular_Exonentiation(long long a, int b, int n);    //反复平方求幂
    int ProducePrimeNumber(int prime[]);    //生成1000以内素数
    int Exgcd(int m,int n,int &x);    //欧几里得扩展算法
    void RSA_Initialize();    //RSA初始化
    void RSA_Encrypt();    //RSA加密
    void RSA_Decrypt();    //RSA解密
    void Initialize();    //算法初始化
    int Plaintext[100];  //明文
    long long Ciphertext[100];  //密文
    int n, e = 0, d;

signals:
    void encryptionCompleted(QString key);

};

#endif // PASSWORDGENERATOR_H
