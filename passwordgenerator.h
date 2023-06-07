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
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::PasswordGenerator *ui;
    unsigned long long RSAEnDe(unsigned long long num,unsigned long long Z);
    unsigned long long N,L,E,D;
    //二进制转换
    int BianaryTransform(int num, int bin_num[]);
    //反复平方求幂
    long long Modular_Exonentiation(long long a, int b, int n);
    //生成1000以内素数
    int ProducePrimeNumber(int prime[]);
    //欧几里得扩展算法
    int Exgcd(int m,int n,int &x);
    //RSA初始化
    void RSA_Initialize();
    //RSA加密
    void RSA_Encrypt();
    //RSA解密
    void RSA_Decrypt();
    //算法初始化
    void Initialize();
    int Plaintext[100];//明文
    long long Ciphertext[100];//密文
    int n, e = 0, d;

signals:
    void encryptionCompleted(QString key);

};

#endif // PASSWORDGENERATOR_H
