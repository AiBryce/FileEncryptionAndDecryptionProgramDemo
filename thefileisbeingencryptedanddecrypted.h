#ifndef THEFILEISBEINGENCRYPTEDANDDECRYPTED_H
#define THEFILEISBEINGENCRYPTEDANDDECRYPTED_H

#include <QWidget>

namespace Ui {
class TheFileIsBeingEncryptedAndDecrypted;
}

class TheFileIsBeingEncryptedAndDecrypted : public QWidget
{
    Q_OBJECT

public:
    explicit TheFileIsBeingEncryptedAndDecrypted(QWidget *parent = nullptr);
    ~TheFileIsBeingEncryptedAndDecrypted();

private:
    Ui::TheFileIsBeingEncryptedAndDecrypted *ui;
};

#endif // THEFILEISBEINGENCRYPTEDANDDECRYPTED_H
