#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
ComponetDetectDialog::ComponetDetectDialog(QWidget *parent):QDialog(parent)
{
    //�½������ڣ�������������������ڵ��½�
    MainwindowWidget *MaiW = new MainwindowWidget(this);

}
//void ComponetDetectDialog::changemotorspeed()
//{
//    bool ok;
//    QString motorspeed = ComponetDetectDialoggetText(this,tr("Motor Speed"),tr("Please input new motor speed"),QLineEdit::Normal,speedLabel.text(),&ok);
//    if (ok && !motorspeed.isEmpty())
//        speedLabel.setText(motorspeed);
//}
