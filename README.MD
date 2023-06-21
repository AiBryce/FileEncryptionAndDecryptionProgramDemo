文件加密解密程序 V 1.1.7
FileEncryptionAndDecryptionProgramDemo
---
---
---

# 程序介绍

## 程序名称

文件加密解密程序 V 1.1.7

---

## V 1.1.7 更新内容：

1. 修复了一些bug。

近期更新：

1. 程序加入图标；
2. 美化界面；
3. 调整提示信息排版；
4. 修复检测文件不显示提示问题；
5. 加入了MD5加密算法，对密码进行MD5加密，提高了密码的安全性。
6. 加入了RSA加密。

---

## 程序介绍

本程序是一个文件加密解密程序，可以对文件进行加密和解密操作，加密后的文件只能通过本程序进行解密，解密后的文件也只能通过本程序进行加密。同时，本程序还可以生成随机密码，以及对密码进行RSA加密。

基于Qt Creator 4.12.2 (Based on Qt 5.14.2)开发。

- Qt versions: Qt 5.14.2
- Qt Creator versions: 4.12.2 (Windows 11)
- Build system: qmake
- Base class: QWidget
- Kit: Desktop Qt 5.14.2 MinGW 64-bit


# 程序结构

- `FileEncryptionAndDecryptionProgramDemo.pro`：项目配置文件

- `main.cpp`：程序入口文件

- `widget.cpp`: 主窗口源文件

- `widget.h`: 主窗口头文件

- `widget.ui`: 主窗口界面文件

- `passwordgenerator.cpp`: RAS加密解密算法源文件
  
- `passwordgenerator.h`: RAS加密解密算法头文件

- `passwordgenerator.ui`: RAS加密解密算法界面文件

# 核心代码

## 文件加密解密

```cpp
int i = 0;
while(!fileStrem.atEnd())
{
    uint bufferSize = 1;
    char buffer[1];
    qint64 bytesRead = fileStrem.readRawData(buffer, bufferSize);
    if (bytesRead == -1) break;
    buffer[0] ^= passwordKey[i++ % pwdlen];
    file_edStream.writeRawData(buffer, bytesRead);
}
```
## RAS加密解密算法

感谢：
[RSA加密算法c++简单实现](https://www.cnblogs.com/stwzhong/p/3402735.html)
[RSA加密算法](https://blog.csdn.net/lbwnbnbnbnbnbnbn/article/details/124173910)
两篇文章对于RSA加密算法的讲解，本程序的RSA加密算法部分参考了这两篇文章。