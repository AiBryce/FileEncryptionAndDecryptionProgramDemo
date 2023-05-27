文件加密解密程序FileEncryptionAndDecryptionProgramDemo
---
---
---

# 项目介绍

## 项目名称

文件加密解密程序

## 项目功能

- 文件加密
- 文件解密

## 项目背景

本项目是一个文件加密解密程序，可以对文件进行加密和解密操作，加密后的文件只能通过本程序进行解密，解密后的文件也只能通过本程序进行加密。

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