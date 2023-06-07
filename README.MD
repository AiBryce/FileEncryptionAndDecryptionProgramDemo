文件加密解密程序FileEncryptionAndDecryptionProgramDemo
---
---
---

# 项目介绍

## 项目名称

文件加密解密程序 V'1.1

---

V 1.1.2 更新内容：

1. 新增置入密码提示。
2. 新增RSA加密时无密钥提示。
3. 修复了一些bug。

近期更新：

1. 加入了MD5加密算法，对密码进行MD5加密，提高了密码的安全性。
2. 加入了RSA加密。

---

## 项目功能

- 文件加密
- 文件解密

本项目是一个文件加密解密程序，可以对文件进行加密和解密操作，加密后的文件只能通过本程序进行解密，解密后的文件也只能通过本程序进行加密。同时，本程序还可以生成随机密码，以及对密码进行RSA加密。

## 项目技术

本项目基于QtQt Creator 4.12.2 (Based on Qt 5.14.2)开发。

## 项目环境

- Qt versions: Qt 5.14.2
- Qt Creator versions: 4.12.2 (Windows 11)
- Build system: qmake
- Base class: QWidget
- Kit: Desktop Qt 5.14.2 MinGW 64-bit


# 项目结构

- `FileEncryptionAndDecryptionProgramDemo.pro`：项目配置文件

- `main.cpp`：程序入口文件

- `widget.cpp`: 主窗口源文件

- `widget.h`: 主窗口头文件

- `widget.ui`: 主窗口界面文件

- `passwordgenerator.cpp`: RAS加密解密算法源文件
  
- `passwordgenerator.h`: RAS加密解密算法头文件

- `passwordgenerator.ui`: RAS加密解密算法界面文件

# 核心代码

## 文件加密

```cpp
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
```

## 文件解密

```cpp
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
    ui->progressBar->setValue((int)(progressBarNum++ * 1.0 / fileSize * 79));
}


```


RAS加密解密算法

首先感谢：
[RSA加密算法c++简单实现](https://www.cnblogs.com/stwzhong/p/3402735.html)
[RSA加密算法](https://blog.csdn.net/lbwnbnbnbnbnbnbn/article/details/124173910)
两篇文章对于RSA加密算法的讲解，本项目的RSA加密算法部分参考了这两篇文章。
```cpp

//二进制转换
int PasswordGenerator::BianaryTransform(int num, int bin_num[])
{

    int i = 0,  mod = 0;

    //转换为二进制，逆向暂存temp[]数组中
    while(num != 0)
    {
        mod = num%2;
        bin_num[i] = mod;
        num = num/2;
        i++;
    }

    //返回二进制数的位数
    return i;
}
//反复平方求幂
long long PasswordGenerator::Modular_Exonentiation(long long a, int b, int n)
{
    int c = 0, bin_num[1000];
    long long d = 1;
    int k = BianaryTransform(b, bin_num)-1;

    for(int i = k; i >= 0; i--)
    {
        c = 2*c;
        d = (d*d)%n;
        if(bin_num[i] == 1)
        {
            c = c + 1;
            d = (d*a)%n;
        }
    }
    return d;
}
//生成1000以内素数
int PasswordGenerator::ProducePrimeNumber(int prime[])
{
    int c = 0, vis[1001];
    memset(vis, 0, sizeof(vis));
    for(int i = 2; i <= 1000; i++)if(!vis[i])
        {
            prime[c++] = i;
            for(int j = i*i; j <= 1000; j+=i)
                vis[j] = 1;
        }

    return c;
}

//欧几里得扩展算法
int PasswordGenerator::Exgcd(int m,int n,int &x)
{
    int x1,y1,x0,y0, y;
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;
    int r=m%n;
    int q=(m-r)/n;
    while(r)
    {
        x=x0-q*x1; y=y0-q*y1;
        x0=x1; y0=y1;
        x1=x; y1=y;
        m=n; n=r; r=m%n;
        q=(m-r)/n;
    }
    return n;
}
//RSA初始化
void PasswordGenerator::RSA_Initialize()
{
    //取出1000内素数保存在prime[]数组中
    int prime[5000];
    int count_Prime = ProducePrimeNumber(prime);
    //随机取两个素数p,q
    srand((unsigned)time(NULL));
    int ranNum1 = rand()%count_Prime;
    int ranNum2 = rand()%count_Prime;
    int p = prime[ranNum1], q = prime[ranNum2];
    n = p*q;
    int On = (p-1)*(q-1);
    //用欧几里德扩展算法求e,d
    for(int j = 3; j < On; j+=1331)
    {
        int gcd = Exgcd(j, On, d);
        if( gcd == 1 && d > 0)
        {
            e = j;
            break;
        }

    }
    this->ui->lineEdit->setText(QString(QString::number(n)));
    this->ui->lineEdit_2->setText(QString(QString::number(e)));
    this->ui->lineEdit_3->setText(QString(QString::number(d)));

}

//RSA加密
void PasswordGenerator::RSA_Encrypt()
{
    int i = 0;
    for(i = 0; i < 100; i++)
        Ciphertext[i] = Modular_Exonentiation(Plaintext[i], e, n);

    QString codeStt = "";
    //cout<<"Use the public key (e, n) to encrypt:"<<'\n';
    this->ui->textEdit->append(QString("加密后密文:"));
    for(i = 0; i < 100; i++)
    {
        cout<<Ciphertext[i]<<" ";
        codeStt += QString::number(Ciphertext[i]);
        codeStt += QString(' ');

    }
        this->ui->textEdit->append(codeStt);
       encryptionCompleted(codeStt);
}

//RSA解密
void PasswordGenerator::RSA_Decrypt()
{
    int i = 0;
    for(i = 0; i < 100; i++)
        Ciphertext[i] = Modular_Exonentiation(Ciphertext[i], d, n);
    QString codeStt = "";
    //cout<<"Use private key (d, n) to decrypt:"<<'\n';
    this->ui->textEdit->append(QString("解密后明文:"));
    for(i = 0; i < 100; i++)
    {
        cout<<Ciphertext[i]<<" ";
        codeStt += QString::number(Ciphertext[i]);
        codeStt += QString(' ');

    }
    this->ui->textEdit->append(codeStt);

}

//算法初始化
void PasswordGenerator::Initialize()
{
    int i;
    srand((unsigned)time(NULL));
    for(i = 0; i < 100; i++)
        Plaintext[i] = rand()%1000;
    this->ui->textEdit->append(QString("明文密码:"));
    QString codeStt = "";
    //cout<<"Generate 100 random numbers:"<<'\n';
    for(i = 0; i < 100; i++)
    {
        cout<<Plaintext[i]<<" ";
        codeStt += QString::number(Plaintext[i]);
        codeStt += QString(' ');

    }
        //cout<<Plaintext[i]<<" ";
    this->ui->textEdit->append(codeStt);
}
```