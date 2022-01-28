/*
 ---------------------------------------------------------------------------
 Copyright (c) 2013, Igor Saric. All rights reserved.

 LICENSE TERMS

 The redistribution and use of this software (with or without changes)
 is allowed without the payment of fees or royalties provided that:

  1. source code distributions include the above copyright notice, this
     list of conditions and the following disclaimer;

  2. binary distributions include the above copyright notice, this list
     of conditions and the following disclaimer in their documentation;

  3. the name of the copyright holder is not used to endorse products
     built using this software without specific written permission.

 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness
 and/or fitness for purpose.
 ---------------------------------------------------------------------------
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinyaes.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PlainText->setText("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    ui->KeyText->setText("587b14e9ef30e95b64dc5ec71230197a");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ExecuteButton_clicked()
{
    TinyAES crypto;

    QByteArray key = crypto.HexStringToByte(ui->KeyText->text());
    QByteArray data = ui->PlainText->toPlainText().toLatin1();

    QByteArray encrypted = crypto.Encrypt(data, key);
    QByteArray decrypted = crypto.Decrypt(encrypted, key);

    ui->EncryptedText->setText(QString(encrypted));
    ui->DecryptedText->setText(QString(decrypted));

}
