#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"gui.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

/*****************************************************
主窗口类
******************************************************/

class ComponetDetectDialog : public QDialog
{
    Q_OBJECT
public:
    ComponetDetectDialog(QWidget *parent = 0);
    MainwindowWidget *maiW;

//    QLabel speedLabel;
//    QString *motorspeed;
//private slots:
//    void changemotorspeed();
};

#endif // DIALOG_H
