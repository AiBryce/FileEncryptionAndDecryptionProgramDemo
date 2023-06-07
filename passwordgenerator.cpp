#include "passwordgenerator.h"
#include "ui_passwordgenerator.h"
using namespace std;
PasswordGenerator::PasswordGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);
    //文本框提示
    ui->textEdit->setPlaceholderText("若你要加密或解密你可以将密文或明文填在此处。");
    ui->lineEdit->setPlaceholderText("公共模数N，为加密解密同时拥有");
    ui->lineEdit_2->setPlaceholderText("公有密钥E，为加密拥有，解密时此处不填");
    ui->lineEdit_3->setPlaceholderText("公有密钥D，为解密拥有，加密时此处不填");
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}

using namespace std;

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


//欧几里得扩展算法，既辗转相除法
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
    this->ui->textEdit->append(QString("加密后密文:"));


    for(i = 0; i < 100; i++)
    {
        cout<<Ciphertext[i]<<" ";
        codeStt += QString::number(Ciphertext[i]);
        codeStt += QString(' ');

    }
    ui->textEdit->setTextColor(QColor(255,0,0));
    this->ui->textEdit->append(codeStt);
    ui->textEdit->setTextColor(QColor(0,0,0));
    encryptionCompleted(codeStt);
}

//RSA解密
void PasswordGenerator::RSA_Decrypt()
{
    int i = 0;
    for(i = 0; i < 100; i++)
        Ciphertext[i] = Modular_Exonentiation(Ciphertext[i], d, n);
    QString codeStt = "";
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
    for(i = 0; i < 100; i++)
    {
        cout<<Plaintext[i]<<" ";
        codeStt += QString::number(Plaintext[i]);
        codeStt += QString(' ');

    }
    this->ui->textEdit->append(codeStt);
}




void PasswordGenerator::on_pushButton_3_clicked()
{
    //加密
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","你没有输入N！");
        return;
    }
    if(ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","你没有输入E！");
        return;
    }
    if(ui->textEdit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this,"警告","你没有输入内容！");
        return;
    }

    n = ui->lineEdit->text().toInt();
    e = ui->lineEdit_2->text().toInt();
    QStringList list = ui->textEdit->toPlainText().split(" ");
    for (int i = 0; i < 100; i++) {
            Plaintext[i] = list[i].toLongLong();
        }
    RSA_Encrypt();
}

void PasswordGenerator::on_pushButton_clicked()
{
    Initialize();   //初始化算法
    RSA_Initialize();  //RSA初始化
    RSA_Encrypt();  //加密
    RSA_Decrypt();  //解密
    //分别将加密解密的密文明文放入textEdit
    this->ui->textEdit->append(QString("N:"));
            this->ui->textEdit->append(QString(QString::number(n)));
    this->ui->textEdit->append(QString("E:"));
            this->ui->textEdit->append(QString(QString::number(e)));
    this->ui->textEdit->append(QString("D:"));
            this->ui->textEdit->append(QString(QString::number(d)));
}

void PasswordGenerator::on_pushButton_2_clicked()
{
    //解密
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","你没有输入N！");
        return;
    }
    if(ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","你没有输入D！");
        return;
    }
    if(ui->textEdit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this,"警告","你没有输入内容！");
        return;
    }

    n = ui->lineEdit->text().toInt();
    d = ui->lineEdit_3->text().toInt();
        QStringList list = ui->textEdit->toPlainText().split(" ");
        for (int i = 0; i < 100; i++) {
                Ciphertext[i] = list[i].toLongLong();
            }
    RSA_Decrypt();

}
