#include "thefileisbeingencryptedanddecrypted.h"
#include "ui_thefileisbeingencryptedanddecrypted.h"

TheFileIsBeingEncryptedAndDecrypted::TheFileIsBeingEncryptedAndDecrypted(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TheFileIsBeingEncryptedAndDecrypted)
{
    ui->setupUi(this);
}

TheFileIsBeingEncryptedAndDecrypted::~TheFileIsBeingEncryptedAndDecrypted()
{
    delete ui;
}
